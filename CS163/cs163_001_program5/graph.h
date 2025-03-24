#include <string>
#include <cstring>
#include <cctype>
#include <iostream>

using namespace std;

//Bradley Chang CS163_001 Program 5. Purpose of this file is to contain the vertex struct, node struct for the adjacency list,
//and the table ADT with all of its function prototypes

struct route
{
	string location;
	string desc;
};

struct vertex
{
	route * entry;
	struct node * head;
};

struct node
{
	vertex * adjacent;
	node * next;
};

class table
{
	public:
		table(int size = 5);
		~table();
		int insert_vertex(route & to_add);
		int insert_edge(string current_vertex,string to_attach);
		int find_location(string key_value);
		int display_adjacent();

	private:
		vertex * adjacency_list;
		int list_size;
		int display_adjacent(node * head);
};
bool again();
