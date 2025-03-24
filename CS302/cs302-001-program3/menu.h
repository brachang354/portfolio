//Bradley Chang CS302 Program 3
//This file will contain the menu class declaration.
#include "234tree.h"

class menu
{
	public:
		int main_menu();
		int sandwich_menu();
		int cake_menu();
		int pancake_menu();
		bool again();
	private:
		unique_ptr<ice_cream> i_ptr;	
		Btree tree;
};
