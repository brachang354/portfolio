#include "header.h"
//Put all functions in here

//New food function to allow user to input information

void newFood(node * & head)
{
	cout << "Enter food cart's name: ";
	cin.get(head->foodInfo.name, SIZE, '\n');
	cin.ignore(100, '\n');

	cout << "Enter favorite food: ";
	cin.get(head->foodInfo.favFood, SIZE, '\n');
	cin.ignore(100, '\n');
	
	cout << "Enter cost of favorite food: ";
	cin >> head->foodInfo.cost;
	cin.ignore(100, '\n');
	
	cout << "Enter rating of food cart (1-10): ";
	cin >> head->foodInfo.rating;
	cin.ignore(100, '\n');
	
	int length {0};	//Length of description
	head->foodInfo.desc_ptr = nullptr;

	cout << "Enter a description: ";
	cin.get(head->foodInfo.desc, DESC, '\n');
	cin.ignore(100, '\n');

	length = (strlen(head->foodInfo.desc) + 1);
	head->foodInfo.desc_ptr = new char[length];
	strcpy(head->foodInfo.desc_ptr, head->foodInfo.desc);
}

//Insert node at beginning and insert food information into that node
void insertFood(node * & head)
{
	if(!head)
	{
		head = new node;
		head->next = nullptr;
	}
	else if (head)
	{
		node * temp = head;
		head = new node;
		head->next = temp;
	}	
	newFood(head);

}

//Display all contents of LLL
void display(node * head)
{	
	int count{0};
	if(!head)
		return;

	node * current = head;
	while(nullptr != current)
	{
		++count;
		cout << count << ")" << endl;
		cout << "Name: " << current->foodInfo.name << endl;
		cout << "Favorite Food: " << current->foodInfo.favFood << endl;
		cout << "Cost of Favorite Food: $" << current->foodInfo.cost << endl;
		cout << "Rating of Food Cart (1-10): " << current->foodInfo.rating << endl;
		cout << "Description: " << current->foodInfo.desc_ptr << endl;
		cout << endl;
		current = current->next;	
	}

}

//Asks if user wants to enter information again
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
//Destructor
void destroy(node * & head)
{
	//To destroy all nodes
	while(head)
	{
		node * temp = head;	//Temp pointer pointing to where head is pointing
		head = head->next;
		delete [] temp->foodInfo.desc_ptr;
		delete temp;
		temp = nullptr;
	}

	
}


