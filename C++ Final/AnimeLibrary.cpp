/**************************************
** John Velazquez
** Final Project
***************************************
** Program that creates a Library
** for Anime.
** Allows you to add, delete, and search 
** for Anime within the library.
***************************************/
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
using namespace std;

//Function prototypes
char menu();  
void displayAnime(string animeFile, string studioile);
void addAnime(string animeFile, string studioFile);
void searchAnime(string animeFile, string studioFile);
void deleteAnime(const char *animeFile, const char *studioFile);

//Main Function runs the program
int main()
{
	// Variables declared in Main
	char choice;
	bool notValid = true;
	bool open = true;
	string animesFile = "Animes.dat";
	string studiosFile = "Studios.dat";
	
	ifstream inputStudio;
	ofstream outputStudio;
	
	
	//Takes the input from the menu function and runs a function based on the choice
	do
	{
		choice = menu();
		
		switch(toupper(choice))
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

//Menu function actually displays the menu choices to the user and returns the input by user
char menu()
{
	char menuChoice;
	
	cout << "Enter the letter for the menu option you want:" << endl;
	cout << "A. Display Watched Anime" << endl;
	cout << "B. Search Anime" << endl;
	cout << "C. Add Anime" << endl;
	cout << "D. Delete Anime" << endl;
	cout << "X. Quit Program\n" << endl;
				
	cin >> menuChoice;
	cin.ignore(256, 10);
	
	cout << "\n" << endl;
	return menuChoice;
}

//displayAnime function displays the Animes side by side with the Studios for each anime from their respective .dat files
void displayAnime(string animeFile, string studioFile)
{
	ifstream inputAnime;
	ifstream inputStudio;
	string anime;
	string studio;
	
	//opens anime file
	inputAnime.open(animeFile);
	
	if(inputAnime)
	{
		inputStudio.open(studioFile);
		{
			if(inputStudio)
			{
				//outputs the current line of both files
				while(getline(inputAnime, anime) && getline(inputStudio, studio))
				{
					cout << anime << ", " <<  studio << endl;
				}
			}
		}
	}
	//Error message
	else
	{
		cout << "File doesn't exist... " << endl;
	}
		
	inputAnime.close();
	inputStudio.close();
	
	cout << "\n" << endl;
}

//addAnime function adds Anime/Studio input from the user to their respective .dat files
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
			
			//Error message
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
		//Error message
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
/*
	searchAnime function takes user input and searches the Animes.dat file and looks for matching titles 
	and returns the matching Anime and Studio if there are any. This function is case sensitive so inputting
	"Naruto" and "naruto" will return different results. If the search function finds an anime it will also
	return the line number which is used for deletion.

*/
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
		cout << "Enter anime title (Case Sensitive): " << endl;
		getline(cin, anime);
		
		//Error message
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
	
	//open Files
	inputAnime.open(animeFile);
	inputStudio.open(studioFile);
	for(int i = 0; getline(inputAnime, line); i++)
	{
		for(int j = 0; getline(inputStudio, line2); j++)
		{
			//if anime found returns the current line of Animes.dat and Studios.dat
			if(line.find(anime) != string::npos)
			{
				cout << "\nFound: " << line << ", " << line2 << "\nLine: " << i << endl;
				count++;
			}
			break;
		}
	}
	
	cout << "\n\n";
	
	//close files
	inputAnime.close();
	inputStudio.close();
	
	if(count == 0)
		cout << "Could not find the Anime \"" << anime << "\"\n" << endl;
}

//deleteAnime delets an Anime and its Studio given the line number of the .dat file
void deleteAnime(const char *animeFile, const char *studioFile)
{
	string choice = "N";
	int n;
	do{
		
		cout << "Enter Line No. to delete (if you'd like to quit type 'Y'): ";
		cin >> choice;
		if(choice == "Y" || choice == "y")
			exit(0);
	}while((choice == "N" || choice == "n"));
	
	stringstream num(choice);
	num >> n;
	
	cout << "Deleting..." << endl;
	//open files in read mode or in mode 
    ifstream is(animeFile);
	ifstream is2(studioFile); 
  
    //open files in write mode or out mode 
    ofstream ofs; 
    ofs.open("tempAnime.txt", ofstream::out); 
	ofstream ofs2; 
    ofs2.open("tempStudio.txt", ofstream::out); 
	
    char c; 
	char c2; 
    int line_no = 0; 
    while(is.get(c)) 
    { 
        //if a newline character 
        if (c == '\n') 
        line_no++; 
  
        //file content not to be deleted 
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
	
	//closing output files
    ofs.close();
	ofs2.close(); 
	
    //closing input files
    is.close();
	is2.close(); 
  
    //remove the original files
    remove(animeFile);
	remove(studioFile);
  
    //rename the files
    rename("tempAnime.txt", animeFile);
	rename("tempStudio.txt", studioFile); 
	
	cout << "Finished deleting\n" << endl;
}