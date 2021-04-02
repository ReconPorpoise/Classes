#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

class Song {
public:
  string title;
  int time;
  int track;      // Primary key
  bool operator < (Song another) const { return title < another.title;}
};

//this operator writes out the song in the correct format
inline ostream & operator << (ostream& out, Song & l) {     
  cout << "\t\t" << l.track << ".  " << l.title << ": " << l.time/60 << ":";
  if ((l.time % 60) < 10) cout << "0";
  cout << l.time % 60;
  return out;
}

class Album {
  public :
    mutable map<int, Song> songs;
    string name;  // Album's name
    string artist;
    string genre;
    mutable int time;     // Total time of all songs on album
    mutable int nsongs;   // Total number of songs on album

    bool operator < (Album another) const { return name < another.name;}
    bool operator == (string albumName) const { return name == albumName;}
    friend std::ostream& operator<<(std::ostream& out, const Album& al);
};

//this operator writes out the album in the correct format
inline ostream& operator<<(ostream& out, const Album& al)
{
  cout << "\t" << al.name << ": " << al.nsongs << ", " << al.time/60 << ":";
  if ((al.time % 60) < 10) cout << "0";
  cout << al.time % 60 << endl;
  for (map<int, Song>::const_iterator it=al.songs.begin(); it!=al.songs.end(); ++it){
    Song curSong = it->second;
    cout << curSong << endl;
  }
  return out;
}

class Artist {
   public :
     string name; // Artist's name
     mutable set<Album> albums; // Artist's Albums
     int time;    // Total time of all songs on all albums by this artist
     int nsongs;  // Total number of songs on all albums by this artist

     bool operator < (Artist another) const { return name < another.name;}
     bool operator == (string artistName) const { return name == artistName;}
     friend std::ostream& operator<<(std::ostream& out, const Artist& ar);
};

//this operator writes out the artist in the correct format
inline ostream& operator<<(ostream& out, const Artist& ar)
{
  cout << ar.name << ": " << ar.nsongs << ", " << ar.time/60 << ":";
  if ((ar.time % 60) < 10) cout << "0";
  cout << ar.time % 60 << endl;
  for (set<Album>::iterator it=ar.albums.begin(); it!=ar.albums.end(); ++it)
    cout << *it;
  return out;
}
