//Bradley Chang CS302_001 Program 1
#include "menu.h"
using namespace std;

//**********Activity Base Class implementation***********
//Constructor
activity::activity():guest_name(nullptr), schedule_time(0), cost(0)
{}
//Destructor
activity::~activity()
{
	//delete [] guest_name;
	//guest_name = nullptr;
}
//Display. Displays all data members belonging to the activity class
void activity::display() const
{
	cout << "Guest name: " << guest_name << endl;
	cout << "Schedule time: " << schedule_time << endl;
	cout << "Activity cost: " << cost << endl;
}

//Copy Constructor
activity::activity(const activity & source):guest_name(source.guest_name), schedule_time(source.schedule_time), cost(source.cost)
{}	
//Constructor with args
activity::activity(const char * a_name, int a_time, int a_cost):schedule_time(a_time), cost(a_cost)
{
	guest_name = new char[strlen(a_name) + 1];
	strcpy(guest_name, a_name);
}

//Assignment operator
activity & activity::operator= (const activity & source)
{
	if(&source == this)
		return *this;
	schedule_time = source.schedule_time;
	cost = source.cost;
	if(source.guest_name)
	{
		if(guest_name)
		{
			delete [] guest_name;
		}
		guest_name = new char[strlen(source.guest_name) +1];
		strcpy(guest_name, source.guest_name);
	}
	return *this;
}

int activity::get_guestname()	//Get the guest's name
{
	cout << "Enter guest name: " << endl;
	string name;
	getline(cin, name);

	return 0;
}		
int activity::guest_amount()	//Get group size of guests
{
	int amount {0};
	cout << "Enter amount of additional guests: ";
	cin >> amount;
	cout << "Guest amount: " << amount << endl;
	return amount;
}		
int activity::activity_cost()	//Getting the cost of an activity
{
	int cost {0};
	cost = (rand() % 20) + 10;
	cout << "Activity cost: " << cost << endl;	

	return cost;
}

//*********Corn Maze Class implementation**********
corn_maze::corn_maze():stamps(0), time(0), difficulty(0)	//Constructor
{}
corn_maze::~corn_maze()		//Destructor
{}
corn_maze::corn_maze(const char * a_name, int a_time, int a_cost, int a_stamp, int maze_time, int a_difficulty):	//Constructor with args	
	activity(a_name, a_time, a_cost), stamps(a_stamp), time(maze_time), difficulty(a_difficulty)
{}

int corn_maze::stamp_count()	//Count the stamps that guests acquire
{
	return 0;
}
int corn_maze::maze_time()	//Track time that guests spend in maze
{
	return 0;
}
int corn_maze::maze_difficulty()	//Guests can select what maze difficulty they want
{
	return 0;
}
void corn_maze::display() const	//Display
{
	activity::display();
	cout << "Stamps: " << stamps << endl;
	cout << "Time spent: " << time << endl;
	cout << "Difficulty level: " << difficulty << endl;
}
//********Egg Hunt Class implementation************
egg_hunt::egg_hunt():eggs_count(0), times(0)	//Constructor
{}
egg_hunt::~egg_hunt()	//Destructor
{}		
egg_hunt::egg_hunt(const char * a_name, int a_time, int a_cost, int a_egg_count, int a_start_time, const char * a_prize):	//Constructor w/ args
	activity(a_name, a_time, a_cost), eggs_count(a_egg_count), times(a_cost)
{
	prize = new char[strlen(a_prize) + 1];
	strcpy(prize, a_prize);
}
int egg_hunt::count_eggs()	//Counts eggs that guests find
{
	return 0;
}
int egg_hunt::start_times()	//Keeps track of egg hunt start times
{
	return 0;
}
int egg_hunt::start_race()	//Starts the egg hunt	
{
	return 0;
}
void egg_hunt::display() const	//Display
{

}

//********Berry Picking Class implementation********
berry_picking::berry_picking(): type(" "), b_count(0), b_weight(0)		//Constructor
{}
/*berry_picking::~berry_picking()		//Destructor
{}*/
berry_picking::berry_picking(const char * a_name, int a_time, int a_cost, const string & a_type, int a_berry_count, int a_berry_weight):
	activity(a_name, a_time, a_cost), type(a_type), b_count(a_berry_count), b_weight(a_berry_weight)
{}
//berry_picking::berry_picking(const berry_picking & source): type(nullptr), b_count(source.b_count), b_weight(source.b_weight)  
//{}
int berry_picking::berry_count()	//Keeps track of the amount of berries
{
	return 0;
}
int berry_picking::berry_weight()	//Keeps track of the weight of berries
{
	return 0;
}
int berry_picking::berry_type()		//Allows customers to pick different types of berries they want to pick
{
	return 0;
}
void berry_picking::display() const	//Display
{
	activity::display();
	cout << "Type of berry: " << type << endl;
	cout << "Count of berries: " << b_count << endl;
	cout << "Weight of berries: " << b_weight << endl;
}

//*******Again function ******
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
