#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>
//Bradley Chang CS163_001 Program #3. Purpose of this file is to contain the animal struct, node struct, table class with all of its function prototypes

const int SIZE {300};

struct animal
{
	char * name;
	char * sci_name;
	char * location;
	char * desc;
	char * population;
	char * life_span;

};

struct node 
{
	animal animals;
	node * next;
};

class table
{
	public:
		table(int size = 31);	//Constructor
		int add_animal(char * key_value, animal & to_add);	//Adds an animal to the table. Returns 1 for success
		int load_file(char * file_name, animal & my_animal, table & my_table);	//Loads an external data file to add animals to the table. Returns 1 for success
		int display_all();	//Displays all information inside the table
		int display_animal(char * name_to_find);	//Takes in an animal's name and displays information about it. Returns 1 for success
		int retrieve_animal(char * name_to_find, animal & animal_info);//Takes in an animal's name to retrieve information about an animal
		~table(void);	//Destructor
		int remove_animal(char * name_to_find);//Find's index where the animal is located, then uses it's common name to 
									//find it's node and delete it.
		int display_location(char * loca_to_find);//Find's an animal by location and displays it.
		int copy_data(animal & to_add, int i);	//To copy data into a node of an index. Needs an animal and index passed in.
	private:
		node ** hash_table;
		int hash_table_size;
		int hash_function(char * key)const;	//Hash function. Takes in a key and returns an index to map to.
		int remove_animal(node * & head, char * name_to_find);	//Recursive call for remove animal function.
};
bool again();
