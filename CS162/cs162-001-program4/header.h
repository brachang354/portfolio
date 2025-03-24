//Bradley Chang CS162_001 Program 4
//Purpose of this program is to be an activity tracker in where
//the user can input activities and keep track of them.

#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

const int SIZE {51};

class activity
{
	public:	//function prototypes go here
		activity();		//constructor
		void welcome();		//Welcome message for user
		void newActivity();	//User inputs activities into activity list
		void display();		//Displays all info from activity list
		int displayDiff();	//User enters difficulty, displays all info with that difficulty only
		bool again();		//asks user to do something again
		
		int diff;		//Difficulty of acitivity
	private: // data types go here
		char actName[SIZE];	//Name of acitivity
		char location[SIZE];	//Location of acitivity
		char recom [SIZE];	//Recommendations for activity
		int people;		//Number of people participating in activity
};

class list
{
	public:
		list();
		~list();

		int actAllocate();	//Asks user how big they want their array
	private:
		activity * actList;	//pointer for activity class, the activity list
		
		int arraySize;		//Size of array once allocated
		int itemsStored;	//Number of items stored in array
};






