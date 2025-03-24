#include "trivia.h"

//Bradley Chang CS 163. Purpose of main is to test out all of our functions. Each function has its own menu, and 
//can be repeated as well while the program is running. 

using namespace std;
const int SIZE {100};

int main()
{
	list my_list;	//Object for list class
	clue my_clue;	//Object for clue data type
	char name[SIZE];//Static array for name
	int clues{0};
	int prizes{0};
	int prize_amount{0};
	do	//Loop to add new categories to list
	{
		cout << "Insert name for category: " << endl;
		cin.get(name, SIZE, '\n'); cin.ignore(SIZE, '\n');
		my_list.add_category(name);
	}while(again());
	

	my_clue.clue = new char[SIZE];
	my_clue.answer = new char[SIZE];
	do	//Loop to add in clues to selected category
	{
		cout << "Enter category name you want to add clue to: " << endl;
		cin.get(name, SIZE, '\n'); cin.ignore(SIZE, '\n');
	
		cout << "Enter prize amount for clue: " << endl;
		cin >> my_clue.prize; cin.ignore(100, '\n');

		cout << "Enter clue: " << endl;
		cin.get(my_clue.clue, SIZE, '\n'); cin.ignore(SIZE, '\n');
	
		cout << "Enter clue answer: " << endl;
		cin.get(my_clue.answer, SIZE, '\n'); cin.ignore(SIZE, '\n');

		cout << "Enter difficulty(1-10): " << endl;
		cin >> my_clue.difficulty; cin.ignore(100, '\n');

		clues = my_list.add_clue(my_clue, name);
		if(clues == 1)
		{
			cout << "Added clue" << endl;
		}
		if(clues == 2)
		{
			cout << "Added another clue" << endl;	
		}
		if(clues == 0)
		{
			cout << "Error could not add clue" << endl;
		}
		

	}while(again());
	
	do	//Entering in category to view prizes
	{
		cout << "Enter category name you want to view all prizes: " << endl;
		cin.get(name, SIZE, '\n'); cin.ignore(SIZE, '\n');
		cout << "Displaying all prizes for " << name << endl;
		prizes = my_list.display_prizes(name);
		cout << "Amount of prizes total: " << prizes << endl << endl;
	}while(again());

	do	//Enter in category and prize to view clue
	{
		cout << "Enter category you want to display a clue: " << endl;
		cin.get(name, SIZE, '\n'); cin.ignore(SIZE, '\n');
		cout << "Select prize to view clue: " << endl;
		cin >> prizes; cin.ignore(SIZE, '\n');
		prize_amount = my_list.display_clue(name, prizes);
	}while(again());
	
	cout << "Displaying all info inputted: " << endl << my_list.display_categories() << endl;	//Displays all categories

	do	//Enter in category to remove
	{	
		cout << "Select category to remove: " << endl;
		cin.get(name, SIZE, '\n'); cin.ignore(SIZE, '\n');
		if(my_list.remove(name))
		{
			cout << "Successfully removed" << endl;
		}
		else
		{
			cout << "Error, could not remove" << endl;
		}
		cout << "Displaying new category list: " << endl << my_list.display_categories() << endl;
	}while(again());

	

	return 0;
}

