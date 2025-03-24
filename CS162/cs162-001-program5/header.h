//Bradley Chang CS162_001 Program 5
//
//Purpose of this program is to be a food cart tracker. It will ask for 
//the name of the food cart, a favorite food, cost of favorite food,
//a rating of the cart from 1 to 10, and a description. All information
//is stored in a linear linked list. All information that user entered
//is displayed back in order of last item entered to first item entered.

#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

const int SIZE {51};	//Max size of name array and favorite food array.
const int DESC {201};	//Maximum size of description

struct food
{
	char name[SIZE];	//Name of food cart
	char favFood[SIZE];	//Favorite food from cart
	int cost;		//Cost of food
	char desc[DESC];	//Initial static array for description
	char * desc_ptr;	//Description of food cart pointer
	int rating;		//Rating of cart from 1 - 10
};

struct node
{
	food foodInfo;	//Food object
	node * next;	//Pointer to next node
};

//Prototype for functions
void newFood(node * & head);		//Function to read in info from user
void insertFood(node * & head);		//Inserts a new node into LLL at beginning
void display(node * head);		//Traverses LLL and displays all contents.
bool again();				//Asks user if they want to perform action again.
void destroy(node * & head);		//Deletes the linear linked list and any dynamic memory stored in it
