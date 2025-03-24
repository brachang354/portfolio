#include "stack.h"
#include "queue.h"
using namespace std;
//Bradley Chang CS163 Program #2. Purpose of this file is to call all the public member functions
//from the stack class and queue class to test if they work.

int main()
{
	const int SIZE {100};
	
	message my_message;	
	stack my_stack;
	contact my_contact;
	queue my_queue;
	
//Stack function calls
	cout << "Test stack functions?: " << endl;
	if(again())
	{

		my_message.subject = new char[SIZE];
		my_message.sender = new char[SIZE];
		my_message.body = new char[SIZE];
		my_message.date = new char[SIZE];
		//Loop for push function call
		do
		{
			cout << "Insert Subject: " << endl;
			cin.get(my_message.subject, SIZE, '\n'); cin.ignore(100, '\n');

			cout << "Insert Sender: " << endl;
			cin.get(my_message.sender, SIZE, '\n'); cin.ignore(100, '\n');

			cout << "Insert Body: " << endl;
			cin.get(my_message.body, SIZE, '\n'); cin.ignore(100, '\n');

			cout << "Insert Date: " << endl;
			cin.get(my_message.date, SIZE, '\n'); cin.ignore(100, '\n');
			
			cout << "Items in list: " << my_stack.push(my_message) << endl;

			cout << "Again?: " << endl;
		}while(again());

		my_stack.display_all();

		//Pop function call
		cout << "Pop item from top of stack? (Y/N): " << endl;
		if(again())
		{
			do
			{
				my_stack.pop();
				my_stack.display_all();
				cout << "Again?: " << endl;
			}while(again());
		}

		cout << "Most recent message: " << endl;
		my_stack.peek(my_message);

		delete [] my_message.subject;
		delete [] my_message.sender;
		delete [] my_message.body;
		delete [] my_message.date;
	}
//Queue function calls

	cout << "Test queue functions?: " << endl;
	if(again())
	{
		my_contact.name = new char[SIZE];
		my_contact.email = new char[SIZE];
		my_contact.birthday = new char[SIZE];
		//Enqueue function call
		do
		{
			cout << "Insert name: " << endl;
			cin.get(my_contact.name, SIZE, '\n'); cin.ignore(100, '\n');
			cout << "Insert email: " << endl;
			cin.get(my_contact.email, SIZE, '\n'); cin.ignore(100, '\n');
			cout << "Insert phone number: " << endl;
			cin >> my_contact.phone_number; cin.ignore(100, '\n');
			cout << "Insert birthday: " << endl;
			cin.get(my_contact.birthday, SIZE, '\n'); cin.ignore(100, '\n');
			
			my_queue.enqueue(my_contact);

			cout << "Again?: " << endl;
		}while(again());

		my_queue.display_all();
		
		cout << "Peeking newest info: " << endl;
		my_queue.peek(my_contact);
		
		//Dequeue function call
		cout << "Dequeue item from list? (y/n): " << endl;
		if(again())
		{
			do
			{
				my_queue.dequeue();
				my_queue.display_all();
				cout << "Again?: " << endl;
			}while(again());
		}
			
		delete [] my_contact.name;
		delete [] my_contact.email;
		delete [] my_contact.birthday;
	}
	return 0;
};
