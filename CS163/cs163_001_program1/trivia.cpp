#include "trivia.h"

using namespace std;

//Bradley Chang Project 1. Purpose of this file is to contain the bodies of every public member function. 
//These functions will be called in main to test them out. Functions include adding a category, displaying info in all categories
//adding a clue, displaying prizes in a specified category, displaying a clue for a matching category and prize, and removing a category.

//Constructor
list::list()
{
	head = nullptr;	
}	
//Destructor
list::~list()
{
	while(head)
	{
		category_node * hold = head;
		hold = head->next;

		while(head->clue_head)
		{
			clue_node * clue_temp = head->clue_head;
			clue_node * clue_hold = clue_temp->clue_next;
			clue_temp->clue_next = nullptr;
			head->clue_head = clue_hold;
			delete clue_temp;
			clue_temp = clue_hold;
		}
		head->next = nullptr;
		delete head;
		head = hold;
	}
}

//This function will add a category to a LLL
bool list::add_category(char name[]) 
{
	if(!head)	//There's no list so we add a node to the beginning.
	{
		head = new category_node;	// Make a new node
		head->category_name = new char(strlen(name) + 1);//Allocate array for category name
		strcpy(head->category_name, name);	//Copy name argument into category name in node.
		head->next = nullptr;				//Set next pointer to null

		return true;
	}
	else	//There's a list, so we add node to the beginning  of that list
	{
		category_node * temp = head;
		head = new category_node;
		head->next = temp;

		head->category_name = new char(strlen(name) + 1);//Allocate array for category name
		strcpy(head->category_name, name);	//Copy name argument into category name in node.
		return true;
	}
}

//This function will display all categories and clue information inside
int list::display_categories()
{
	if(!head)
		return 0;
	
	int count {0};
	category_node * temp = head;
	while (temp != nullptr)
	{

		clue_node * clue_temp = temp->clue_head;
		cout << "Category: " << temp->category_name << endl;
		
		while (clue_temp != nullptr)
		{
			cout << "-Prize: " << clue_temp->a_clue.prize << endl;
			cout << "-Clue: " << clue_temp->a_clue.clue << endl;
			cout << "-Answer: " << clue_temp->a_clue.answer << endl;
			cout << "-Difficulty: " << clue_temp->a_clue.difficulty << endl;
			if(!clue_temp->a_clue.played)
				cout << "Not Played" << endl;
			if(clue_temp->a_clue.played)
				cout << " Played" << endl;
			cout << endl;
			clue_temp = clue_temp->clue_next;
		}
		
		++count;
		temp = temp->next;
	}
	return count;
}

//This function will add a clue to a clue list inside a category node
int list::add_clue(clue & clue_data, char category_name[])
{
	if(!head)
		return 0;

	category_node * temp = head;

	while(temp && strcmp(temp->category_name, category_name)!=0)	//Traverse list to find matching category name.
	{
		temp = temp->next;
	}	//Temp pointer will stop at the category node we want.
	
	if(!temp)
		return 0;
	
	clue_node * clue_temp = temp->clue_head;	//Create temp clue pointer so we can access data in clue node
	
		//First scenario, there is no clue list in the category node. So we add a clue node to it.
	if(clue_temp == nullptr)
	{
		clue_temp = new clue_node;	//Create a new clue node
		temp->clue_head = clue_temp;

		clue_temp->a_clue.prize = clue_data.prize;	//Assign the clue prize and store it in the clue node
		
		clue_temp->a_clue.clue = new char(strlen(clue_data.clue) + 1);
		strcpy(clue_temp->a_clue.clue, clue_data.clue);

		clue_temp->a_clue.answer = new char(strlen(clue_data.answer) + 1);
		strcpy(clue_temp->a_clue.answer, clue_data.answer);

		clue_temp->a_clue.difficulty = clue_data.difficulty;

		clue_temp->a_clue.played = false;

		clue_temp->clue_next = nullptr;	//Next pointer of clue node will be null
		return 1;
	}

	else	//Second scenario, there is already a clue list
	{
		clue_node * clue_hold = clue_temp;	//Create a clue hold pointer to hold onto LLL
		clue_temp = new clue_node;	//Create new clue node with clue temp
		clue_temp->clue_next = clue_hold;	//Reconnect the new clue node and have it point to clue hold
		temp->clue_head = clue_temp;

		clue_temp->a_clue.prize = clue_data.prize;	//Insert prize data into clue node

		clue_temp->a_clue.clue = new char(strlen(clue_data.clue) + 1);
		strcpy(clue_temp->a_clue.clue, clue_data.clue);

		clue_temp->a_clue.answer = new char(strlen(clue_data.answer) + 1);
		strcpy(clue_temp->a_clue.answer, clue_data.answer);
		
		clue_temp->a_clue.difficulty = clue_data.difficulty;
		clue_temp->a_clue.played = false;
		return 2;
	}

}

bool list::read_in_clue(char category_name[], char file_name[])
{}

//This displays all the prizes in a specific category
int list::display_prizes(char category_name[])
{
	if(!head)
		return 0;
	category_node * temp = head;
	while(temp && strcmp(temp->category_name, category_name) != 0)
	{
		temp = temp->next;
	}
	if(!temp)
		return 0;

	int count{0};
	clue_node * clue_temp = temp->clue_head;
	
	while(clue_temp)
	{
		cout << "Prize: " << clue_temp->a_clue.prize << endl;
		++count;
		clue_temp = clue_temp->clue_next;
	}
	return count;

}
//Displaying a clue of a selected category and prize
int list::display_clue(char category_name[], int clue_prize) 
{
	if(!head)
		return 0;
	category_node * temp = head;
	while(temp && strcmp(temp->category_name, category_name) != 0)
	{
		temp = temp->next;
	}
	if(!temp)
		return 0;

	clue_node * clue_temp = temp->clue_head;
	while(clue_temp && clue_temp->a_clue.prize != clue_prize)
	{
		clue_temp = clue_temp->clue_next;
	}
	if(!clue_temp)
		return 0;
	cout << "Clue: " << clue_temp->a_clue.clue << endl;
	clue_temp->a_clue.played = true;
	return clue_temp->a_clue.prize;


}

bool list::remove(char category_name[])
{
	if(!head)
		return false;
	//First scenario, one category in LLL
	if(!head->next)
	{
		while(head->clue_head)
		{
			clue_node * clue_temp = head->clue_head;
			clue_node * clue_hold = clue_temp->clue_next;
			clue_temp->clue_next = nullptr;
			head->clue_head = clue_hold;
			delete clue_temp;
			clue_temp = clue_hold;
		}
		delete head;
		head = nullptr;
		return true;
	}
	//Second scenario multiple categories
	
	category_node * temp = head;
	category_node * previous = temp;
	while(temp && strcmp(temp->category_name, category_name) != 0)
	{
		previous = temp;
		temp = temp->next;
	}
	if(!temp)
		return false;

	while(temp->clue_head)
	{
		clue_node * clue_temp = temp->clue_head;
		clue_node * clue_hold = clue_temp->clue_next;
		clue_temp->clue_next = nullptr;
		temp->clue_head = clue_hold;
		delete clue_temp;
		clue_temp = clue_hold;
	}
	previous->next = temp->next;
	temp->next = nullptr;
	delete temp;
	temp = previous->next;
	return true;

}

bool again()
{	
        char response {'n'};
        cout << "Do you want to enter again? (y/n): ";
        cin >> response;
        cin.ignore(100, '\n');
        if (toupper(response) == 'Y')
                return true;
        return false;
}
