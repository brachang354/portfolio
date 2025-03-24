//Bradley Chang CS302 menu functions
//Purpose of this file is to contain the main menu functions
#include "menu.h"
using namespace std;
const int MAX = 1000;
menu::menu()
{}
menu::~menu()
{}
int menu::main_menu()
{
	int option {0};
	do
	{
		cout << "Select what activity you'd like to do" << endl;
		cout << "1. Corn Maze\n2. Egg Hunt\n3. Berry Picking\n0. Exit Program" << endl;
		cin >> option; 
		cin.ignore(MAX, '\n');
		if(option == 1)
		{
			cout << "Selected Corn Maze" << endl;
			corn_menu();
		}	
		else if(option == 2)
		{	
			cout << "Selected Egg Hunt" << endl;
			egg_menu();
		}
		else if(option == 3)
		{
			cout << "Selected Berry Picking" << endl;
			berry_menu();
		}
		else if(option == 0)
		{
			cout << "Exiting Program" << endl;
			return 0;
		}
		cout << "Do another activity?" << endl;
	}while(again());
	cout << "Exiting program" << endl;
	return 0;
}

int menu::corn_menu()
{
	int option {0};

	char temp[MAX];
	char * guest_name = nullptr;	//Name of activity
	int schedule_time {0};	//Scheduled time of activity
	int cost {0};		//Fee of activity that customers pay
	int stamps {0};	//Amount of stamps
	int time {0};	//Amount of time spent in maze
	int difficulty{0};	//Difficulty of maze

	//corn_maze corn(guest_name, schedule_time, cost, stamps, time, difficulty);		
	do
	{
		cout << "Select Corn Action " << endl;
		cout << "1. Add a guest\n2. Remove oldest guest\n3. Display all guests\n4. Start maze run\n5. Delete all guests\n";
		cin >> option;
		cin.ignore(100, '\n');
		switch (option)
		{
			case 1:
			{
			
				cout << "Adding a guest: " << endl;

				cout << "Insert Guest name: " << endl;
				cin.get(temp, MAX, '\n'); 
				cin.ignore(MAX, '\n');
				if(guest_name)
					delete [] guest_name;

				guest_name = new char[strlen(temp) +1];
				strcpy(guest_name, temp);

				cout << "Insert Schedule time: " << endl;
				cin >> schedule_time; 
				cin.ignore(MAX, '\n');

				cout << "Insert Cost: " << endl;
				cin >> cost; 
				cin.ignore(MAX, '\n');

				cout << "Insert Stamps: " << endl;
				cin >> stamps; 
				cin.ignore(MAX, '\n');

				cout << "Insert Maze time: " << endl;
				cin >> time; 
				cin.ignore(MAX, '\n');

				cout << "Insert Maze difficulty: " << endl;
				cin >> difficulty; 
				cin.ignore(MAX, '\n');

				corn_maze corn(guest_name, schedule_time, cost, stamps, time, difficulty);		
				CLL.enqueue(corn);
				
				CLL.display();		
				
				break;
			}
			
			case 2:
				cout << "Removing oldest guest: " << endl;
				CLL.dequeue();
				CLL.display();
				break;
			case 3:
				cout << "Display all guests: " << endl;
				CLL.display();			
				break;
			case 4:
				cout << "Start a maze run: " << endl;
				break;
			case 5:
				cout << "Removing all items: " << endl;
				CLL.remove_all();
				CLL.display();
				break;
			default:
				cout << "Exiting corn maze: " << endl;
				break;
		}
		cout << "Do another corn option?" << endl;
	}while(again());

	return 1;
}

int menu::egg_menu()
{
	return 0;
}

int menu::berry_menu()
{
	int option{0};
	//vector <berry_picking> v_berry;
	
	char temp[MAX];
	char * guest_name = nullptr;	//Name of activity
	int schedule_time {0};	//Scheduled time of activity
	int cost {0};		//Fee of activity that customers pay
	string type;		//Berry type
	int b_count {0};	//Berry count
	int b_weight {0};	//Berry weight
	do
	{
		cout << "Select berry picking option. " << endl;
		cout << "1. Add a guest\n2. Remove a guest\n3. Display all guests\n4. Start berry picking\n5. Remove all items.\n0. Exit berry picking\n";
		cin >> option;
		cin.ignore(MAX, '\n');
		switch(option)
		{
			case 1:
			{
				cout << "Adding a guest: " << endl;
				cout << "Insert Guest name: " << endl;
				cin.get(temp, MAX, '\n'); 
				cin.ignore(MAX, '\n');
				if(guest_name)
					delete [] guest_name;

				guest_name = new char[strlen(temp) +1];
				strcpy(guest_name, temp);

				cout << "Insert Schedule time: " << endl;
				cin >> schedule_time; 
				cin.ignore(MAX, '\n');

				cout << "Insert Cost: " << endl;
				cin >> cost; 
				cin.ignore(MAX, '\n');
		
				cout << "Insert berry type: " << endl;
				getline(cin, type);
				//cin.ignore(MAX, '\n');
				
				cout << "Insert berry count: " << endl;
				cin >> b_count;
				cin.ignore(MAX, '\n');
			
				cout << "Insert berry weight: " << endl;
				cin >> b_weight;
				cin.ignore(MAX, '\n');
				
				berry_picking berry(guest_name, schedule_time, cost, type, b_count, b_weight);
				v_berry.push_back(berry);

				break;
			}
			case 2:
			{
				cout << "Insert index of guest to remove: " << endl;
				int index_input {0};
				int index{0};
				auto i = v_berry.begin();
				cin >> index_input;
				cin.ignore(MAX,'\n');
				while(index != index_input && i != v_berry.end())
				{
					++index;
					++i;
				}
				if(index == index_input)
				{
					v_berry.erase(i);
				}
				else
					cout << "No matching index to remove. Please try again. " << endl;

				
				break;
			}
			case 3:
			{
				if(v_berry.empty())
				{
					cout << "Empty guest list!" << endl;
					break;
				}
				cout << "Displaying all guests: " << endl;
				int index {0};
				auto i = v_berry.begin();
				while(i != v_berry.end())
				//for(auto i = v_berry.begin(); i != v_berry.end(); ++i)
				{
					cout << "Index: " << index << endl;
					i->display();
					cout << endl;
					++i;
					++index;
				}
				break;
			}
			case 4:
				cout << "Start berry picking: " << endl;
				break;
			case 5:
				cout << "Removing all items" << endl;
				v_berry.clear();
				/*while(!v_berry.empty())
				{
					v_berry.pop_back();
				}*/
				break;
			default:
				cout << "Exiting berry picking" << endl;
				break;
		}
		cout << "Do another berry option?" << endl;
	}while(again());

	return 1;
}
