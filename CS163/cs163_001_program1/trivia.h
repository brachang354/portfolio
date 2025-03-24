#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>


//Bradley Chang, 10-3-2023, CS163, Program #1

//Purpose of this file is to hold the class object for the categories which will contain
//the public member functions and head pointer. This file will also hold a node struct for 
//the list of categories which will contain the name of the category, next pointer, and head pointer
//to a clue node. There will also be node struct for the clues containing info on the 
//prize, clue, clue answer and next pointer

struct clue	//Clue data type containing prize amount, trivia clue, and the clue answer
{
	int prize;
	char * clue;
	char * answer;
	int difficulty;
	bool played;	//False if clue has not been played, true if clue has been played
};

struct clue_node	//Clue node containing clue information and next pointer
{
	clue a_clue;
	clue_node * clue_next;
};

struct category_node	//Category node containing category name, next pointer, and head pointer to clue node
{
	char * category_name;
	category_node * next;
	clue_node * clue_head;

};

class list
{
	public:
		list();	//Constructor
		~list();//Destructor
		bool add_category(char name[]); //Adds a category to the list, passes in the name of the category. Returns true if successfully
						//adds, returns false if it cannot add because category name already exists.
		int display_categories();	//Displays all categories, returns the number of categories displayed, returns 0 if no categories
		int add_clue(clue & clue_data, char category_name[]);//Adds a clue to a category. Passes in the clue object for the clue data like the
						//prize, the clue itself and the answer. Returns 0 if it cannot add a clue.
		bool read_in_clue(char category_name[], char file_name[]);//Adds in clue to a category from external data file. Passes in
									  //catregory name and file name. Returns true if successfully reads
									  //in clue
		int display_prizes(char category_name[]);	//Displays prizes in particular category. Passes in category name.
								//Returns amount of prizes displayed, returns 0 if nothing to display.
		int display_clue(char category_name[], int clue_prize); // Displays the clue based off of category name and prize amount. 
		bool remove(char category_name[]); //Removes a category, returns true if successfully removed.
	
	private:
		category_node * head;

};

bool again();
