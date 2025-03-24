#include "d_struct.h"

class menu
{
	public:
		menu();
		~menu();
		int main_menu();	//Main menu function to choose an activity
		int corn_menu();	//Corn menu to handle corn maze actions
		int egg_menu();		//Egg menu to handle egg hunt actions
		int berry_menu();	//Berry menu to handle berry picking actions
	
	private:
		CLL_corn CLL;
		//ARR_egg ARR;
		vector <berry_picking> v_berry;
};
