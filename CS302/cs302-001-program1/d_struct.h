//Bradley Chang CS302
//******DATA STRUCTURE CLASSES******//
//Using Lab 1's node classes as reference
#include "farm.h"
class corn_node: public corn_maze	//CLL Node for the corn maze class
{
	public:
		corn_node();	//Constructor
		~corn_node();	//Destructor
		corn_node(const corn_node & source);	//Copy constructor
		corn_node(const corn_maze & new_corn);	

		//Constuctor with arguments. Unsure if this is the way to do it. Don't need
		//corn_node(const char * a_name, int a_schedule_time, int a_cost, int a_stamp, int a_start_time, int a_difficulty);
	
		void set_next(corn_node * new_next);	//Setter for next
		corn_node *& get_next();	//Getter for next
		bool has_next() const;		//Checks if next is null
	private:
		corn_node * next;
};

class CLL_corn
{
	public:
		CLL_corn();	//Constructor
		~CLL_corn();	//Destructor
		void display() const;	//Display
		int enqueue(const corn_maze & to_add);	//Inserting a node
		int dequeue();		//Removing a node
		int remove_all();	//Remove all
		CLL_corn & operator=(const CLL_corn & source);	//Assignment operator
		int copy(corn_node *& dest, corn_node * source, corn_node * source_rear);
	private:
		corn_node * rear;
		void display(corn_node * rear) const;	//Recursive display
		int remove_all(corn_node *& rear);	//Recursive remove
		
};

class egg_node: public egg_hunt		//An ARR node for the egg_hunt class
{
	public:
		egg_node();	//Constructor
		~egg_node();	//Destructor
		egg_node(const egg_node & source);	//Copy constructor
		egg_node(const egg_hunt & new_hunt);  //Constructor w/ arg
		
		void set_next(egg_node * new_next);	//Setter
		egg_node *& get_next();	//Getter
		bool has_next() const;	//Checks for next
	private:
		egg_node * next; 
};

class ARR_egg
{
	public:
		ARR_egg();	//Default constructor
		ARR_egg(int size = 5);	//Constructor
		~ARR_egg();	//Destructor
		void display() const;	//Display
		int insert();
		int remove();
		int remove_all();
	private:
		egg_node ** table;	//Pointer to head pointer
		int table_size;		//Size of the array
};
