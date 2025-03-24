//Bradley Chang CS302 Program #3
//This file contains the implementation of the menu member functions to be used in main
#include "menu.h"

int menu::main_menu()
{
	int option{0};
	do
	{
		cout << "Welcome to the ice cream dessert tracker!" << endl;
		cout << "Please select an option." << endl;
		cout << "0. Quit\n1. Ice Cream Sandwich\n2. Ice Cream Cake\n3. Ice Cream Pancake\n4. Display all\n";
		cin >> option;
		cin.ignore(100, '\n');
		switch(option)
		{
			case 0:
				cout << "Quiting Program" << endl;
				return 0;
				break;
			case 1:
				cout << "Ice Cream Sandwich Option" << endl;
				sandwich_menu();
				break;
			case 2:
				cout << "Ice Cream Cake Option" << endl;
				cake_menu();
				break;
			case 3:
				cout << "Ice Cream Pancake Option" << endl;
				pancake_menu();
				break;
			case 4:
				cout << "Displaying all products inputted" << endl;
				tree.display();
				break;
			default:
				cout << "Invalid input" << endl;
				break;
		}
		cout << "Would you like to restart the main menu?" << endl;
	}while(again());

	return 0;
}


int menu::sandwich_menu()
{
	int option {0};
	do
	{
		cout << "Selected Ice Cream Sandwich Option" << endl;
		cout << "Please select an option." << endl;
		cout << "0. Quit back to main\n1. Insert new Sandwich\n2. Eat a Sandwich\n";
		cin >> option;
		cin.ignore(100, '\n');
		switch(option)
		{
			case 0:
				cout << "Quitting Sandwich Option" << endl;
				return 0;
				break;
			case 1:
				cout << "Inserting new Sandwich" << endl;
				i_ptr = make_unique<sandwich>();
				i_ptr->insert();
				cout << "Displaying inserted information\n" << endl;
				i_ptr->display();
				tree.insert(i_ptr);
				break;
			case 2:
				i_ptr = make_unique<sandwich>();
				i_ptr->eat_dessert();
				break;
			default:
				cout << "Invalid input" << endl;
				break;
		}
		cout << "Do another Sandwich Option?" << endl;
	}while(again());
	return 0;
}


int menu::cake_menu()
{
	int option {0};
	do
	{
		cout << "Selected Ice Cream Cake Option" << endl;
		cout << "Please select an option." << endl;
		cout << "0. Quit back to main\n1. Insert new Cake\n2. Blow Candles\n3. Eat a Cake\n";
		cin >> option;
		cin.ignore(100, '\n');
		switch(option)
		{
			case 0:
				cout << "Quitting Cake Option" << endl;
				return 0;
				break;
			case 1:
				cout << "Inserting new Cake" << endl;
				i_ptr = make_unique<cake>();
				i_ptr->insert();
				cout << "Displaying inserted information\n" << endl;
				i_ptr->display();
				tree.insert(i_ptr);
				break;
			case 2:
			{
				cout << "Candles option" << endl;
				//cake cake_obj;
				//i_ptr = make_unique<&cake_obj>();
				ice_cream * ice_ptr = new cake;
				cake * cake_ptr = dynamic_cast<cake*>(ice_ptr);
				cake_ptr->blow_candles();
				delete ice_ptr;
							
				break;
			}
			case 3:
				i_ptr = make_unique<cake>();
				i_ptr->eat_dessert();
				break;

			default:
				cout << "Invalid input" << endl;
				break;
		}
		cout << "Do another Cake Option?" << endl;
	}while(again());
	return 0;
}


int menu::pancake_menu()
{
	int option {0};
	do
	{
		cout << "Selected Ice Cream Pancake Option" << endl;
		cout << "Please select an option." << endl;
		cout << "0. Quit back to main\n1. Insert new Pancake\n2. Eat a Pancake\n";
		cin >> option;
		cin.ignore(100, '\n');
		switch(option)
		{
			case 0:
				cout << "Quitting Cake Option" << endl;
				return 0;
				break;
			case 1:
				cout << "Inserting new Pancake" << endl;
				i_ptr = make_unique<pancake>();
				i_ptr->insert();
				cout << "Displaying inserted information\n" << endl;
				i_ptr->display();
				tree.insert(i_ptr);
				break;
			case 2:
				i_ptr = make_unique<pancake>();
				i_ptr->eat_dessert();
				break;
			default:
				cout << "Invalid input" << endl;
				break;
		}
		cout << "Do another Pancake Option?" << endl;
	}while(again());
	return 0;
}
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

