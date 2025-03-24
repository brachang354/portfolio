#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <time.h>
//#include "DLL.h"
using namespace std;
//Bradley Chang CS302_001 Program #2
//This is the contestant .h file that'll contain the class definitions of the contestant base class
//and its derived classes of slime, zombie, and dragon

class contestant
{
	public:
		//Default constructor, constructor with args, copy constructor, assginment op, and destructor
		contestant();
		contestant(const char * a_name, int a_position, int a_speed, float a_distance);
		contestant(const contestant & source);
		contestant & operator= (const contestant & source);
		~contestant();

		friend ostream & operator<< (ostream & out, const contestant & to_display);	//Might just be a wrapper or could implement display with just this
		void display() const;								//Named display function that << will call.
		friend istream & operator>> (istream & in, contestant & to_insert);	//Insertion operator to input a name
	
		//Relational and equality operators to compare contestants' distance.
		friend int operator==(const contestant & op1, const contestant & op2);
		friend int operator!=(const contestant & op1, const contestant & op2);
		friend int operator<(const contestant & op1, const contestant & op2);
		friend int operator<=(const contestant & op1, const contestant & op2);
		friend int operator>(const contestant & op1, const contestant & op2);
		friend int operator>=(const contestant & op1, const contestant & op2);
		
		//Named compare function for relational/equality operators to call
		int compare(const contestant & op1, const contestant & op2);
		
		//Binary operators to increment distance by speed
		contestant & operator+= (const contestant & op2);		

		int finish(int finish_distance);					//Determines if contestant is at finish line. Returns True when distance >= finish_distance
	protected:
		char * name;	//Name of contestant
		int position;	//Contestant's position in race. 
		int speed;	//Contestant's speed throughout the race
		float distance;	//Distance remaining for contestant to finish the race
};

class slime: public contestant
{
	public:
		//Default constructor, constructor with args, copy constructor, assginment op, and destructor
		slime();
		slime(const char * a_name, int a_position, int a_speed, float a_distance, int a_slime_size, int an_amount_absorbed, const char * an_obj_absorbed, const string & a_s_event);
		slime(const slime & source);
		slime & operator= (const slime & source);
		~slime();

		friend ostream & operator<< (ostream & out, const slime & to_display);		//Wrapper for display
		void display() const;								//Named display function
		friend istream & operator>> (istream & in, slime & to_insert);			//Insertion operator for slime name?
		int adjust_size(int amount_absorbed);						//Adjusts size of slime based on amount of items absorbed
		int random_slime_event();						//Random slime events with size being the amount of contestants in the race.
	protected:
		int slime_size;		//Size of slime
		int amount_absorbed;	//Amount of objects slime absorbs
		char * obj_absorbed;	//Named items that slime absorbs
		string s_event;		//Random events unique to slime contestants
};

class zombie: public contestant
{
	public:
		//Default constructor, constructor with args
		zombie();
		zombie(const char * a_name, int a_position, int a_speed, float a_distance, int a_brain, const string & a_z_event);

		friend ostream & operator<< (ostream & out, const zombie & to_display);
		void display () const;
		friend istream & operator>> (istream & in, zombie & to_insert);
		int adjust_speed(int brains);	//Adjusts speed based on brains eaten
		int random_zombie_event();	//Randome zombie events for zombies to encounter.
	protected:
		int brains;		//Amount of brains zombie has eaten
		string z_event;		//Random events unique to zombie contestants
};

class dragon: public contestant
{
	public:
		//Default constructor, constructor with args
		dragon();
		dragon(const char * a_name, int a_position, int a_speed, float a_distance, int an_elevation, const string & a_d_event);
		
		friend ostream & operator<< (ostream & out, const dragon & to_display);
		void display() const;
		friend istream & operator>> (istream & in, dragon & to_insert);
		int adjust_speed(int elevation);	//Adjusts speed based on elevation
		int random_dragon_event();		//Random dragon events for dragons to encounter.
	protected:
		int elevation;		//Elevation that dragon flies at
		string d_event;		//Random events unique to dragon contestants
};
