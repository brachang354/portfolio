#include "table.h"
using namespace std;
//Bradley Chang CS163_001 Program #3. Purpose of this file is to contain the member function implementation
table::table(int size)
{
	hash_table_size = size;
	hash_table = new node*[size];
	int count {0};
	while (count != size)
	{
		hash_table[count] = nullptr;
		++count;
	}
}
table::~table(void)
{
	int i {0};
	while (i < hash_table_size)
	{
		node * temp = hash_table[i];
		while(temp != nullptr)
		{
			hash_table[i] = temp->next;
			delete [] temp->animals.name;
			delete [] temp->animals.sci_name;
			delete [] temp->animals.location;
			delete [] temp->animals.desc;
			delete [] temp->animals.population;
			delete [] temp->animals.life_span;
			delete temp;
			temp = hash_table[i];
		}
		++i;
	}
	delete [] hash_table;	
}

int table::hash_function(char * key)const	//Hash function, takes all of characters in the name and adds them together to get an index
{
	int table_index {0};
	int i {0};
	int key_size {0};
	key_size = strlen(key);
	while (i < key_size)
	{
		table_index += key[i];
		++i;
	}
	table_index = table_index % hash_table_size;
	return table_index;
}

int table::add_animal(char * key_value, animal & to_add)	//Adds an animal to the table. Passes in the key value, and animal object
{
	int i {0};//Index for table
	i = hash_function(key_value);
	//First case if index has empty LLL
	if(!hash_table[i])
	{
		hash_table[i] = new node;
		hash_table[i]->next = nullptr;
		copy_data(to_add, i);
		return i;
	}
	//Second case if index has a LLL
	else
	{
		node * temp = hash_table[i];
		hash_table[i] = new node;
		hash_table[i]->next = temp;
		copy_data(to_add, i);
		return i;
	}
	return i;
}
int table::load_file(char * file_name, animal & my_animal, table &  my_table)	//Loads an external data file to add animals to the table. Passes in file name, animal object, and table object
{
	ifstream in_file;
	
	in_file.open(file_name);
	
	if(in_file)
	{
		my_animal.name = new char[SIZE];	//Arrays created for input
		my_animal.sci_name = new char[SIZE];
		my_animal.location = new char[SIZE];
		my_animal.desc = new char[SIZE];
		my_animal.population = new char[SIZE];
		my_animal.life_span = new char[SIZE];
		
		in_file.get(my_animal.name, SIZE, '|'); in_file.ignore(SIZE, '|');
		while(in_file && !in_file.eof())	//Loop to add all data from file into table
		{
			in_file.get(my_animal.sci_name, SIZE, '|'); in_file.ignore(SIZE, '|');
			in_file.get(my_animal.location, SIZE, '|'); in_file.ignore(SIZE, '|');
			in_file.get(my_animal.desc, SIZE, '|'); in_file.ignore(SIZE, '|');
			in_file.get(my_animal.population, SIZE, '|'); in_file.ignore(SIZE, '|');
			in_file.get(my_animal.life_span, SIZE, '\n'); in_file.ignore(SIZE, '\n');

			my_table.add_animal(my_animal.name, my_animal);

			in_file.get(my_animal.name, SIZE, '|'); in_file.ignore(100, '|');
		}
		in_file.close();

		delete [] my_animal.name;
		delete [] my_animal.sci_name;
		delete [] my_animal.location;
		delete [] my_animal.desc;
		delete [] my_animal.population;
		delete [] my_animal.life_span;
		return 1;
	}
	return 0;

}
int table::display_all()	//Displays all data inside the table
{
	int i {0};
	while (i != hash_table_size)	//This loop goes through all the indices in the table
	{
		node * temp = hash_table[i];
		cout << "\nIndex: " << i << endl;
		while(temp != nullptr)//At each index, this loop will display everything inside the LLL at that index
		{
			cout << "-Name: " << temp->animals.name << endl;
			cout << "-Sci Name: " << temp->animals.sci_name << endl;
			cout << "-Location: " << temp->animals.location << endl;			
			cout << "-Desc: " << temp->animals.desc << endl;
			cout << "-Population: " << temp->animals.population << endl;
			cout << "-Life Span: " << temp->animals.life_span << endl << endl;
			temp = temp->next;
		}
		++i;
	}
	return i;
}
int table::display_animal(char * name_to_find)	//Searches an animal by name and displays it's info.
{
	int i {0};
	i = hash_function(name_to_find);	
	node * temp = hash_table[i];
	while (temp != nullptr && strcmp(temp->animals.name, name_to_find) != 0)
	{
		temp = temp->next;
	}
	if(!temp)
	{
		cout << "No match found" << endl;
		return 0;
	}
	else
	{
		cout << "Match found, displaying info" << endl;
		cout << "-Name: " << temp->animals.name << endl;
		cout << "-Sci Name: " << temp->animals.sci_name << endl;
		cout << "-Location: " << temp->animals.location << endl;
		cout << "-Desc: " << temp->animals.desc << endl;
		cout << "-Population: " << temp->animals.population << endl;
		cout << "-Life Span: " << temp->animals.life_span << endl;
		return 1;
	}

}
int table::retrieve_animal(char * name_to_find, animal & animal_info)	//Searches an animal by name and retrieve's its info by copying into animal object passed in
{
	int i {0};
	i = hash_function(name_to_find);	
	node * temp = hash_table[i];
	while (temp != nullptr && strcmp(temp->animals.name, name_to_find) != 0)
	{
		temp = temp->next;
	}
	if(!temp)
	{
		cout << "No match found" << endl;
		return 0;
	}
	else
	{
		strcpy(animal_info.name, temp->animals.name);
		strcpy(animal_info.sci_name, temp->animals.sci_name);
		strcpy(animal_info.location, temp->animals.location);
		strcpy(animal_info.desc, temp->animals.desc);
		strcpy(animal_info.population, temp->animals.population);
		strcpy(animal_info.life_span, temp->animals.life_span);
		return 1;
	}
}
int table::remove_animal(char * name_to_find)	//Wrapper function for remove_animal
{//Commented out code was originally going to be an iterative solution
	int i {0};
	//int match {0};
	i = hash_function(name_to_find);
	//node * temp = hash_table[i];
	/*if(!hash_table[i]->next && strcmp(temp->animals.name, name_to_find) == 0)//If only one node, and its a match
	{
		delete hash_table[i];
		hash_table[i] = nullptr;
		return 1;
	}*/
	if(!hash_table[i])//strcmp(hash_table[i]->animals.name, name_to_find) == 0)	//If the first node is a match
	{
		/*hash_table[i] = temp->next;
		delete [] temp->animals.name;
		delete [] temp->animals.sci_name;
		delete [] temp->animals.location;
		delete [] temp->animals.desc;
		delete [] temp->animals.life_span;
		delete temp;
		return 1;*/
		return 0;
	}
	return remove_animal(hash_table[i], name_to_find);
}

int table::remove_animal(node * & head, char * name_to_find)	//Recursive call for remove animal
{
	if(!head)
		return 0;	//Reach end of LLL no match
	if(strcmp(head->animals.name, name_to_find) == 0)	//If match then reconnect and delete
	{
		node * temp = head;
		head = head->next;
		delete [] temp->animals.name;
		delete [] temp->animals.sci_name;
		delete [] temp->animals.location;
		delete [] temp->animals.desc;
		delete [] temp->animals.population;
		delete [] temp->animals.life_span;
		delete temp;
		return 1;

	}
	
	return remove_animal(head->next, name_to_find);
}

int table::display_location(char * loca_to_find)	//Searches for a location from the entire table and displays all matches.
{
	int i {0};
	while (i != hash_table_size)
	{
		node * temp = hash_table[i];
		while(temp != nullptr)
		{	
			if(strcmp(temp->animals.location, loca_to_find) == 0)
			{
				cout << "\nIndex: " << i << endl;
				cout << "-Name: " << temp->animals.name << endl;
				cout << "-Sci Name: " << temp->animals.sci_name << endl;
				cout << "-Location: " << temp->animals.location << endl;			
				cout << "-Desc: " << temp->animals.desc << endl;
				cout << "-Population: " << temp->animals.population << endl;
				cout << "-Life Span: " << temp->animals.life_span << endl;
			}
			temp = temp->next;
		}
		++i;
	}
	return i;

}
	
int table::copy_data(animal & to_add, int i)	//Copy function that takes in an animal object and copies it into a node in the table. Only really used for add function
{
	hash_table[i]->animals.name = new char[strlen(to_add.name) + 1];
	strcpy(hash_table[i]->animals.name, to_add.name);

	hash_table[i]->animals.sci_name = new char[strlen(to_add.sci_name) + 1];
	strcpy(hash_table[i]->animals.sci_name, to_add.sci_name);
	
	hash_table[i]->animals.location = new char[strlen(to_add.location) + 1];
	strcpy(hash_table[i]->animals.location, to_add.location);
	
	hash_table[i]->animals.desc = new char[strlen(to_add.desc) + 1];
	strcpy(hash_table[i]->animals.desc, to_add.desc);

	hash_table[i]->animals.population = new char[strlen(to_add.population) + 1];
	strcpy(hash_table[i]->animals.population, to_add.population);
	
	hash_table[i]->animals.life_span = new char[strlen(to_add.life_span) + 1];
	strcpy(hash_table[i]->animals.life_span, to_add.life_span);

	return 0;
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
