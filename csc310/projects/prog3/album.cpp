#include <iostream>
#include <string>
#include "album.h"
using namespace std;

Album::Album(const Album& otherAlbum) {
	strcpy(UPC, otherAlbum.UPC); strcpy(Artist, otherAlbum.Artist); strcpy(Title, otherAlbum.Title);
}

Album::Album(String upc, String artist, String title) {
	strcpy(UPC, upc); strcpy(Artist, artist); strcpy(Title, title);
}

/*
Album::Album() {
	strcpy(UPC, "\0"); strcpy(Artist, "\0"); strcpy(Title, "\0");
}

Album & Album::operator = (const Album& otherAlbum) {
	strcpy(UPC, otherAlbum.UPC); strcpy(Artist, otherAlbum.Artist); strcpy(Title, otherAlbum.Title);
	return *this;	
}

istream & operator >> (istream & stream, Album & C) {

}

ostream & operator << (ostream & stream, Album & C) {
	cout << C.UPC << " " << C.Artist << " " << C.Title << endl;
	return stream;
}

string Album::getUPC() {
	return UPC;
}

int Album::recordSize() {

}
*/
