#include "graph.h"

using namespace std;

//Bradley Chang CS163_001 Program 5. Purpose of this file is to contain the main menu, and test out all public member functions

int main()
{
	table my_table;
	route my_route;
	string curr_loca;
	string attach_loca;
	int menu {0};

	do
	{
		cout << "Welcome! Select what you want to do" << endl;
		cout << "1. Quit \n2. Insert vertices \n3. Connect one location to another" << endl;
		cin >> menu; cin.ignore(100, '\n');
		if(menu == 1)
		{
			cout << "Quitting program" << endl;
			return 0;
		}
		else if(menu == 2)
		{
			do
			{
				cout << "Input location: " << endl;
				getline(cin, my_route.location);
				cout << "Input description: " << endl;
				getline(cin, my_route.desc);
				my_table.insert_vertex(my_route);
				my_table.display_adjacent();
				cout << "Add another?" << endl;
			}while(again());
		}
		else if(menu == 3)
		{
			do
			{
				cout << "Input starting location" << endl;
				getline(cin, curr_loca);
				cout << "Input destination location" << endl;
				getline(cin, attach_loca);
				my_table.insert_edge(curr_loca, attach_loca);
				my_table.display_adjacent();
				cout << "Add another connection?" << endl;
			}while(again());
		}

		cout << "Do another task?" << endl;
	}while(again());
	return 0;
}
