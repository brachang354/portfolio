#
#include <cstring>
#include <cctype>
#include <iostream>

//Bradley Chang CS163_001 Program 2. Purpose of this file is to contain the stack data structure
//for our messages. Will contain functions such as display all, push (add) to stack, pop (remove)
//from stack, and peek.

struct message
{
	char * subject;
	char * sender;
	char * body;
	char * date;
};

struct node
{
	message * messages;
	node * next;
};

const int MAX = 5;

class stack
{
	public:
		stack(void);
		~stack(void);

		int display_all(void) const;	//Displays all messages in stack. Returns 0 if nothing to display
		int push(message & to_add);	//Adds a message to the top of the stack. Returns 0 if it cannot add.
		int pop(void);	//Removes a message at the top of the stack. Returns 0 if it cannot remove.
		int peek(message & found_at_top) const;//Displays the most recent message at the top of the stack. Returns 0 if theres nothing to display.
		int copy_data(message & to_add);	//Copys information into an array index in the stack. Used in push function.	
		
	private:
		node * head;
		int top_index;
};
bool again();

