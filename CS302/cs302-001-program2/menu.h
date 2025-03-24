#include "contestant.h"
#include "DLL.h"
//Bradley Chang CS302 Program #2
//menu.h file contains the menu class, menu function prototypes and DLL 
class menu
{
	public:
		~menu();
		int main_menu();
		int slime_menu();
		int zombie_menu();
		int dragon_menu();
		bool again();
	private:
		DLL <slime> slime_obj;
		DLL <zombie> zombie_obj;
		DLL <dragon> dragon_obj;

		slime slime_data;
		zombie zombie_data;
		dragon dragon_data;

};
