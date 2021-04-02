#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include "mp3.cpp"
using namespace std;

void makeList(set<Artist>& artists, string fileName);

int main(int argc, char** argv) 
{
	if(argc != 2) {
		cout << "mp3: missing filename 'mp3'" << endl;
		return 1;
	}

	set<Artist> artists;
	makeList(artists, argv[1]);
	
	return 0;
}

void makeList(set<Artist>& artists, string fileName) {
	fstream infile(fileName.c_str(), ios::in);
	string currRecord = "";
	while(getline(infile, currRecord)) {
		// split the line into the separate info per track
		vector<string> info;
		stringstream s(currRecord);
		string temp;
		while(s >> temp)
			info.push_back(temp);
	
		string song = info[0];
		string time = info[1];
		string artist = info[2];
		string album = info[3];
		string genre = info[4];
		string track = info[5]; 		

		if(artists.find(artist) == artists.end()) {
			// create new artist
			Artist newArtist;
			newArtist.name = artist;
			newArtist.time += stoi(time);
			newArtist.nsongs++;
			// create new album
			Album newAlbum;
			newAlbum.name = album;
			newAlbum.artist = artist;
			newAlbum.genre = genre;
			newAlbum.time += stoi(time);
			newAlbum.nsongs++;

			// create new song
			Song newSong;
			newSong.title = song;
			newSong.time = stoi(time);
			newSong.track = stoi(track);
	
			newAlbum.songs[stoi(track)] = newSong;
			newArtist.albums.insert(newAlbum);
		}
		// if artist exists and album doesn't:
		else {
			set<Artist>::iterator it;
			for(it = artists.begin(); it != artists.end(); it++) {
				set<Album>::iterator it2;
				bool found = false;
				for(it2 = it.albums.begin(); it != it2.albums.end(); i2++) {
					if(it.name == album)
						found = true;
					if(found) {
						Song newSong;
						newSong.title = song;
						newSong.time = stoi(time);
						newSong.track = stoi(track);
						it.albums.songs[stoi(track)] = newSong;
						break;
					}
				}
				if(!found) {
					Album newAlbum;
					newAlbum.name = album;
					newAlbum.artist = artist;
					newAlbum.genre = genre;
					newAlbum.time += stoi(time);
					newAlbum.nsongs++;

					// create new song
					Song newSong;
					newSong.title = song;
					newSong.time = stoi(time);
					newSong.track = stoi(track);
			
					newAlbum.songs[stoi(track)] = newSong;
				}
			}
		}
	}
	infile.close();
}

// song -> time -> artist -> album -> genre -> track number

/* TODO:
 * - Use a map named songs for all Album objects that will use track num as primary key for a Song object
 * - All artists are to be printed sorted lexicographically, with artist name, comma and space, and total runtime of all songs
 *  	- after each artist, we print their albums (sorted lexicographically) followed by their number of songs and runtime for the album
 *  		- after each album, print each song sorted by track number (16 spaces, track number, a period, a space, the song name, colon, space, song time.
 *  	*make sure all underscores become spaces
 * - (This is in mp3.cpp) Check if artist already exists in vector, if they do, check if the album exists, if it does, add the song, if not, add the album and the song. 
 *   	- if artist doesn't exist, add the artist, album, and song
 */
