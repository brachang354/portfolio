#include <cstring>
#include <cctype>
#include <iostream>

//Bradley Chang CS163_001 Program 2. Purpose of this file is to contain the queue data structure class, and
//queue nodes containing a contact. Contains functions such as display, enqueue, dequeue, and peek

struct contact
{
	char * name;
	char * email;
	int phone_number;
	char * birthday;
};

struct q_node
{
	contact contacts;
	q_node * next;
};

class queue
{
	public:
		queue(void);
		~queue(void);

		int display_all();	//Displays all contacts in the queue. Returns 0 if nothing to display
		int enqueue(contact & to_add);//Adds a contact to the queue. Returns 0 if it cannot add a contact
		int dequeue();	//Removes a contact. Returns 0 if nothing to remove.
		int peek(const contact & to_peek);	//Displays the last item queued in. Returns 0 if nothing to display
		int q_copy_data(contact & to_add);	//Copies data into a queue node, used for enqueue function.
	private:
		q_node * rear;
		int display_all(q_node * & rear);
};

