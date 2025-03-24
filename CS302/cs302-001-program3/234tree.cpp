//Bradley Chang CS302 Program #3
//This file contains the implementation of the node and 234tree functions.
#include "234tree.h"

//******NODE CLASS******
node::node()
{
	for(int i {0}; i < 4; ++i)
		child[i] = nullptr;
	for(int i {0}; i < 3; ++i)
		data[i].reset();
}

//node::node(const ice_cream *& source)
/*node::node (const data_type & source)
{
	//1. Container to hold new data
	//2. Reset data's unique ptr
	//3. Point to container with our unique ptr
	//4. Look into make_unique
	//5. Look into move with unique ptr
	//for(int i {0}; i < 3; ++i)
	//	data[i] = source;

	for(int i {0}; i < 4; ++i)
		child[i] = nullptr;
}
*/
node * & node::get_child(int i)
{
	return child[i];
}

void node::set_child(node * new_child, int i)
{
	child[i] = new_child;
}

typedef unique_ptr<ice_cream> data_type;
data_type & node::get_data(int i)
{
	return data[i];
}

void node::display(int i) const	//Displays data in a single node
{
	data[i]->display();
	cout << endl;
}
int node::sort_data()		//Sorts the data in the node.
{
	//Perform selection sort to sort the data.
	int i, j, min_idx;
	for(i = 0; i < 2; ++i)
	{
		min_idx = i;
		for(j = i + 1; j < 3; ++j)
		{
			if(data[j] < data[min_idx])
				min_idx = j;
		}

		if(min_idx != i)
			swap(data[min_idx], data[i]);
	}

	return 0;
}


//******234 B-Tree Class**********
Btree::Btree(): root(nullptr)
{}

Btree::~Btree()
{
	remove_all();
}

int Btree::insert(data_type & new_data)
{//Wrapper function for insert.
	//int i {0};
	if(!root)	//Tree is empty make the first node
	{
		root = new node;
		root->get_data(0) = move(new_data);
		//++i;
		return 1;
	}
	/*if(is_root_full(root) != false)	//If the root is not full then we keep adding data into the node;
	{
		root->get_data(i) = move(new_data);
		++i;
		return 1;
	}*/
	return insert(root, new_data);
}

int Btree::insert(node * & root, data_type & new_data)
{
	if(!root)
	{
		root = new node;
		root->get_data(0) = move(new_data);
		return 1;
	}

	if(new_data < root->get_data(0))
		return insert(root->get_child(0), new_data);
	return insert(root->get_child(3), new_data);
	
}

int Btree::remove_all()
{
	if(!root)
		return 0;
	return remove_all(root);
}

int Btree::remove_all(node * & root)
{
	if(!root)
		return 0;
	remove_all(root->get_child(0));
	remove_all(root->get_child(1));
	remove_all(root->get_child(2));
	remove_all(root->get_child(3));

	delete root;
	root = nullptr;
	return 1;
}

void Btree::display()
{
	if(!root)
		return;
	display(root);
}
void Btree::display(node * root)
{
	if(!root)
		return;
	display(root->get_child(0));
	display(root->get_child(1));
	
	/*for(int i = 0; i < 3; i++)
	{
		if(root->get_child(i))
			root->display(i);
	}*/
	root->display(0);

	display(root->get_child(2));
	display(root->get_child(3));
}

bool Btree::is_root_full(node * root)	//Returns true if root is full
{
	for(int i = 0; i < 3; ++i)
	{
		if(root->get_data(i) == nullptr)	//One of the data members is null meaning theres still space and the node is not full.
			return false;
	}
	return true;
}

//Copy Constructor
Btree::Btree(const Btree & source)
{
	if(!source.root)
		root = nullptr;
	else
		copy(root, source.root);

}

//Assignment operator
Btree & Btree::operator= (const Btree & source)
{
	if(this == &source)
		return *this;
	remove_all();

	copy(root, source.root);
	return *this;
}

//Copy function
void Btree::copy(node *& dest, node * source)
{
	if(!source)
		return;
	dest = new node;
	dest->get_data(0) = move(source->get_data(0));

	copy(dest->get_child(0), source->get_child(0));
	copy(dest->get_child(1), source->get_child(1));
	copy(dest->get_child(2), source->get_child(2));
	copy(dest->get_child(3), source->get_child(3));
}
