#include "Header.h"

enum Menu{Exit, Output, Title, Genre, Actor, Year, Rating};

int main() {
	int option = NULL;
	bool run;
	run = true;
	Menu exit;
	exit = Exit;
	Menu menuOption;
	fileNames fn;
	filesInfo fi;
	movies search;

	titles *headTitle = NULL;
	titles *tailTitle = NULL; 

	titles* headTitle1 = NULL;
	titles* tailTitle1 = NULL;
	string title;

	leadingActors* headActor = NULL;
	leadingActors* tailActor = NULL;
	string leadActor;

	supportActors* headSupportActor = NULL;
	supportActors* tailSupportActor = NULL;
	string supportActor;

	genres* headGenre = NULL;
	genres* tailGenre = NULL;
	string genre;

	alternativeGenres* headAltGenre = NULL;
	alternativeGenres* tailAltGenre = NULL;
	string altGenre;

	years* headYear = NULL;
	years* tailYear = NULL;
	string year;

	ratings* headRating = NULL;
	ratings* tailRating = NULL;
	string rating;

	synopsis* headSynops = NULL;
	synopsis* tailSynops = NULL;
	string synops;

	GetFiles (fn.inputFileName, fn.outputFileName);
	OpenFiles(fn.inputFileName, fn.outputFileName, fi.InFile, fi.lines, fi.OutFile);

	while (run) {
		DisplayMenu(option);
		if (option == 0) {
			run = false;
		}
		else if (option >= 0 && option <= 6) {
			int amountOfLines = 0;
			string amountOfLinesHolder;

			while (getline(fi.lines, amountOfLinesHolder)) {
				amountOfLines++;
			}

			string emptyLine;
			const int RUN_AMOUNT = amountOfLines / 9;
			for (int i = 0; i < RUN_AMOUNT; i++) {

				string titleLine, leadActorLine, supportActorLine, genreLine,
					alternateGenreLine, yearLine, ratingLine, line, eachWord,
					synopsisLine;
				string dot = ". ";
				getline(fi.InFile, titleLine);

				getline(fi.InFile, leadActorLine);

				getline(fi.InFile, supportActorLine);

				getline(fi.InFile, genreLine);

				getline(fi.InFile, alternateGenreLine);

				getline(fi.InFile, yearLine);

				getline(fi.InFile, ratingLine);

				int index = 0;
				int key = 0;
				bool found = false;
				while (!found) {
					while (getline(fi.InFile, line)) {
						found = line.find('.');
						if (found != string::npos) {
							break;
						}
					}
				}

				stringstream iss(line);

				while (iss >> eachWord) {
					if (index >= 10) {
						if (eachWord.size() > 9) {
							synopsisLine = synopsisLine + "\n" + eachWord;

							index = 0;
						}
						else {
							if (index >= 13) {
								synopsisLine = synopsisLine + "\n" + eachWord;

								index = 0;
							}
							else {
								synopsisLine = synopsisLine + " " + eachWord;

								index++;
							}
						}
					}
					else if (index < 10) {
						if (key == 0) {
							synopsisLine = eachWord;
							key++;
							index++;
						}
						else {
							synopsisLine = synopsisLine + " " + eachWord;
							index++;
						}
					}
				}
				getline(fi.InFile, emptyLine);
				AddTitle(headTitle, tailTitle, titleLine);
				AddLeadActor(headActor, tailActor, leadActorLine);
				AddSupportActor(headSupportActor, tailSupportActor, supportActorLine);
				AddGenre(headGenre, tailGenre, genreLine);
				AddAlternativeGenre(headAltGenre, tailAltGenre, alternateGenreLine);
				AddYear(headYear, tailYear, yearLine);
				AddRating(headRating, tailRating, ratingLine);
				AddSynopsis(headSynops, tailSynops, synopsisLine);
			}


			if (option == 1) {
				menuOption = Output;
			}
			else if (option == 2) {
				menuOption = Title;
			}
			else if (option == 3) {
				menuOption = Genre;
			}
			else if (option == 4) {
				menuOption = Actor;
			}
			else if (option == 5) {
				menuOption = Year;
			}
			else if (option == 6) {
				menuOption = Rating;
			}

			if (menuOption == Output) {

				ListAllMovies(headTitle, headYear, headRating, headGenre, headAltGenre, headActor, headSupportActor, fi.OutFile);

			} else if (menuOption == Title || menuOption == Genre || menuOption == Actor || menuOption == Year || menuOption == Rating) {

				Search(headTitle, headYear, headRating, headGenre,
					headAltGenre, headActor, headSupportActor, fi.OutFile, menuOption);

			} 

		} else {
			cin.fail();
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl << "***** Please Enter an Appropriate Option *****" << endl;
		}
	}

	system("pause");
	return 0;
}

void GetFiles(string& inputFileName, string& outputFileName) {
	cout << "Which input file would you like to use (type d for default file)? ";
	getline(cin, inputFileName);
	cout << "Which output file would you like to use (type d for default file)? ";
	getline(cin, outputFileName);
}

void OpenFiles(string inputFileName, string outputFileName, ifstream& InFile, ifstream& lines, ofstream& OutFile) {
	if (inputFileName == "d" || inputFileName == "D") {
		InFile.open("InFile.txt");
		lines.open("InFile.txt");
	}
	else {
		InFile.open(inputFileName);
		lines.open(inputFileName);
	}

	if (outputFileName == "d" || outputFileName == "D") {
		OutFile.open("OutFile.txt");
	}
	else {
		OutFile.open(outputFileName);
	}
}

void DisplayMenu(int& option) {
	cout << endl << "DVD MENU OPTIONS" << endl << endl;
	cout << "1 - Output Entire List" << endl;
	cout << "2 - Title Search" << endl;
	cout << "3 - Genre Search" << endl;
	cout << "4 - Actor Search" << endl;
	cout << "5 - Year Search" << endl;
	cout << "6 - Rating Search (0-9)" << endl;
	cout << "0 - EXIT" << endl;
	cout << "Enter an option (0 to exit) : ";
	cin >> option;
}

void AddTitle(titles *&head, titles *&newTitle, string title) {
	titles* temp = new titles;
	if (head == NULL) {
		temp->title = title;
		temp->next = NULL;
		head = temp;
		newTitle = temp;
	} else {
		temp->title = title;
		temp->next = NULL;
		newTitle->next = temp;
		newTitle = temp;
	}
}

void AddLeadActor(leadingActors*&head, leadingActors*&tail, string actorName) {
	leadingActors* temp = new leadingActors;
	if (head == NULL) {
		temp->leadActor = actorName;
		temp->next = NULL;
		head = temp;
		tail = temp;
	}else {
		temp->leadActor = actorName;
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}
}

void AddSupportActor(supportActors*& head, supportActors*& tail, string supportActor) {
	supportActors* temp = new supportActors;
	if (head == NULL) {
		temp->supportActor = supportActor;
		temp->next = NULL;
		head = temp;
		tail = temp;
	} else {
		temp->supportActor = supportActor;
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}
}
void AddGenre(genres*& head, genres*& tail, string genre) {
	genres* temp = new genres;
	if (head == NULL) {
		temp->genre = genre;
		temp->next = NULL;
		head = temp;
		tail = temp;
	} else {
		temp->genre = genre;
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}
}

void AddAlternativeGenre(alternativeGenres*& head, alternativeGenres*& tail, string alternativeGenre) {
	alternativeGenres* temp = new alternativeGenres;
	if (head == NULL) {
		temp->alternativeGenre = alternativeGenre;
		temp->next = NULL;
		head = temp;
		tail = temp;
	} else {
		temp->alternativeGenre = alternativeGenre;
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}
}

void AddYear(years*& head, years*& tail, string year) {
	years* temp = new years;
	if (head == NULL) {
		temp->year = year;
		temp->next = NULL;
		head = temp;
		tail = temp;
	} else {
		temp->year = year;
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}
}

void AddRating(ratings*& head, ratings*& tail, string rating){
	ratings* temp = new ratings;
	if (head == NULL) {
		temp->rating = rating;
		temp->next = NULL;
		head = temp;
		tail = temp;
	} else {
		temp->rating = rating;
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}
}
void AddSynopsis(synopsis*& head, synopsis*& tail, string synops) {
	synopsis* temp = new synopsis;
	if (head == NULL) {
		temp->synops = synops;
		temp->next = NULL;
		head = temp;
		tail = temp;
	} else {
		temp->synops = synops;
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}
}

void Search(titles* head, years* year, ratings* rating, genres* genre, 
	alternativeGenres* altGenres, leadingActors* lead, supportActors* support,
	ofstream& oFile, int choice) {
	
	filesInfo fi;
	fi.lines.open("InFile.txt");
	string input;
	string yearOrRating;

	if (choice == Title) {
		cout << "Enter a title : ";
		cin.ignore(1000, '\n');
		getline(cin, input);
	}
	else if (choice == Actor) {
		cout << "Enter an actor : ";
		cin.ignore(1000, '\n');
		getline(cin, input);
	}
	else if (choice == Genre) {
		cout << "Enter a genre : ";
		cin.ignore(1000, '\n');
		getline(cin, input);
	}
	else if (choice == Year) {
		cout << "Enter a year : ";
		cin.ignore(1000, '\n');
		getline(cin, yearOrRating);
	}
	else if (choice == Rating) {
		cout << "Enter a rating : ";
		cin.ignore(1000, '\n');
		getline(cin, yearOrRating);
	}
	int key = 0;
	int counter = 1;
	bool found = false;
	while (head != NULL) {
		if (choice == Title || choice == Actor || choice == Genre ) {
			if (head->title == input || lead->leadActor == input || genre->genre == input
				|| altGenres->alternativeGenre == input || support->supportActor == input) {
				if (key == 0) {
					if (head->title == input) {
						oFile << "Search by title for " << input << " found:\n";
						oFile << "MOVIE #  TITLE                                                    YEAR RATING GENRE             ALT GENRE         LEAD ACTOR          SUPPORTING ACTOR" << endl;
						oFile << "------- --------------------------------------------------------- ---- ------ ----------------- ----------------- ------------------- -------------------" << endl;
						key++;
					}
					else if (lead->leadActor == input) {
						oFile << "Search by actor for " << input << " found:\n";
						oFile << "MOVIE #  TITLE                                                    YEAR RATING GENRE             ALT GENRE         LEAD ACTOR          SUPPORTING ACTOR" << endl;
						oFile << "------- --------------------------------------------------------- ---- ------ ----------------- ----------------- ------------------- -------------------" << endl;
						key++;
					}
					else if (genre->genre == input) {
						oFile << "Search by genre for " << input << " found:\n";
						oFile << "MOVIE #  TITLE                                                    YEAR RATING GENRE             ALT GENRE         LEAD ACTOR          SUPPORTING ACTOR" << endl;
						oFile << "------- --------------------------------------------------------- ---- ------ ----------------- ----------------- ------------------- -------------------" << endl;
						key++;
					}
					else if (altGenres->alternativeGenre == input) {
						oFile << "Search by alternative genre for " << input << " found:\n";
						oFile << "MOVIE #  TITLE                                                    YEAR RATING GENRE             ALT GENRE         LEAD ACTOR          SUPPORTING ACTOR" << endl;
						oFile << "------- --------------------------------------------------------- ---- ------ ----------------- ----------------- ------------------- -------------------" << endl;
						key++;
					}
					else if (support->supportActor == input) {
						oFile << "Search by support actor for " << input << " found:\n";
						oFile << "MOVIE #  TITLE                                                    YEAR RATING GENRE             ALT GENRE         LEAD ACTOR          SUPPORTING ACTOR" << endl;
						oFile << "------- --------------------------------------------------------- ---- ------ ----------------- ----------------- ------------------- -------------------" << endl;
						key++;
					}
				}
				found = true;
				oFile << "  " << setw(4) << left << counter << "  " << setw(58) << left << head->title << setw(7) << left << year->year << setw(4) << left << rating->rating
					<< " " << setw(17) << left << genre->genre << " " << setw(17) << left << altGenres->alternativeGenre << " " << setw(19) << left << lead->leadActor << " "
					<< support->supportActor << endl;
				counter++;
				head = head->next;
				lead = lead->next;
				year = year->next;
				rating = rating->next;
				genre = genre->next;
				support = support->next;
				altGenres = altGenres->next;

			} else {
				head = head->next;
				lead = lead->next;
				year = year->next;
				rating = rating->next;
				genre = genre->next;
				support = support->next;
				altGenres = altGenres->next;
			}
		} else if (choice == Year || choice == Rating) {
			if (year->year == yearOrRating || rating->rating == yearOrRating) {
				if (key == 0) {
					if (year->year == yearOrRating) {
						oFile << "Search by year for " << yearOrRating << " found:\n";
						oFile << "MOVIE #  TITLE                                                    YEAR RATING GENRE             ALT GENRE         LEAD ACTOR          SUPPORTING ACTOR" << endl;
						oFile << "------- --------------------------------------------------------- ---- ------ ----------------- ----------------- ------------------- -------------------" << endl;
						key++;
					}
					else  if (rating->rating == yearOrRating) {
						oFile << "Search by rating for " << yearOrRating << " found:\n";
						oFile << "MOVIE #  TITLE                                                    YEAR RATING GENRE             ALT GENRE         LEAD ACTOR          SUPPORTING ACTOR" << endl;
						oFile << "------- --------------------------------------------------------- ---- ------ ----------------- ----------------- ------------------- -------------------" << endl;
						key++;
					}
					
				}
				found = true;
				oFile << "  " << setw(4) << left << counter << "  " << setw(58) << left << head->title << setw(7) << left << year->year << setw(4) << left << rating->rating
					<< " " << setw(17) << left << genre->genre << " " << setw(17) << left << altGenres->alternativeGenre << " " << setw(19) << left << lead->leadActor << " "
					<< support->supportActor << endl;
				counter++;
				head = head->next;
				lead = lead->next;
				year = year->next;
				rating = rating->next;
				genre = genre->next;
				support = support->next;
				altGenres = altGenres->next;

			}
			else {
				head = head->next;
				lead = lead->next;
				year = year->next;
				rating = rating->next;
				genre = genre->next;
				support = support->next;
				altGenres = altGenres->next;
			}
		}
		
	}
	oFile << endl;
	if (found != true) {
		if (choice == Title) {
			cout << "\n********** MOVIE WITH TITLE \"" << input <<"\" NOT FOUND **********\n";
		}
		else if (choice == Actor) {
			cout << "\n********** ACTOR WITH NAME \"" << input << "\" NOT FOUND **********\n";
		}
		else if (choice == Genre) {
			cout << "\n********** GENRE \"" << input << "\" NOT FOUND **********\n";
		}
		else if (choice == Year) {
			cout << "\n********** MOVIES WITH YEAR \"" << yearOrRating << "\"NOT FOUND **********\n";
		}
		else if (choice == Rating) {
			cout << "\n********** MOVIES WITH RATING \"" << yearOrRating << "\" NOT FOUND **********\n";
		}
		
	}
	else {
		if (choice == Title) {
				cout << "\n********** MOVIE WITH TITLE \"" << input << "\" FOUND **********\n";
		} else if (choice == Actor) {
			if (counter > 2) {
				cout << "\n********** ACTORS WITH NAME \"" << input << "\" FOUND **********\n";

			} else {
				cout << "\n********** ACTOR WITH NAME \"" << input << "\" FOUND **********\n";
			}
		}
		else if (choice == Genre) {
			if (counter > 2) {
				cout << "\n********** \"" << input << "\" MOVIES FOUND **********\n";
			}else {
				cout << "\n********** \"" << input << "\" MOVIE FOUND **********\n";
			}
		}
		else if (choice == Year) {
			if (counter > 2) {
				cout << "\n********** MOVIES WITH YEAR \"" << yearOrRating << "\" FOUND **********\n";

			} else {
				cout << "\n********** MOVIE WITH YEAR \"" << yearOrRating << "\" FOUND **********\n";

			}
		}
		else if (choice == Rating) {
			if (counter > 2) {
				cout << "\n********** MOVIES WITH RATING \"" << yearOrRating << "\" FOUND **********\n";
			}
			else {
				cout << "\n********** MOVIE WITH RATING \"" << yearOrRating << "\" FOUND **********\n";
			}
		}
	}
}

void ListAllMovies(titles* head, years* year, ratings* rating, genres* genre,
	alternativeGenres* altGenres, leadingActors* lead, supportActors* support, ofstream& oFile) {
	
		cout << endl << "Listing all movies!" << endl << endl;
		int key = 1;
		oFile << "COMPLETE MOVIE LISTING" << endl;
		oFile << "MOVIE #  TITLE                                                    YEAR RATING GENRE             ALT GENRE         LEAD ACTOR          SUPPORTING ACTOR" << endl;
		oFile << "------- --------------------------------------------------------- ---- ------ ----------------- ----------------- ------------------- -------------------" << endl;

		while (head != NULL) {
			oFile << "  " << setw(4) << left << key << "  " << setw(58) << left << head->title << setw(7) << left << year->year << setw(4) << left << rating->rating
				  << " " << setw(17) << left << genre->genre << " " << setw(17) << left << altGenres->alternativeGenre << " " << setw(19) << left << lead->leadActor << " "
				  << support->supportActor << endl;
			key++;
			head = head->next;
			lead = lead->next;
			year = year->next;
			rating = rating->next;
			genre = genre->next;
			support = support->next;
			altGenres = altGenres->next;
		}
		oFile << endl;
}