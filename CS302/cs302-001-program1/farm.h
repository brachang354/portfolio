//Bradley Chang CS302_001 Program 1. Farm activities

#include <string>
#include <cstring>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>
using namespace std;
//This file will contain the core hierarchy of the class structure
//Activity is the base class and corn maze, egg hunt, and berry picking will be the derived classes

class activity
{
	public: 
		activity();	//Constructor
		~activity();	//Destructor
		void display() const;	//Display function
		activity(const activity & source);	//Copy Constructor
		activity(const char * a_name, int a_time, int a_cost);	//Constructor w/ args
		activity & operator= (const activity & source);

		int get_guestname();	//Get the guest's name
		int guest_amount();	//Get group size of guests
		int activity_cost();	//Getting the cost of an activity
	protected: 
		char * guest_name;	//Name of activity
		int schedule_time;	//Scheduled time of activity
		int cost;		//Fee of activity that customers pay
};

class corn_maze: public activity	//Will use a CLL data structure
{
	public:
		corn_maze();	//Constructor
		~corn_maze();	//Destructor
		corn_maze(const char * a_name, int a_time, int a_cost, int a_stamp, int maze_time, int a_difficulty);	//Constructor w/ args
		int stamp_count();	//Count the stamps that guests acquire
		int maze_time();	//Track time that guests spend in maze
		int maze_difficulty();	//Guests can select what maze difficulty they want
		void display() const;	//Display
	protected:
		int stamps;	//Amount of stamps
		int time;	//Amount of time spent in maze
		int difficulty;	//Difficulty of maze
};

class egg_hunt: public activity		//Will use a ARR data structure
{
	public:
		egg_hunt();	//Constructor
		~egg_hunt();	//Destructor
		egg_hunt(const char * a_name, int a_time, int a_cost, int a_egg_count, int a_start_time, const char * a_prize);	//Constructor w/ args
		
		int count_eggs();	//Counts eggs that guests find
		int start_times();	//Keeps track of egg hunt start times
		int start_race();	//Starts the egg hunt	
		void display() const;	//Display
				
	protected:
		int eggs_count;	//Amount of eggs
		int times;	//Start times
		char * prize;	//Type of prize a guest can receive
};

class berry_picking: public activity	//Will use a vector data structure
{
	public:
		berry_picking();	//Constructor
		//~berry_picking();	//Destructor
		berry_picking(const char * a_name, int a_time, int a_cost, const string & a_type, int a_berry_count, int a_berry_weight);
		//berry_picking(const berry_picking & source);
		
		int berry_count();	//Keeps track of the amount of berries
		int berry_weight();	//Keeps track of the weight of berries
		int berry_type();	//Allows customers to pick different types of berries they want to pick
		void display() const;	//Display

	protected:
		string type;	//Type of berry
		int b_count;	//Count of berries
		int b_weight;	//Weight of berries
};
bool again();
