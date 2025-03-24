#include "header.h"

//Constructor to zero out data values for activity data
activity::activity()
{
	actName[0] = '\0';
	location[0] = '\0';
	diff = 0;
	recom[0] = '\0';
	people = 0;
}
//Constructor for list which manages indexes for dynamically allocated activity array
list::list()
{
	activity * actList = nullptr;	//acList is the pointer to the activity array which is dynamic
	arraySize = 0;
	itemsStored = 0;
}
//Destructor to delete dynamically allocated array
list::~list()
{
	delete [] actList;
}
//Outputs welcome message
void activity::welcome()
{
	cout << "Welcome to the activity tracker." << endl;
}
//Asks user to choose the size of the array
int list::actAllocate()
{
	cout << "Choose size for the activity list: ";
	cin >> arraySize;
	cin.ignore(100, '\n');
	cout << endl;
	//actList = new activity[arraySize];
	return arraySize;
}
//Allows user to store activity information in array
void activity::newActivity()
{
	cout << "Enter name of activity: ";
	cin.get(actName, SIZE, '\n');
	cin.ignore(100, '\n');

	cout << "Enter location of activity: ";
	cin.get(location, SIZE, '\n');
	cin.ignore(100, '\n');

	cout << "Enter difficulty of activity(1-10): ";
	cin >> diff;
	cin.ignore(100, '\n');

	cout << "Enter recommendations for activity: ";
	cin.get(recom, SIZE, '\n');
	cin.ignore(100, '\n');

	cout << "Enter how many people will participate: ";
	cin >> people;
	cin.ignore(100, '\n');
}
//Displays everyting in the array
void activity::display()
{
	cout << "Activity: " <<actName << endl;
	cout << "Location: " << location << endl;
	cout << "Difficulty: " << diff << endl;
	cout << "Recommendations: " << recom << endl;
	cout << "Number of people involved: " << recom << endl << endl;
}
//User enters in diffculty of activities they want to see and displays them
int activity::displayDiff()
{
	int userDiff {0};
	cout << "What difficulty do you want to display?: ";
	cin >> userDiff;
	cin.ignore(100, '\n');
	return userDiff;
}
//Asks user if they want to do something again
bool activity::again()
{
	char response {'n'};
	cout << "Do you want to enter again? (y/n): ";
	cin >> response;
	cin.ignore(100, '\n');
	if (toupper(response) == 'Y')
		return true;
	return false;
}

