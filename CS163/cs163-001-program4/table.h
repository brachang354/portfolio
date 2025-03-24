#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>
//Bradley Chang CS163_001 Program #4. Purpose of this file is to contain the animal struct, node struct, table class with all of its function prototypes

const int SIZE {300};

struct animal
{
        char * name;
        char * sci_name;
        char * location;
        char * desc;
        char * population;
        int life_span;
};

struct node
{
        animal animals;
        node * left;
	node * right;
};

class table
{
        public:
                table();   //Constructor
                ~table(void);   //Destructor
                int add_animal(animal & to_add);	//Adds an animal to the tree, returns 1 for success.
                int load_file(char * file_name, animal & my_animal, table & my_table);  //Loads an external data file to add animals to the tree. Returns 1 for success
                int display_all();      //Displays all information inside the tree
                int retrieve_animal(char * name_to_find, animal & animal_info);//Takes in an animal's name to retrieve information about an animal
                int remove_animal(char * name_to_find); //Finds an animal by name in tree and removes it. Returns 1 for success.
                int copy_data(node * & root, animal & to_add);  //To copy data into a node of a tree. To be used in the add animal function
		int display_life_range(int start, int end); //Displays all animals within a range of a lifespan. Requires a start and end of the range passed in.
		int count_height();	//Determines height of the tree. Returns the height of the tree.
		int remove_data(node * & ptr);	//Passes in a node pointer and removes all dynamic memory inside that node. To be used inside remove animal function.
        	int remove_all();	//Removes all data in the tree.
	private:
                node * root;
		int add_animal(node * & root, animal & to_add);	//Recursive call for adding an animal
		int display_all(node * root);	//Recursive call for adding an animal
                int remove_animal(node * & root, char * name_to_find);  //Recursive call for remove animal function
		int count_height(node * root);	//Recursive call for count height.
		int retrieve_animal(char * name_to_find, animal & animal_info, node * root); //Recursive call for retrieve animal
		int remove_all(node * & remove_all);	//Recursive call to remove all.
		int display_life_range(int start, int end, node * root);	//Recursive call for display life range
};
bool again();

