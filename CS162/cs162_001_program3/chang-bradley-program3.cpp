//Bradley Chang, CS162-001, Program #3
/*The purpose of this program is to allow the user to make a Comic Con event planner.
The program will create an external data file where the user can enter in the name
of the event, the celebrity they want to meet, their fan favorite, the time and day
of the event, and the description of what the user wants to do when they see their
celebrity. 

*/
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
using namespace std;
//Constants
const int SIZE {21};
const int EVENT {31};	//Max characters of event
const int NAME {31};	//Max characters of name
const int FAN {31};	//Max characters of fan favorite
const int MAX {255};	//Max characters for displaying data from external file
const int DATE {11};	//Max characters of date
const int DESC {51};	//Max chracters of description

//Constant file name
const char outfile[] = "eventdata.txt";

//Structure definitions go here
struct event
{
	char eventName[EVENT];
	char celeb[NAME];
	char fanFav[FAN];
	char date[DATE];
	char desc[DESC];
};

//Prototypes go here
void inputEventInfo(event & to_enter);
void display(event & eventInfo);
void writeExternal(event & eventInfo);
void displayExternal();
//int load(event allEvents[]);	//Count the number of events in file
//Main body
int main()
{

	//Creating variables here
	event eventInfo;
	int option {0};
	bool again;	
	char againOpt{' '};
	int numEvent {0};
	//Calling functions here
	cout << "Welcome to the comic con event planner.\n"
		<< "With this program you can input information about an event and store it\n"
		<< "in an external data file, or display all information from the file." << endl;
	
	cout << "Items in data file: " << numEvent << endl;

	again = true;
	
	

	while (again == true)
	{
		cout << "Choose what you like to do.\n"
			<< "1. Input information\n"
			<< "2. Display contents\n"
			<< "3. Quit" << endl;
		cout << "Option: ";
		cin >> option;
		cin.ignore(100, '\n');
	
		if(option == 1)	//Inputting information
		{
			
			cout << "Inputting information" << endl;
			inputEventInfo(eventInfo);
			display(eventInfo);
			writeExternal(eventInfo);
			
			cout << "Run program again? (y/n): ";
			cin >> againOpt;
			cin.ignore(100, '\n');
			if (againOpt == 'y')
			{
				again = true;
			}
			if (againOpt == 'n')
			{
				again = false;
				cout << "Exiting program" << endl;
			}
		}
		if(option == 2)	//Displaying information from external file
		{
			cout << "Displaying file contents" << endl;
			displayExternal();

			cout << "Run program again? (y/n): ";
			cin >> againOpt;
			cin.ignore(100, '\n');
			if (againOpt == 'y')
			{
				again = true;
			}
			if (againOpt == 'n')
			{
				again = false;
				cout << "Exiting program" << endl;
			}

		}
		if(option == 3)	//Quit program
		{
			cout << "Exiting program" << endl;
			again = false;
		}
	}

	return 0;
}

//Functions go here
void inputEventInfo(event & toEnter)
{
	cout << "Enter event name: ";
	cin.get(toEnter.eventName, EVENT, '\n');
	cin.ignore(100, '\n');

	cout << "Enter celebrity name: ";
	cin.get(toEnter.celeb, NAME, '\n');
	cin.ignore(100, '\n');

	cout << "Enter fan favorite: ";
	cin.get(toEnter.fanFav, FAN, '\n');
	cin.ignore(100, '\n');

	cout << "Enter date of event (MM/DD/YYYY): ";
	cin.get(toEnter.date, DATE, '\n');
	cin.ignore(100, '\n');

	cout << "Enter description of what you want to do: ";
	cin.get(toEnter.desc, DESC, '\n');
	cin.ignore(100, '\n');

}
void display(event & eventInfo)
{
	cout << "Displaying event information entered..." << endl
	<< "Event name: " << eventInfo.eventName << endl
	<< "Celebrity name: " << eventInfo.celeb << endl
	<< "Fan Favorite: " << eventInfo.fanFav << endl
	<< "Date: " << eventInfo.date << endl
	<< "Description: " << eventInfo.desc << endl;
}
void writeExternal(event & eventInfo)
{

	//Writing to external data file
	ofstream fileOut;	//File variable for output
	
	fileOut.open(outfile, ios::app);	//Opening data file
	if (fileOut)
	{
		fileOut << eventInfo.eventName << ":"	//Outputting event info to external file
			<< eventInfo.celeb << ":"
			<< eventInfo.fanFav << ":"
			<< eventInfo.date << ":"
			<< eventInfo.desc << endl;

		fileOut.close();	//Closing external file
		fileOut.clear();
	}
}
void displayExternal()
{

	//Opening external data file to display contents
	char line[MAX];
	char delimiter;
	ifstream fileIn;	//File variable for input
	fileIn.open(outfile);

	if (fileIn)
	{
		fileIn.get(line, MAX, '\n');
		while (fileIn && !fileIn.eof())
		{
			//delimiter = fileIn.get();
			cout << line << endl;
			fileIn.ignore(100,'\n');

			fileIn.get(line, MAX, '\n');

		}
	fileIn.close();
	fileIn.clear();	
	}
}

