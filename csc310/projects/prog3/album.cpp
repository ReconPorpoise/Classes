#include <iostream>
#include <string>
#include "album.h"
using namespace std;

Album::Album(const Album& otherAlbum) {
	strcpy(UPC, otherAlbum.UPC); strcpy(Artist, otherAlbum.Artist); 
	strcpy(Title, otherAlbum.Title);
}

Album::Album(String upc, String artist, String title) {
	strcpy(UPC, upc); strcpy(Artist, artist); strcpy(Title, title);
}

Album::Album() {
	strcpy(UPC, "\0"); strcpy(Artist, "\0"); strcpy(Title, "\0");
}

Album & Album::operator = (const Album& otherAlbum) {
	strcpy(UPC, otherAlbum.UPC); strcpy(Artist, otherAlbum.Artist); 
	strcpy(Title, otherAlbum.Title);
	return *this;	
}

bool operator < (const Album& a, const Album& b) {
	return a.UPC < b.UPC;
}

istream & operator >> (istream & stream, Album & C) {
	stream.getline(C.UPC, 50, '\n');
	stream.getline(C.Artist, 50, '\n');
	stream.getline(C.Title, 50, '\n');
	return stream;	
}

ostream & operator << (ostream & stream, Album & C) {
	cout << C.UPC << " " << C.Artist << " " << C.Title;
	return stream;
}

string Album::getUPC() {
	return UPC;
}

int Album::recordSize() {
	return sizeof(Album);
}
