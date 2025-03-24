//Bradley Chang CS302 Program 3
//This file contains the class declarations of the node class and the 234tree class

#include "ice_cream.h"
#include <memory>

class node
{
	public:
		//Typedefs
		typedef unique_ptr<ice_cream> data_type;

		//Constructors and constructors with args
		node();
		node (const data_type & source);
		
		//Setters and getters for child nodes and data.
		node * & get_child(int i);
		void set_child(node * new_child, int i);
		data_type & get_data(int i);

		void display(int i) const;	//Displays data in a single node
		
		int sort_data();		//Sorts the data in the node.

	private:
		data_type data[3];
		node * child[4];

};


class Btree
{
	public:
		//Typedefs
		typedef unique_ptr<ice_cream> data_type;
		
		//Constructor, destructor, copy constructor, and assignment op 
		Btree();
		~Btree();
		Btree(const Btree & source);
		Btree & operator= (const Btree & source);

		//Wrapper functions for insert, remove_all, and display
		int insert(data_type & new_data);
		int remove_all();
		void display();

		//Other functions
		bool is_root_full(node * root);	//Returns true if root is full

	private:
		//Recursive functions
		int insert(node * & root, data_type & new_data);
		int remove_all(node * & root);
		void display(node * root);
		void copy(node *& dest, node * source);

		//Data members
		node * root;

};
