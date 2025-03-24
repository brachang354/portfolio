#include "header.h"

int main()
{
	node * head = nullptr;

	do
	{
	insertFood(head);
	}while(again());

	display(head);

	destroy(head);
	
	return 0;
}
