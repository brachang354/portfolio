//Bradley Chang CS302 Program 1
//Function implementation of data structures
#include "menu.h"
	
//*********Corn Node************
corn_node::corn_node(): next(nullptr) 	//Constructor
{}
corn_node::~corn_node() 		//Destructor
{}
corn_node::corn_node(const corn_node & source): corn_maze(source), next(nullptr)	//Copy constructor
{}
corn_node::corn_node(const corn_maze & new_corn): corn_maze(new_corn), next(nullptr)	
{}
void corn_node::set_next(corn_node * new_next) 	//Setter for next
{
	next = new_next;
}
corn_node *& corn_node::get_next() 	//Getter for next
{
	return next;
}
bool corn_node::has_next() const 		//Checks if next is null
{
	return next != nullptr;
}

//*********CLL for Corn Maze********

CLL_corn::CLL_corn() 	//Constructor
{}
CLL_corn::~CLL_corn() 	//Destructor
{
	if(rear)
	{
		remove_all();
	}
}
void CLL_corn::display() const 	//Display wrapper
{
	if(!rear)
	{
		cout << "Nothing to display!" << endl;
		return;
	}
	display(rear->get_next());
}

void CLL_corn::display(corn_node * rear) const	//Display recursive
{
	if(rear == this->rear)
	{
		//Display function to cout
		rear->display();
		return;
	}
	//Display function to cout
	rear->display();

	display(rear->get_next());
}
int CLL_corn::enqueue(const corn_maze & to_add) 	//Inserting a node
{

	if(!rear)	//First case empty list
	{	
		rear = new corn_node(to_add);	//Create a new node passing in the corn maze object	
		//rear->stamps = to_add.stamps;
		rear->set_next(rear);
		return 1;
	}
	else		//Second case multi item list
	{
		corn_node * hold = rear->get_next();
		corn_node * temp = new corn_node(to_add);	//Create a new node passing in the corn maze object
		
		//rear->get_next() = new corn_node;
		rear->set_next(temp);
		rear = rear->get_next();
		rear->set_next(hold);
		return 1;
	}
}
int CLL_corn::dequeue() 		//Removing a node
{
	if(!rear)
		return 0;
	if(rear == rear->get_next())	//If there is only one node
	{
		delete rear;
		rear = nullptr;
		return 1;
	}
	else
	{
		corn_node * temp = rear->get_next();
		rear->set_next(temp->get_next());
		delete temp;
		return 1;
	}
	return 0;
}
int CLL_corn::remove_all() 	//Remove all wrapper
{
	if(!rear)
		return 0;
	
	corn_node * temp = rear;
	//temp->set_next(rear->get_next());
	temp = rear->get_next();
	rear->set_next(nullptr);
	rear = temp;

	return remove_all(rear);
}
int CLL_corn::remove_all(corn_node *& rear)	//Recursive remove
{
	if(!rear)
		return 0;
	remove_all(rear->get_next());
	delete rear;
	rear = nullptr;
	return 1;
}
CLL_corn & CLL_corn::operator=(const CLL_corn & source)	//Assignment op
{
	if (this == &source)
	{
		return *this;
	}
	
	//Uncomment below after implementation of copy function.
	//copy(rear, source.rear->get_next(), source.rear);
	return *this;
}

//********Egg Hunt ARR Node**********
egg_node::egg_node(): next(nullptr)	//Constructor
{}
egg_node::~egg_node()	//Destructor
{}
egg_node::egg_node(const egg_node & source): egg_hunt(source), next(nullptr)	//Copy constructor
{}
egg_node::egg_node(const egg_hunt & new_hunt): egg_hunt(new_hunt), next(nullptr)  //Constructor w/ arg
{}
void egg_node::set_next(egg_node * new_next)	//Setter
{
	next = new_next;
}
egg_node *& egg_node::get_next()	//Getter
{
	return next;
}
bool egg_node::has_next() const	//Checks for next
{
	return next != nullptr;
}

//********Egg Hunt ARR Class***********
ARR_egg::ARR_egg(): table(nullptr)	//Defualt constructor
{}
ARR_egg::ARR_egg(int size)	//Constructor
{
	table_size = size;
	table = new egg_node*[size];
	for(int i = 0; i != size; ++i)
	{
		table[i] = nullptr;
	}
}
ARR_egg::~ARR_egg()	//Destructor
{}
void ARR_egg::display() const	//Display
{
}
int ARR_egg::insert()
{
	return 0;
}
int ARR_egg::remove()
{
	return 0;
}
int ARR_egg::remove_all()
{
	return 0;
}
