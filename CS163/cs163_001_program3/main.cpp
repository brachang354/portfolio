#include "table.h"

using namespace std;
//Bradley Chang CS163_001 Program #3. This file contains a menu system that tests out all of the table function calls.

int main()
{
	int menu {0};
	animal my_animal;
	table my_table;

	do
	{
		cout << "Welcome, what would you like to do?" << endl;
		cout << "1. Quit \n2. Add animal \n3. Load file \n4. Find animal name \n5. Remove animal \n6. Retrieve animal \n7. Display by location" << endl;
		cin >> menu; cin.ignore(100, '\n');
		if(menu == 1)
		{
			cout << "Quitting Program!" << endl;
			return 0;
		}
		else if(menu == 2)	//Adding an animal into the table
		{	//Creates array for user to input info into
			my_animal.name = new char[SIZE];	
			cout << "Insert name: " << endl;
			cin.get(my_animal.name, SIZE, '\n'); cin.ignore(100, '\n');

			my_animal.sci_name = new char[SIZE];
			cout << "Insert Sci name: " << endl;
			cin.get(my_animal.sci_name, SIZE, '\n'); cin.ignore(100, '\n');
			
			my_animal.location = new char[SIZE];
			cout << "Insert location: " << endl;
			cin.get(my_animal.location, SIZE, '\n'); cin.ignore(100, '\n');
			
			my_animal.desc = new char[SIZE];
			cout << "Insert desc: " << endl;
			cin.get(my_animal.desc, SIZE, '\n'); cin.ignore(100, '\n');
			
			my_animal.population = new char[SIZE];
			cout << "Insert population: " << endl;
			cin.get(my_animal.population, SIZE, '\n'); cin.ignore(100, '\n');
			
			my_animal.life_span = new char[SIZE];
			cout << "Insert life span: " << endl;
			cin.get(my_animal.life_span, SIZE, '\n'); cin.ignore(100, '\n');
			
			my_table.add_animal(my_animal.name, my_animal);//Call the add animal function passing in the name and animal data.

			cout << "Displaying all data: " << endl;
			my_table.display_all();

			delete [] my_animal.name;	//Deletes all dynamic arrays for user input
			delete [] my_animal.sci_name;
			delete [] my_animal.location;
			delete [] my_animal.desc;
			delete [] my_animal.population;
			delete [] my_animal.life_span;
			
		}

		else if(menu == 3)	//Loads a external file
		{
			char * file_name;
			file_name = new char[SIZE];
			cout << "Insert file name: " << endl;
			cin.get(file_name, SIZE, '\n'); cin.ignore(100, '\n');
			
			my_table.load_file(file_name, my_animal, my_table);	//Calls load file function, passing in file name, animal object and table object
			
			cout << "Displaying all data: " << endl;
			my_table.display_all();	

			delete [] file_name;
		}
		
		else if(menu == 4)	//Finds an animal to display
		{
			char * name_to_find;
			name_to_find = new char[SIZE];
			cout << "Insert animal name to find (EXACT MATCHES ONLY, BE CAREFUL WITH SPACES AND CAPS): " << endl;
			cin.get(name_to_find, SIZE, '\n'); cin.ignore(100, '\n');
			my_table.display_animal(name_to_find);	//Calls display animal function passing in a name to find
			delete [] name_to_find;
		}
		else if (menu == 5)	//Finds an animal to remove
		{
			int match {0};
			char * name_to_find;
			name_to_find = new char[SIZE];
			cout << "Insert animal name to remove (EXACT MATCHES ONLY, BE CAREFUL WITH SPACES AND CAPS): " << endl;
			cin.get(name_to_find, SIZE, '\n'); cin.ignore(100, '\n');
			match = my_table.remove_animal(name_to_find);	//calls remove animal function passing in a name to find
			if(match)
			{
				cout << "Removal Successful" << endl;
				my_table.display_all();
			}
			else
				cout << "Error removal failed. No match found" << endl;

			delete [] name_to_find;
		}
		else if(menu == 6)	//Retrives an animal's info by name and copies it into the my_animal object.
		{
			int match {0};
			char * name_to_find;
			name_to_find = new char[SIZE];
			my_animal.name = new char[SIZE];
			my_animal.sci_name = new char[SIZE];
			my_animal.location = new char[SIZE];
			my_animal.desc = new char[SIZE];
			my_animal.population = new char[SIZE];
			my_animal.life_span = new char[SIZE];

			cout << "Insert animal name to retrieve (EXACT MATCHES ONLY, BE CAREFUL WITH SPACES AND CAPS): " << endl;
			cin.get(name_to_find, SIZE, '\n'); cin.ignore(100, '\n');
			match = my_table.retrieve_animal(name_to_find, my_animal);
			if(match)
			{
				cout << "Retrival Successful: Displaying retrived info" << endl;
					
				cout << "-Name: " << my_animal.name << endl;
				cout << "-Sci Name: " << my_animal.sci_name << endl;
				cout << "-Location: " << my_animal.location << endl;
				cout << "-Desc: " << my_animal.desc << endl;
				cout << "-Population: " << my_animal.population << endl;
				cout << "-Life Span: " << my_animal.life_span << endl;
			}
			else
				cout << "Error retrival failed. No match found" << endl;

			delete [] name_to_find;	
			delete [] my_animal.name;
			delete [] my_animal.sci_name;
			delete [] my_animal.location;
			delete [] my_animal.desc;
			delete [] my_animal.population;
			delete [] my_animal.life_span;
		}
		else if(menu == 7)	//Displays all animals with a matching location
		{
			char * loca_to_find;
			loca_to_find = new char[SIZE];
			cout << "Insert location to display (EXACT MATCHES ONLY, BE CAREFUL WITH SPACES AND CAPS): " << endl;
			cin.get(loca_to_find, SIZE, '\n'); cin.ignore(100, '\n');
			cout << "Displaying all matches for " << loca_to_find << endl;
			my_table.display_location(loca_to_find);
		}

		cout << "Perform another task?" << endl;
	}while(again());
	
	return 0;
}
