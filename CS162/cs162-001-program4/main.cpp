#include "header.h"

int main()
{
	//Create object of class, and variables
	activity * actList = nullptr; //Pointer for the activity list array
	list arrayList;
	int MAX {0};	//Size of the activity array
	int i {0};	//Current index in activity array for when storing items
	int j {0};	//Current index for when displaying items
	int n {0};	//Current index for when displaying items matching difficulty
	int userDiff {0};	//Difficulty user wants to search for
	//Function calls
	actList->welcome();
	MAX = arrayList.actAllocate(); //Sets MAX to the size of what the user wants for the array
	actList = new activity[MAX]; //Setting the size of activity list to size MAX
	
	//Loop for storing items in array
	if(i < MAX)
	{
		do
		{
			actList[i].newActivity();
			actList[i].display();
			++i;
		}while(i < MAX && actList->again());
	}

	//Loop for displaying all items in array
	cout << "Displaying all entered info" << endl;
	while (j < i)
	{
		actList[j].display();
		++j;
	}
	//Displaying all items in array that matches certain difficulty
	userDiff = actList->displayDiff();
	cout << "Displaying items of diffculty " << userDiff << ":" << endl;
	while (n < i)
	{
		if(actList[n].diff == userDiff)
		{
			actList[n].display();
		}
		++n;
	}

	//Deleting the actList array so memory can be used again
	delete [] actList;
	actList = nullptr;

	return 0;
}



