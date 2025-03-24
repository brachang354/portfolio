#ifndef DLL_H
#define DLL_H
//Bradley Chang CS302 Program 2
//Purpose of this file is to contain the template prototype of the node class, and DLL class
using namespace std;

template <typename TYPE>
class node
{
	public:
		typedef node<TYPE>* node_ptr_type;

		node<TYPE>();
		node<TYPE>(const TYPE & source);
		
		//Getters and setters for next and prev
		node_ptr_type & get_next();
		node_ptr_type & get_prev();
		void set_next(node_ptr_type new_next);
		void set_prev(node_ptr_type new_prev);
		
		bool has_next();

		TYPE & get_data();
		
		void display() const;				//Displays contents of a single node
		int increment_distance(const TYPE & speed);	//Increments distance of contestant by speed.
	private:
		TYPE data;
		node_ptr_type next;
		node_ptr_type prev;
	
};

template <typename TYPE>
class DLL
{
	public:
		typedef node<TYPE> node_type;
		typedef node_type * node_ptr;
		
		//Constructor and copy constructor
		DLL();
		DLL(const DLL<TYPE> & source);
		~DLL();	
	
		int insert(const TYPE & new_data);
		void display() const;
		DLL<TYPE> & operator= (const DLL<TYPE> & source);
		int remove_all();
		int increment_distance();			//Wrapper for incrementing distance
		TYPE & get_data(int index);			//Gets the data type at a specified index.
	private:
		node_ptr head;
		node_ptr tail;

		//Recursive function calls
		int insert(node_ptr & head, const TYPE & new_data);
		void display(const node_ptr head, int count) const;
		void copy(node_ptr & dest, const node_ptr source);	
		int remove_all(node_ptr & head);
		int increment_distance(node_ptr & head);
		TYPE & get_data(const node_ptr head, int index, int count);
};


#include "DLL.tpp"
#endif
