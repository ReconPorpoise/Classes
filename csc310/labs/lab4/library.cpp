#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include "mp3.cpp"
using namespace std;

void makeList(set<Artist>& artists, string fileName);
void printList(set<Artist> artists);
string under2Space(string toChange);

int main(int argc, char** argv) 
{
	if(argc != 2) {
		cout << "mp3: missing filename 'mp3'" << endl;
		return 1;
	}

	set<Artist> artists;
	makeList(artists, argv[1]);
	printList(artists);
	
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
	
		string song = under2Space(info[0]);
		string time = info[1];		

		int timeFix = 0;
		vector<string> timePiece;
		stringstream t(time);
		string token;
		while(getline(t, token, ':'))
			timePiece.push_back(token);
		timeFix += stoi(timePiece[0]) * 60;
		timeFix += stoi(timePiece[1]);
		time = to_string(timeFix);
		
		string artist = under2Space(info[2]);
		string album = under2Space(info[3]);
		string genre = under2Space(info[4]);
		string track = info[5]; 		


		// gets the artist position
		set<Artist>::iterator artFind = find(artists.begin(), artists.end(), artist);
		if(artFind == artists.end()) {
			// create new artist
			Artist newArtist;
			newArtist.name = artist;
			newArtist.time = 0;
			newArtist.time += stoi(time);
			newArtist.nsongs = 1;
			// create new album
			Album newAlbum;
			newAlbum.name = album;
			newAlbum.artist = artist;
			newAlbum.genre = genre;
			newAlbum.time = 0;
			newAlbum.time += stoi(time);
			newAlbum.nsongs = 1;
			// create new song
			Song newSong;
			newSong.title = song;
			newSong.time = stoi(time);
			newSong.track = stoi(track);
	
			newAlbum.songs[stoi(track)] = newSong;
			newArtist.albums.insert(newAlbum);
	
			artists.insert(newArtist);
		}
		// if artist exists:
		else {
			Artist cArt = *artFind;
			set<Album>::iterator albFind = find(cArt.albums.begin(), cArt.albums.end(), album);
			// if album doesn't exist:
			if(albFind == cArt.albums.end()) {
				// create new album
				Album newAlbum;
				newAlbum.name = album;
				newAlbum.artist = artist;
				newAlbum.genre = genre;
				newAlbum.time = 0;
				newAlbum.time += stoi(time);
				newAlbum.nsongs += 1;
				cArt.nsongs += 1;
				cArt.time += stoi(time);

				// create and add song to it
				Song newSong;
				newSong.title = song;
				newSong.time = stoi(time);
				newSong.track = stoi(track);
				
				// add song to album
				newAlbum.songs[stoi(track)] = newSong;

				// add album to artist
				cArt.albums.insert(newAlbum);
			}
			// if album exists:
			else {
				Album cAlb = *albFind;

				// create and add new song
				Song newSong;
				newSong.title = song;
				newSong.time = stoi(time);
				newSong.track = stoi(track);	
				cAlb.songs[stoi(track)] = newSong;
				// increase album and artist time and song count
				cAlb.time += stoi(time);
				cAlb.nsongs += 1;
				cArt.time += stoi(time);
				cArt.nsongs += 1;

				// we cannot update sets... delete old replace with new
				cArt.albums.erase(albFind);
				cArt.albums.insert(cAlb);
			}		
			artists.erase(artFind);
			artists.insert(cArt);
		}
		info.clear();
		timePiece.clear();
	}
	infile.close();
}

void printList(set<Artist> artists) 
{
	set<Artist>::iterator it;
	for(it = artists.begin(); it != artists.end(); ++it)
		cout << *it;
}

// convert underscores to spaces
string under2Space(string toChange) {
	string toReturn = "";
	for(int i = 0; i < toChange.length(); i++) {
		if(toChange[i] == '_')
			toReturn += " ";
		else
			toReturn += toChange[i];
	}
	return toReturn;
}
