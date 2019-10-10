/**************************************
** John Velazquez
** Final Project
***************************************
** Program that creates a Library
** for watched and planned to watch
** anime. 
**
** The Program will have an add, delete
** display, and search function
***************************************/
#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;

char menu();  
void displayAnime(string animeFile, string studioile);
void addAnime(string animeFile, string studioFile);
void searchAnime(string animeFile, string studioFile);
void deleteAnime(const char *animeFile, const char *studioFile);

//C:\Users\John\Documents\pocketcpp\QuickStart\C++ MidTerm

int main()
{
	// Variable Declared in Main
	char choice;
	bool notValid = true;
	bool open = true;
	string animesFile = "Animes.dat";
	string studiosFile = "Studios.dat";
	
	ifstream inputStudio;
	ofstream outputStudio;
	
	
	//Displays the menu choices
	do
	{
		choice = menu();
		
		switch (toupper(choice))
		{
			
			case 'A':
				//Displays Anime in your watched library
				system ("CLS");
				displayAnime(animesFile, studiosFile);
				break;
				
			case 'B':
				//Searches for an Anime in your watched Library
				system ("CLS");
				searchAnime(animesFile, studiosFile);
				break;
				
			case 'C':
				//Adds Anime to the Library
				system ("CLS");
				addAnime(animesFile, studiosFile);
				break;
			case 'D':
				//Deletes Anime from the Library
				system ("CLS");
				deleteAnime("Animes.dat", "Studios.dat");
				break;
				
			case 'X':
				//Closes the program down
				system ("CLS");
				cout << "Exiting Program..." << endl;
				open = false;
				break;
				
			default:
				//Default error message
				system ("CLS");
				cout << "Please pick a choice from the menu below...\n\n" << endl;
		}
		
		
	} while(open);
	
	
	
	
	return 0;
}

char menu()
{
	char menuChoice;
	
	cout << "Enter the letter for the menu option you want:" << endl;
	cout << "A. Display Watched Anime" << endl;
	cout << "B. Search Anime" << endl;
	cout << "C. Add Anime" << endl;
	cout << "D. Delete Anime" << endl;
	cout << "X. Quit Program" << endl;
				
	cin >> menuChoice;
	cin.ignore(256, 10);
	
	cout << "\n" << endl;
	return menuChoice;
}

void displayAnime(string animeFile, string studioFile)
{
	ifstream inputAnime;
	ifstream inputStudio;
	string anime;
	string studio;
	
	inputAnime.open(animeFile);
	
	if(inputAnime)
	{
		inputStudio.open(studioFile);
		{
			if(inputStudio)
			{
				while(getline(inputAnime, anime) && getline(inputStudio, studio))
				{
					cout << anime << ", " <<  studio << endl;
				}
			}
		}
	}
	else
	{
		cout << "File doesn't exist... " << endl;
	}
		
	inputAnime.close();
	inputStudio.close();
	
	cout << "\n" << endl;
}

void addAnime(string animeFile, string studioFile)
{
	ofstream outputAnime;
	ofstream outputStudio;
	string anime;
	string studio;
	string addAnother;
	
	do
	{
		do
		{
			cout << "Enter anime title: " << endl;
			getline(cin, anime);
			
			if(anime == "")
			{
				cout << "There was an error entering the anime" << endl; 
				cout << "If you'd like to quit type 'Y' if not type 'N': " << endl;
				getline(cin, addAnother);
				//cin.ignore(256, 10);
				if(addAnother == "Y" || addAnother == "y")
					exit(0);
			}
		}while(anime == "" && (addAnother != "Y" || addAnother != "y"));
		
	
		cout << "Enter the studio name for " << anime << ": " << endl;
		getline(cin, studio);
		outputAnime.open(animeFile, ofstream::out | ofstream::app);
		outputStudio.open(studioFile, ofstream::out | ofstream::app);
		
		if(outputAnime && outputStudio)
		{
			outputAnime << anime << endl;
			outputStudio << studio << endl;
			cout << "Would you like to add another anime? (Y/N): ";
			getline(cin, addAnother);
		}
		else
		{
			cout << "Error adding anime: " << endl;
			cout << "If you'd like to quit type 'Y' if not type 'N': ";
			getline(cin, addAnother);
		}
		outputAnime.close();
		outputStudio.close();
	} while(addAnother == "Y" || addAnother == "y");
	cout << "\n\n" << endl;
}

void searchAnime(string animeFile, string studioFile)
{
	ifstream inputAnime;
	ifstream inputStudio;
	string line;
	string line2;
	string anime;
	string addAnother = "N";
	int count = 0;

	do
	{
		cout << "Enter anime title: " << endl;
		getline(cin, anime);
		
		if(anime == "")
		{
			cout << "There was an error entering the anime" << endl; 
			cout << "If you'd like to quit type 'Y' if not type 'N': " << endl;
			getline(cin, addAnother);
			//cin.ignore(256, 10);
			if(addAnother == "Y" || addAnother == "y")
				exit(0);
		}
	}while(anime == "" && (addAnother != "Y" || addAnother != "y"));
	
	inputAnime.open(animeFile);
	inputStudio.open(studioFile);
	for(int i = 0; getline(inputAnime, line); i++)
	{
		for(int j = 0; getline(inputStudio, line2); j++)
		{
			if(line.find(anime) != string::npos)
			{
				cout << "\nFound: " << line << ", " << line2 << "\nLine: " << i << endl;
				count++;
			}
			break;
		}
	}
	
	cout << "\n\n";
	
	inputAnime.close();
	inputStudio.close();
	
	if(count == 0)
		cout << "Could not find the Anime \"" << anime << "\"\n" << endl;
}

void deleteAnime(const char *animeFile, const char *studioFile)
{
	int n;
	cout << "Enter Line No. to delete: ";
	cin >> n;
	cout << "Deleting..." << endl;
	
	// open file in read mode or in mode 
    ifstream is(animeFile);
	ifstream is2(studioFile); 
  
    // open file in write mode or out mode 
    ofstream ofs; 
    ofs.open("tempAnime.txt", ofstream::out); 
	ofstream ofs2; 
    ofs2.open("tempStudio.txt", ofstream::out); 
	
    char c; 
	char c2; 
    int line_no = 0; 
    while(is.get(c)) 
    { 
        // if a newline character 
        if (c == '\n') 
        line_no++; 
  
        // file content not to be deleted 
        if (line_no != n) 
            ofs << c; 
    } 
    line_no = 0; 
    while (is2.get(c)) 
    { 
        if (c == '\n') 
        line_no++; 
        if (line_no != n) 
            ofs2 << c; 
    } 
	
	// closing output file 
    ofs.close();
	ofs2.close(); 
	
    // closing input file 
    is.close();
	is2.close(); 
  
    // remove the original file 
    remove(animeFile);
	remove(studioFile);
  
    // rename the file 
    rename("tempAnime.txt", animeFile);
	rename("tempStudio.txt", studioFile); 
	
	cout << "Finished deleting\n" << endl;
}