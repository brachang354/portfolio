#include "table.h"

using namespace std;
//Bradley Chang CS163_001 Program #4. Purpose of this file is to test out our table functions by calling them in each menu option.

int main()
{	
	animal my_animal;
	table my_table;
	int menu {0};
	do
	{
		cout << "Welcome, what would you like to do?" << endl;
		cout << "1. Quit \n2. Add animal \n3. Remove animal \n4. Retrieve animal \n5. Remove all data \n6. Display life span range" << endl;
		cin >> menu; cin.ignore(100, '\n');
		if (menu == 1)
		{
			cout << "Quitting program!" << endl;
			return 0;
		}
		else if(menu == 2)
		{
			my_animal.name = new char[SIZE];
                        my_animal.sci_name = new char[SIZE];
                        my_animal.location = new char[SIZE];
                        my_animal.desc = new char[SIZE];
                        my_animal.population = new char[SIZE];
                        //my_animal.life_span = new char[SIZE];

                        cout << "Insert name: " << endl;
                        cin.get(my_animal.name, SIZE, '\n'); cin.ignore(100, '\n');
                        cout << "Insert Sci name: " << endl;
                        cin.get(my_animal.sci_name, SIZE, '\n'); cin.ignore(100, '\n');
                        cout << "Insert location: " << endl;
                        cin.get(my_animal.location, SIZE, '\n'); cin.ignore(100, '\n');
                        cout << "Insert desc: " << endl;
                        cin.get(my_animal.desc, SIZE, '\n'); cin.ignore(100, '\n');
                        cout << "Insert population: " << endl;
                        cin.get(my_animal.population, SIZE, '\n'); cin.ignore(100, '\n');
                        cout << "Insert life span: " << endl;
                        //cin.get(my_animal.life_span, SIZE, '\n'); cin.ignore(100, '\n');
			cin >> my_animal.life_span; cin.ignore(100, '\n');

			my_table.add_animal(my_animal);
			cout << "Displaying all data" << endl;
			my_table.display_all();
			cout << "Tree height: " << my_table.count_height() << endl;
			delete [] my_animal.name;
			delete [] my_animal.sci_name;
			delete [] my_animal.location;
			delete [] my_animal.desc;
			delete [] my_animal.population;
			//delete [] my_animal.life_span;
		}
		else if(menu == 3)
		{
			int remove {0};
			char * name_to_remove;
			name_to_remove = new char[SIZE];
			cout << "Insert animal's name to remove: " << endl;
			cin.get(name_to_remove, SIZE, '\n'); cin.ignore(100,'\n');

			remove = my_table.remove_animal(name_to_remove);
			if (remove == 4)
				cout << "Node has two children and right child is IOS" << endl;
			cout << "Displaying all data" << endl;
			my_table.display_all();
			cout << "Tree height: " << my_table.count_height() << endl;
			delete [] name_to_remove;
		}
		else if(menu == 4)
		{
			my_animal.name = new char[SIZE];
                        my_animal.sci_name = new char[SIZE];
                        my_animal.location = new char[SIZE];
                        my_animal.desc = new char[SIZE];
                        my_animal.population = new char[SIZE];
                        //my_animal.life_span = new char[SIZE];
			char * name_to_find;
			name_to_find = new char[SIZE];
			
			cout << "Insert animal's name to retrieve: " << endl;
			cin.get(name_to_find, SIZE, '\n'); cin.ignore(100, '\n');
			if(!my_table.retrieve_animal(name_to_find, my_animal))
				cout << "No match found" << endl;
			else
			{
				cout << "Displaying retrieved info: " << endl;
				cout << "-Name: " << my_animal.name << endl;
				cout << "-Sci Name: " << my_animal.sci_name << endl;
				cout << "-Location: " << my_animal.location << endl;
				cout << "-Desc: " << my_animal.desc << endl;
				cout << "-Population: " << my_animal.population << endl;
				cout << "-Life Span: " << my_animal.life_span << endl << endl;
			}
			delete [] my_animal.name;
			delete [] my_animal.sci_name;
			delete [] my_animal.location;
			delete [] my_animal.desc;
			delete [] my_animal.population;
			//delete [] my_animal.life_span;	
			delete [] name_to_find;
		}
		else if(menu == 5)
		{
			cout << "Removing all data" << endl;
			cout << "Nodes removed: " << my_table.remove_all() << endl;
			my_table.display_all();
		}
		else if(menu == 6)
		{
			//char * start; char * end;
			//start = new char[SIZE]; end = new char[SIZE];
			int start {0}; int end {0};

			cout << "Insert starting life span: " << endl;
			//cin.get(start, SIZE, '\n'); cin.ignore(100, '\n');
			cin >> start; cin.ignore(100, '\n');
			cout << "Insert ending life span: " << endl;
			//cin.get(end, SIZE, '\n'); cin.ignore(100, '\n');
			cin >> end; cin.ignore(100, '\n');
			cout << "Displaying all animals between " << start << "and " << end << endl;
			my_table.display_life_range(start, end);

			//delete [] start;
			//delete [] end;
		}
		cout << "Perform another task? " << endl;
	}while(again());


	return 0;
}
