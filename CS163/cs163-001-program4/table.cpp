#include "table.h"

using namespace std;
//Bradley Chang CS163_001 Program #4. Purpose of this file is to contain the implementation of all table member functions.

table::table()   //Constructor
{
	root = nullptr;
}
table::~table(void)   //Destructor
{
	remove_all(root);
}
int table::remove_all()	//Wrapper for remove all
{
	return remove_all(root);
}
int table::remove_all(node * & root)	//Recursive call for removing all nodes in tree. Returns number of nodes removed
{
	if(!root)
		return 0;
	int count {0};
	count = remove_all(root->left) + remove_all(root->right);
	remove_data(root);
	delete root;
	root = nullptr;
	return 1 + count;

}
int table::add_animal(animal & to_add)	//Adds an animal to the tree, returns 1 for success.
{
	return add_animal(root, to_add);
}
int table::add_animal(node * & root, animal & to_add)	//Recursive call for add animal.
{
	if(!root)
	{
		root = new node;
		copy_data(root, to_add);
		root->left = root->right = nullptr;
		return 1;
	}
	if(strcmp(root->animals.name, to_add.name) > 0)
	//if(root->animals.name > to_add.name)
		add_animal(root->left, to_add);
	else
		add_animal(root->right, to_add);
}
int table::load_file(char * file_name, animal & my_animal, table & my_table)  //Loads an external data file to add animals to the tree. Returns 1 for success
{}
int table::display_all()      //Displays all information inside the tree
{
	if(!root)
		return 0;
	return display_all(root);
}
int table::display_all(node * root)
{
	if(!root)
		return 0;
	display_all(root->left);

	cout << "-Name: " << root->animals.name << endl;
	cout << "-Sci Name: " << root->animals.sci_name << endl;
	cout << "-Location: " << root->animals.location << endl;
	cout << "-Desc: " << root->animals.desc << endl;
	cout << "-Population: " << root->animals.population << endl;
	cout << "-Life Span: " << root->animals.life_span << endl << endl;
	
	display_all(root->right);
}
int table::retrieve_animal(char * name_to_find, animal & animal_info) //Takes in an animal's name to retrieve information about an animal
{
	if(!root)
		return 0;
	return retrieve_animal(name_to_find, animal_info, root);
	
}
int table::retrieve_animal(char * name_to_find, animal & animal_info, node * root) //Takes in an animal's name to retrieve information about an animal
{
	if(!root)
		return 0;
	if(strcmp(root->animals.name, name_to_find) > 0)
		retrieve_animal(name_to_find, animal_info, root->left);
	else if(strcmp(root->animals.name, name_to_find) < 0)
		retrieve_animal(name_to_find, animal_info, root->right);
	else if(strcmp(root->animals.name, name_to_find) == 0)
	{
		strcpy(animal_info.name, root->animals.name);
		strcpy(animal_info.sci_name, root->animals.sci_name);
		strcpy(animal_info.location, root->animals.location);
		strcpy(animal_info.desc, root->animals.desc);
		strcpy(animal_info.population, root->animals.population);
		//strcpy(animal_info.life_span, root->animals.life_span); 
		animal_info.life_span = root->animals.life_span;
		return 1;
	}	
}
int table::remove_animal(char * name_to_find) //Finds an animal by name in tree and removes it. Returns 1 for success.
{
	//Check if tree is empty
	if(!root)
		return 0;
	return remove_animal(root, name_to_find);
}
int table::remove_animal(node * & root, char * name_to_find)	//Recursive call for removing an animal
{
	//First traverse to find match
	if(!root)
		return 0;
	if(strcmp(root->animals.name, name_to_find) > 0)
	{
		remove_animal(root->left, name_to_find);
	}
	else if(strcmp(root->animals.name, name_to_find) < 0)
	{
		remove_animal(root->right, name_to_find);
	}
	//Case: Leaf, no children
	else if(!root->left && !root->right)
	{
		remove_data(root);
		delete root;
		root = nullptr;
		return 1;
	}
	//Case: One child on the left
	else if(root->left && !root->right)
	{
		node * hold = root;
		root = root->left;
		remove_data(hold);
		delete hold;
		return 2;
		//remove_data(root);
		//delete root;
		//return hold;
		/*root = hold;
		return 1;*/
	}
	//Case: One child on the right
	else if(!root->left && root->right)
	{
		node * hold = root;
		root = root->right;
		remove_data(hold);
		delete hold;
		return 3;
		//remove_data(root);
		//delete root;
		//return hold;
		/*root = hold;
		return 1;*/
	}
	//Case: Two children
	else
	{
		node * curr = root->right;	//Current looks into root's right

		if(!curr->left)	//If curr is the IOS, meaning it has no left child
		{
			remove_data(root);
			copy_data(root, curr->animals);
			root->right = curr->right;
			remove_data(curr);
			delete curr;
			return 4;
		}
		else	//Curr is not the IOS because it has a left child.
		{
			node * previous = curr;	//Prev is set to curr
			while(curr->left)	//Loop to find IOS by going all the way to the left
			{
				previous = curr;	//Previous will be the IOS's parent
				curr = curr->left;	//Current goes to the IOS
			}	
			remove_data(root);	//Remove's root's data
			copy_data(root, curr->animals);	//Copy current's data into root
			previous->left = curr->right;	//Ios's parent's left pointer now points to curr's right child
			remove_data(curr);
			delete curr;
			return 5;
			//remove_animal(curr, curr->animals.name);	//Call remove function to delete current.
			/*root = nullptr;
			return 1;*/
		}
	}
}
int table::copy_data(node * & root, animal & to_add)  //To copy data into a node of a tree. To be used in the add animal function
{
	root->animals.name = new char[strlen(to_add.name) + 1];
        strcpy(root->animals.name, to_add.name);
        root->animals.sci_name = new char[strlen(to_add.sci_name) + 1];
        strcpy(root->animals.sci_name, to_add.sci_name);
        root->animals.location = new char[strlen(to_add.location) + 1];
        strcpy(root->animals.location, to_add.location);
        root->animals.desc = new char[strlen(to_add.desc) + 1];
        strcpy(root->animals.desc, to_add.desc);
        root->animals.population = new char[strlen(to_add.population) + 1];
        strcpy(root->animals.population, to_add.population);
        /*root->animals.life_span = new char[strlen(to_add.life_span) + 1];
        strcpy(root->animals.life_span, to_add.life_span);*/
	root->animals.life_span = to_add.life_span;
        return 0;
}
int table::display_life_range(int start, int end) //Displays all animals within a range of a lifespan. Requires a start and end of the range passed in.
{
	if(!root)
		return 0;
	return display_life_range(start, end, root);
}
int table::display_life_range(int start, int end, node * root)
{
	if(!root)
                return 0;
        display_life_range(start, end, root->left);
	if(root->animals.life_span >= start && root->animals.life_span <= end)
	{
		cout << "-Name: " << root->animals.name << endl;
		cout << "-Sci Name: " << root->animals.sci_name << endl;
		cout << "-Location: " << root->animals.location << endl;
		cout << "-Desc: " << root->animals.desc << endl;
		cout << "-Population: " << root->animals.population << endl;
		cout << "-Life Span: " << root->animals.life_span << endl << endl;
	}
        display_life_range(start, end, root->right);
}
int table::count_height()	//Determines height of the tree. Returns the height of the tree.
{
	if(!root)
		return 0;
	return count_height(root);
}
int table::count_height(node * root)	//Recursive call for count height.
{
	int left_height {0};
	int right_height {0};
	int height {0};
	if(!root)
		return 0;
	left_height = count_height(root->left);
	right_height = count_height(root->right);
	height = max(left_height, right_height) + 1;
	return height;
}

int table::remove_data(node * & ptr)	//Deletes all dynamic memory in a node
{
	delete [] ptr->animals.name;
	delete [] ptr->animals.sci_name;
	delete [] ptr->animals.location;
	delete [] ptr->animals.desc;
	delete [] ptr->animals.population;
	//delete [] ptr->animals.life_span;
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
