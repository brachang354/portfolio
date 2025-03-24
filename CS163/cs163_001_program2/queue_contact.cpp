#include "queue.h"
using namespace std;
//Bradley Chang CS163 Program #2. Purpose of this file is to contain the implementation
//of all queue functions.

queue::queue(void)	//Constructor
{
	rear = nullptr;
}
queue::~queue(void)	//Destructor
{
	if(!rear)
		return;
	q_node * temp = rear->next;
	rear->next = nullptr;
	q_node * hold = temp;
	while(temp->next != nullptr)
	{
		temp = temp->next;
		delete [] hold->contacts.name;
		delete [] hold->contacts.email;
		delete [] hold->contacts.birthday;
		delete hold;
		hold = temp;
	}
}
int queue::display_all()	//Wrapper function for display
{
	if(!rear)
		return 0;
	/*q_node * current = rear->next;
	do
	{
		cout << "Name: " << current->contacts.name << endl;
		cout << "Email: " << current->contacts.email << endl;
		cout << "Phone Number: " << current->contacts.phone_number << endl;
		cout << "Birthday: " << current->contacts.birthday << endl;
		current = current->next;
	}while(current != rear->next);*/
	return display_all(rear->next);

}
int queue::display_all(q_node * & rear)	//Recursive function for display
{
	if(rear == this->rear)
	{
		cout << "Name: " << rear->contacts.name << endl;
		cout << "Email: " << rear->contacts.email << endl;
		cout << "Phone Number: " << rear->contacts.phone_number << endl;
		cout << "Birthday: " << rear->contacts.birthday << endl;
		return 0;
	}
	cout << "Name: " << rear->contacts.name << endl;
	cout << "Email: " << rear->contacts.email << endl;
	cout << "Phone Number: " << rear->contacts.phone_number << endl;
	cout << "Birthday: " << rear->contacts.birthday << endl;

	return display_all(rear->next);
}
int queue::enqueue(contact & to_add)	//Enqueue adds a new node to the CLL and copies data into it
{
	//First case, empty list
	if(!rear)
	{
		rear = new q_node;
		rear->next = rear;
		q_copy_data(to_add);
		return 1;
	}
	//Second case, there is a list
	if(rear)
	{
		q_node * temp = rear->next;
		rear->next = new q_node;
		rear = rear->next;
		rear->next = temp;

		q_copy_data(to_add);
		return 1;
	}

	return 0;
}
int queue::dequeue()	//Dequeue removes the oldest item in the CLL
{
	//First case, empty list
	if(!rear)
		return 0;
	//Second case, one item list
	if(rear == rear->next)
	{
		delete [] rear->contacts.name;
		delete [] rear->contacts.email;
		delete [] rear->contacts.birthday;
		delete rear;
		rear = nullptr;
		return 1;
	}
	//Third case, multi item list
	else
	{
		q_node * temp = rear->next;
		rear->next = temp->next;
		delete [] temp->contacts.name;
		delete [] temp->contacts.email;
		delete [] temp->contacts.birthday;
		delete temp;
		return 1;
	}
	
}
int queue::peek(const contact & to_peek)//Displays the most recent item
{
	if(!rear)
		return 0;
		
	cout << "Name: " << rear->contacts.name << endl;
	cout << "Email: " << rear->contacts.email << endl;
	cout << "Phone Number: " << rear->contacts.phone_number << endl;
	cout << "Birthday: " << rear->contacts.birthday << endl;
	return 1;
}
int queue::q_copy_data(contact & to_add)
{
	rear->contacts.name = new char[strlen(to_add.name) +1];
	strcpy(rear->contacts.name, to_add.name);
	
	rear->contacts.email = new char[strlen(to_add.email) +1];
	strcpy(rear->contacts.email, to_add.email);

	rear->contacts.phone_number = to_add.phone_number;

	rear->contacts.birthday = new char[strlen(to_add.birthday) +1];
	strcpy(rear->contacts.birthday, to_add.birthday);
	return 1;
}
