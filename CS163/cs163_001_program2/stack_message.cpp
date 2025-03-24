#include "stack.h"
using namespace std;

//Bradley Chang CS163_001 Program #2. Purpose of this file is to contain the implementation of
//the stack functions

stack::stack(void)
{
	head = nullptr;
	top_index = 0;
}
stack::~stack(void)
{
	if(!head)
		return;
	node * temp = head;
	while(head)
	{
		temp = head->next;
		delete [] head->messages;
		delete head;
		head = temp;
	}
}
int stack::display_all(void) const	//Displays all messages in stack. Returns 0 if nothing to display
{
	if(!head)
		return 0;
	node * temp = head;
	int count{0};
	while (temp != nullptr)
	{
		count = 0;
		if(temp == head)
		{
			while(count != top_index)
			{	
				cout << "Subject: " << temp->messages[count].subject << endl;
				cout << "Sender: " << temp->messages[count].sender << endl;
				cout << "Body: " << temp->messages[count].body << endl;
				cout << "Date: " << temp->messages[count].date << endl;
				++count;
			}
		}
		if(temp != head)
		{
			while(count != MAX)
			{
				cout << "Subject: " << temp->messages[count].subject << endl;
				cout << "Sender: " << temp->messages[count].sender << endl;
				cout << "Body: " << temp->messages[count].body << endl;
				cout << "Date: " << temp->messages[count].date << endl;
				++count;
			}
		}
		temp = temp->next;
	}
	return 1;
}
int stack::push(message & to_add)	//Adds a message to the top of the stack. Returns 0 if it cannot add.
{
	//First case, no LLL yet
	if(!head)
	{
		head = new node;
		head->next = nullptr;
		head->messages = new message[MAX];
		
		copy_data(to_add);
	
		top_index += 1;
		return top_index;
	}
	//Second case, there is an LLL but array is NOT full
	if(head && top_index != MAX)
	{
		copy_data(to_add);
		top_index += 1;
		return top_index;
	}
	//Third case, there is an LLL and array is FULL
	if(head && top_index == MAX)
	{
		top_index = 0;
		node * hold = head;
		head = new node;
		head->next = hold;
		head->messages = new message[MAX];
		copy_data(to_add);
		top_index += 1;
		return top_index;
	}
	return 0;
}
int stack::pop(void)	//Removes a message at the top of the stack. Returns 0 if it cannot remove.
{
	//First case. No LLL
	if(!head)
		return 0;
	//Second case. If array has data but the data is the not the last entry
	if(head && top_index != 0)
	{
		top_index -= 1;	//Decrement index
		if(head && top_index == 0)//Check if array is empty, if it is delete the node.
		{
			node * hold = head->next;
			delete head;
			head = hold;
			top_index = MAX;
			return 1;
		}
		return 1;
	}
	//Third case. If array has data and its the last entry
	/*
	if(head && top_index == 0)
	{
		node * hold = head->next;
		delete head;
		head = hold;
		top_index = MAX;
		return 1;
	}
	*/
	return 0;	
}
int stack::peek(message & found_at_top) const//Displays the most recent message at the top of the stack. Returns 0 if theres nothing to display.
{
	if(!head)
		return 0;
	cout << "Subject: " << head->messages[top_index-1].subject << endl;
	cout << "Sender: " << head->messages[top_index-1].sender << endl;
	cout << "Body: " << head->messages[top_index-1].body << endl;
	cout << "Date: " << head->messages[top_index-1].date << endl;
	return 1;
}
int stack::copy_data(message & to_add)
{	
	head->messages[top_index].subject = new char[strlen(to_add.subject) +1];	
	strcpy(head->messages[top_index].subject, to_add.subject);

	head->messages[top_index].sender = new char[strlen(to_add.sender) +1];
	strcpy(head->messages[top_index].sender, to_add.sender);

	head->messages[top_index].body = new char[strlen(to_add.body) +1];
	strcpy(head->messages[top_index].body, to_add.body);
	
	head->messages[top_index].date = new char[strlen(to_add.date) +1];
	strcpy(head->messages[top_index].date, to_add.date);

	return 1;
}
bool again()
{
	char response {'n'};
        cout << "Y or N: ";
        cin >> response;
        cin.ignore(100, '\n');
        if (toupper(response) == 'Y')
                return true;
        return false;
}
