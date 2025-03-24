#include "graph.h"

using namespace std;

//Bradley Chang CS163_001 Program #5. Purpose of this file is to contain the implementation of public table functions

table::table(int size)
{
	list_size = size;
	adjacency_list = new vertex[size];
	int i {0};
	while (i != size)
	{
		adjacency_list[i].head = nullptr;
		adjacency_list[i].entry = nullptr;
		++i;
	}
}
table::~table()
{
	int i {0};
	while(i != list_size)
	{
		node * hold = adjacency_list[i].head;
		while(adjacency_list[i].head)
		{
			hold = adjacency_list[i].head->next;
			delete adjacency_list[i].head;
			adjacency_list[i].head = hold;
		}
		++i;
	}	
	delete [] adjacency_list;
}
int table::insert_vertex(route & to_add)
{
	int i {0};
	while(i != list_size && adjacency_list[i].entry)
		++i;
	if(i == list_size)
		return 0;
	adjacency_list[i].entry = new route;
	adjacency_list[i].entry->location = to_add.location;
	adjacency_list[i].entry->desc = to_add.desc;
	return 1;
}
int table::insert_edge(string current_vertex, string to_attach)
{
	int current_i {0};
	int attach_i {0};
	current_i = find_location(current_vertex);
	attach_i = find_location(to_attach);
	if(current_i == list_size || attach_i == list_size)
		return 0;
	if(current_i == -1 || attach_i == -1)
		return 0;
	node * hold = adjacency_list[current_i].head;
	adjacency_list[current_i].head = new node;
	adjacency_list[current_i].head->adjacent = &adjacency_list[attach_i];
	adjacency_list[current_i].head->next = hold;
	return 1;
	
}
int table::find_location(string key_value)
{
	int i {0};
	while (i < list_size /*&& adjacency_list[i].entry->location != key_value*/)
	{
		if(!adjacency_list[i].entry)
			return -1;
		if(adjacency_list[i].entry->location == key_value)
			return i;
		++i;
	}
	/*cout << i << endl;
	return i;*/
}
int table::display_adjacent()
{
	int i {0};
	while (i != list_size && adjacency_list[i].entry)
	{
		cout << "\nIndex: " << i << endl;
		cout << "Location: " << adjacency_list[i].entry->location << endl;
		cout << "Desciption: " << adjacency_list[i].entry->desc << endl;
		cout << "Connected to..." << endl;
		display_adjacent(adjacency_list[i].head);
		++i;
	}
	return 1;
}
int table::display_adjacent(node * head)
{
	if(!head)
		return 0;
	cout << "-Location: " << head->adjacent->entry->location << endl;
	cout << "-Desciption: " << head->adjacent->entry->desc << endl;
	display_adjacent(head->next);
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

