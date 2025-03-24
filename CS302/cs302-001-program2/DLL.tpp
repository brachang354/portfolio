#ifndef DLL_TPP
#define DLL_TPP
#include <iostream>
#include "error.h"
using std::cout;
using std::endl;
//Bradley Chang CS302 Program 2
//This is the DLL.tpp file which will contian the implementation of the node class and DLL class

//******Node Class Implementation******
template <typename TYPE>
node<TYPE>::node(): next(nullptr), prev(nullptr)
{}

template <typename TYPE>
node<TYPE>::node(const TYPE & source): data(source), next(nullptr), prev(nullptr)
{
	//data = source.data;
}

template <typename TYPE>
typename node<TYPE>::node_ptr_type & node<TYPE>::get_next()
{
	return next;
}

template <typename TYPE>
typename node<TYPE>::node_ptr_type & node<TYPE>::get_prev()
{
	return prev;
}

template <typename TYPE>
void node<TYPE>::set_next(node_ptr_type new_next)
{
	next = new_next;
}

template <typename TYPE>
void node<TYPE>::set_prev(node_ptr_type new_prev)
{
	prev = new_prev;
}

template <typename TYPE>
bool node<TYPE>::has_next()
{
	return next != nullptr;
}

template <typename TYPE>
TYPE & node<TYPE>::get_data()
{
	return data;
}

template <typename TYPE>
void node<TYPE>::display() const		//Displays contents of a single node
{
	cout << data;
}

template <typename TYPE>
int node<TYPE>::increment_distance(const TYPE & speed)	//Increments distance of contestant by speed.
{
	data += speed;
	return 1;
}


//*******DLL Class Implementation********
template <typename TYPE>
DLL<TYPE>::DLL(): head(nullptr), tail(nullptr)
{}

template <typename TYPE>
DLL<TYPE>::~DLL()
{
	remove_all();
}	

template <typename TYPE>
DLL<TYPE>::DLL(const DLL<TYPE> & source)	//Copy constructor
{
	if(!source.head)
	{
		head = nullptr;
	}
	else
	{
		copy(head, source.head);
	}
}
template <typename TYPE>
void DLL<TYPE>::copy(node_ptr & dest, const node_ptr source)
{
	if(!source)	//At the end of source list. Done copying
	{
		dest = nullptr;
		return;
	}
	if(!head)	//First item being copied or only one item being copied. In this case dest is a reference to head and therefore should change head.
	{
		dest = new node_type(source->get_data());
		dest->get_next() = nullptr;
		dest->get_prev() = nullptr;
		tail = dest;
	}
	else		//Else items being copied when node(s) already exist in dest
	{
		dest = new node_type(source->get_data());
		dest->get_next() = nullptr;
		dest->get_prev() = tail;
		tail = dest;
		
	}
	copy(dest->get_next(), source.head->get_next());
}
	
template <typename TYPE>
DLL<TYPE> & DLL<TYPE>::operator= (const DLL<TYPE> & source)
{
	if(this == &source)
		return *this;
	remove_all();
	
	copy(head, source.head);
	return *this;
}
template <typename TYPE>
int DLL<TYPE>::remove_all()
{
	if(!head)
		return 0;
	tail = nullptr;
	return remove_all(head);	
}
template <typename TYPE>	
int DLL<TYPE>::remove_all(node_ptr & head)
{
	if(!head)
		return 0;
	remove_all(head->get_next());
	head->get_prev() = nullptr;
	//delete data;	//Deallocate data
	delete head;
	head = nullptr;
	return 0;
	
}

template <typename TYPE>
int DLL<TYPE>::insert(const TYPE & new_data)	//Wrapper insert
{
	if(!head)	//Empty list. Inserting 
	{
		head = new node_type(new_data);

		tail = head;
		//head->set_next(nullptr);
		//head->set_prev(nullptr);
		head->get_next() = nullptr;
		head->get_prev() = nullptr;
		return 1;
	}
	return insert(head, new_data);
}
template <typename TYPE>
int DLL<TYPE>::insert(node_ptr & head, const TYPE & new_data)	//Recursive insert
{	
	//Adding at end
	if(!head)
	{
		node_ptr temp = new node_type(new_data);
		temp->get_next() = nullptr;
		temp->get_prev() = tail;
		head = temp;
		this->tail = temp;
		return 1;
	}

	//Adding before head
	if(new_data <= this->head->get_data())
	{
		node_ptr temp = new node_type(new_data);
		temp->get_next() = head;
		head->get_prev() = temp;
		temp->get_prev() = nullptr;
		this->head = temp;
		return 1;
	}
	//Adding between
	if(new_data <= head->get_data())
	{
		node_ptr temp = new node_type(new_data);
		temp->get_next() = head;	
		temp->get_prev() = head->get_prev();
		head->get_prev() = temp;
		head = temp;
		return 1;
	}
	return insert(head->get_next(), new_data);
}

//Display Wrapper
template <typename TYPE>
void DLL<TYPE>::display() const
{
	if(!head)
		return;
	int count {0};
	display(head, count);
	cout << endl;
}

//Display Recursive
template <typename TYPE>
void DLL<TYPE>::display(const node_ptr head, int count) const
{
	if(!head)
		return;
	cout << "Contestant #" << count << endl;
	head->display();
	cout << endl;
	display(head->get_next(), count + 1);
}

template <typename TYPE>
int DLL<TYPE>::increment_distance()
{
	if(!head)
		return 0;
	return increment_distance(head);

}

template <typename TYPE>
int DLL<TYPE>::increment_distance(node_ptr & head)
{
	if(!head)
		return 0;
	head->increment_distance(head->get_data());

	return increment_distance(head->get_next());
}

template <typename TYPE>
TYPE & DLL<TYPE>::get_data(int index)
{
	/*try
	{
		if(!head)
			throw TYPE;
		int count {0};
		return get_data(head, index, count);
	}
	catch(TYPE)
	{
		cerr << "List is empty" << endl;
	}*/
	EMPTY empty_error;
	if(!head)
		throw empty_error;
	int count {0};
	return get_data(head, index, count);
}


template <typename TYPE>
TYPE & DLL<TYPE>::get_data(const node_ptr head, int index, int count)
{
	/*try
	{
		if(!head)
			throw TYPE("END ERROR");
		if(index == count)
		{
			return head->get_data();
		}
		return get_data(head->get_next(), index, count + 1);
	}

	catch(TYPE)
	{
		cerr << "Invalid index. Item not found." << endl;
	}*/
	BAD_INDEX index_error;
	if(!head)
		throw index_error;
	if(index == count)
		return head->get_data();
	return get_data(head->get_next(), index, count + 1);
	
}


#endif
