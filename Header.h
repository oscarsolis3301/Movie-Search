#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

struct titles {
	string title;
	titles* next;
};

struct leadingActors {
	string leadActor;
	leadingActors* next;
};

struct supportActors {
	string supportActor;
	supportActors* next;
};

struct genres {
	string genre;
	genres* next;
};

struct alternativeGenres {
	string alternativeGenre;
	alternativeGenres* next;
};

struct years {
	string year;
	years* next;
};

struct ratings {
	string rating;
	ratings* next;
};

struct synopsis {
	string synops;
	synopsis* next;
};


struct movies {
	int year;
	int rating;
	string title;
	string leadingActor;
	string supportActor;
	string genre;
	string alternateGenre;
	string synopsis;
};

struct fileNames {
	string inputFileName;
	string outputFileName;
};

struct filesInfo {
	ifstream InFile;
	ifstream lines;
	ofstream OutFile;
};


void GetFiles(string& inputFileName, string& outputFileName);
void OpenFiles(string inputFileName, string outputFileName, ifstream& InFile, ifstream& lines, ofstream& OutFile);
void DisplayMenu(int& option);

void AddTitle(titles*& head, titles*& newTitle, string title);
void AddLeadActor(leadingActors*& head, leadingActors*& tail, string name);
void AddSupportActor(supportActors*& head, supportActors*& tail, string supportActor);
void AddGenre(genres*& head, genres*& tail, string genre);
void AddAlternativeGenre(alternativeGenres*& head, alternativeGenres*& tail, string alternativeGenre);
void AddYear(years*& head, years*& tail, string year);
void AddRating(ratings*& head, ratings*& tail, string rating);
void AddSynopsis(synopsis*& head, synopsis*& tail, string synops);
void Search(titles* head, years* year, ratings* rating, genres* genre, 
		alternativeGenres* altGenres, leadingActors* lead, supportActors* support, 
		ofstream& oFile, int choice);
void ListAllMovies(titles* head, years* year, ratings* rating, genres* genre,
	alternativeGenres* altGenres, leadingActors* lead, supportActors* support, ofstream& oFile);

