#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "mp3.cpp"
using namespace std;

int main(int argc, char** argv) 
{
	if(argc != 2) {
		cout << "mp3: missing filename 'mp3'" << endl;
		return 1;
	}
	
	return 0;
}
/* TODO:
 * - Use a map named songs for all Album objects that will use track num as primary key for a Song object
 * - All artists are to be printed sorted lexicographically, with artist name, comma and space, and total runtime of all songs
 *  	- after each artist, we print their albums (sorted lexicographically) followed by their number of songs and runtime for the album
 *  		- after each album, print each song sorted by track number (16 spaces, track number, a period, a space, the song name, colon, space, song time.
 *  	*make sure all underscores become spaces
 * - (This is in mp3.cpp) Check if artist already exists in vector, if they do, check if the album exists, if it does, add the song, if not, add the album and the song. 
 *   	- if artist doesn't exist, add the artist, album, and song
 */
