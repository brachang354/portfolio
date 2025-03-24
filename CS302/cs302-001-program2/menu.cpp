#include "menu.h"
//Bradley Chang CS302 Program #2 
//menu.cpp This will contain the menu class member function implementation

int menu::main_menu()
{
	int option {0};
	do
	{
		cout << "Welcome to the Great Monster Race!\n";
		cout << "Please pick what race you want to participate in: \n";
		cout << "1. Slime Race\n2. Zombie Race\n3. Dragon Race\n0. Quit Program\n";
		cin >> option;
		cin.ignore(100, '\n');
		switch(option)
		{
			case 1:
				cout << "Selected Slime Race\n";
				slime_menu();
				break;
			case 2:
				cout << "Selected Zombie Race\n";
				zombie_menu();
				break;
			case 3:
				cout << "Selected Dragon Race\n";
				dragon_menu();
				break;
			case 0:
				cout << "Quitting Program!\n";
				return 0;
				break;
			default:
				break;
		}
		cout << "Would you like to start the program again?\n";
	}while(again());
	
	return 0;
	
}
int menu::slime_menu()
{
	int option {0};
	int slime_count{0};
	do
	{
		cout << "SLIME RACE\n";
		cout << "Please pick an option: \n";
		cout << "1. Insert Slime Contestant\n2. Display all contestants\n3. Start Race\n0. Quit Slime Race\n";
		cin >> option;
		cin.ignore(100, '\n');
		switch(option)
		{
			case 1:
				cout << "Inserting slime contestant\n";
				cin >> slime_data;
				slime_obj.insert(slime_data);
				slime_obj.display();
				++slime_count;
				break;
			case 2:
				cout << "Displaying all contestants\n";
				slime_obj.display();
				break;
			case 3:
				cout << "Starting Race.\n";
				do
				{
					slime_obj.increment_distance();
					
					int index {0};
					while(index < slime_count /*&& !slime_obj.get_data(index).finish(1000)*/)
					{
						try
						{
							cout << "Contestant #" << index << endl;
							slime_obj.get_data(index).random_slime_event();
							cout << endl;
							++index;
						}
						catch(EMPTY)
						{
							cerr << "ERROR: Empty list" << endl;
						}
						catch(BAD_INDEX)
						{
							cerr << "ERROR: Bad Index" << endl;
						}
					}
					slime_obj.display();
				
					cout << "Continue race?\n";
				}while(again());
				/*catch(EMPTY)
				{
					cerr << "ERROR: Empty list" << endl;
				}*/
				break;
			default:
				break;
		}
	
		cout << "Would you like to do another slime race option?\n";
	}while(again());
	return 0;
}
int menu::zombie_menu()
{
	int option {0};
	int zombie_count {0};
	do
	{
		cout << "ZOMBIE RACE\n";
		cout << "Please Pick an Option\n";
		cout << "1. Insert Zombie\n2. Display Zombie Contestants\n3. Start Race\n0. Quit Zombie Race\n";
		cin >> option;
		cin.ignore(100, '\n');
		switch(option)
		{
			case 1:
				cout << "Inserting Zombie Contestant\n";
				cin >> zombie_data;
				zombie_obj.insert(zombie_data);
				zombie_obj.display();
				++zombie_count;

				break;

			case 2:
				cout << "Displaying all Zombies\n";
				zombie_obj.display();
				break;

			case 3:
				cout << "Starting Race" << endl;
				do
				{
					zombie_obj.increment_distance();
					int index {0};
					while(index < zombie_count)
					{
						try
						{
							cout << "Contestant #" << index << endl;
							zombie_obj.get_data(index).random_zombie_event();
							cout << endl;
							++index;
						}
						catch(EMPTY)
						{
							cerr << "ERROR: Empty list" << endl;
						}
						catch(BAD_INDEX)
						{
							cerr << "ERROR: Bad Index" << endl;
						}

					}
					zombie_obj.display();

					cout << "Continue Race?" << endl;
				}while(again());
				break;

			default:
				break;
		}
		cout << "Would you like to do another zombie race option?\n";
	}while(again());
	return 0;
}
int menu::dragon_menu()
{
	int option {0};
	int dragon_count {0};
	do
	{
		cout << "DRAGON RACE\n";
		cout << "Please select an option\n";
		cout << "1. Insert Dragon\n2. Display all dragons\n3. Start race\n0. Quit race\n";
		cin >> option;
		cin.ignore(100, '\n');	
		switch(option)
		{
			case 1:
				cout << "Inserting Dragon Contestant" << endl;
				cin >> dragon_data;
				dragon_obj.insert(dragon_data);
				dragon_obj.display();
				++dragon_count;
				break;
			case 2:
				cout << "Displaying all Dragons" << endl;
				dragon_obj.display();
				break;
			case 3:
				cout << "Starting Dragon Race" << endl;
				do
				{
					dragon_obj.increment_distance();
					int index {0};
					while(index < dragon_count)
					{
						try
						{
							cout << "Contestant #" << index << endl;
							dragon_obj.get_data(index).random_dragon_event();
							cout << endl;
							++index;
						}
						catch(EMPTY)
						{
							cerr << "ERROR: Empty list" << endl;
						}
						catch(BAD_INDEX)
						{
							cerr << "ERROR: Bad Index" << endl;
						}

					}
					dragon_obj.display();

					cout << "Continue Race?" << endl;
				}while(again());
				break;
			default:
				break;

		}

		cout << "Do another dragon race option?\n";
	}while(again());

	return 0;
}

menu::~menu()
{}

bool menu::again()
{                       
         char response {'n'};
         cout << "Y or N: ";
         cin >> response;
         cin.ignore(100, '\n');
         if (toupper(response) == 'Y')
                 return true;
         return false;
}
