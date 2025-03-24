#include "contestant.h"
//Bradley Chang CS302 Program 2
//This file will contain the implementation of the contestant 
using namespace std;

//********CONTESTANT BASE CLASS*************
contestant::contestant(): name(nullptr), position(0), speed(0), distance(0)
{}
contestant::contestant(const char * a_name, int a_position, int a_speed, float a_distance): position(a_position), speed(a_speed), distance(a_distance)
{

}
contestant::contestant(const contestant & source): name(nullptr), position(source.position), speed(source.speed), distance(source.distance)
{
	name = new char[strlen(source.name) + 1];
	strcpy(name, source.name);
}
contestant & contestant::operator= (const contestant & source)
{
	if(&source == this)
		return *this;
	if(source.name)
	{
		if(name)
		{
			delete [] name;
		}
		name = new char[strlen(source.name) + 1];
		strcpy(name, source.name);
	}
	position = source.position;
	speed = source.speed;
	distance = source.distance;
	return *this;
}
contestant::~contestant()
{
	if(name)
	{
		delete [] name;
		name = nullptr;
	}
	position = 0;
	speed = 0;
	distance = 0;
}

ostream & operator<< (ostream & out, const contestant & to_display)	//Might just be a wrapper or could implement display with just this
{
	out << "Name: " << to_display.name << endl;
	out << "Position: " << to_display.position << endl;
	out << "Speed: " << to_display.speed << endl;
	out << "Distance: " << to_display.distance << " meters" << endl;
	return out;
}
void contestant::display() const					//Named display function that << will call.
{
	cout << "Name: " << name << endl;
	cout << "Position: " << position << endl;
	cout << "Speed: " << speed << endl;
	cout << "Distance: " << distance << endl;
}
istream & operator>> (istream & in, contestant & to_insert)	//Insertion operator to input a name
{
	char temp[100];
	cout << "Enter name of contestant: " ;
	in.get(temp, 100, '\n');
	in.ignore(100, '\n');

	if(to_insert.name)
		delete [] to_insert.name;
	to_insert.name = new char[strlen(temp) + 1];
	strcpy(to_insert.name, temp);
	//to_insert.name = temp;

	cout << "Enter average speed: ";
	in >> to_insert.speed;
	in.ignore(100, '\n');
	return in;
}

int contestant::compare(const contestant & op1, const contestant & op2)
{
	return 0;
}

int operator==(const contestant & op1, const contestant & op2) 
{
	//if(/*static_cast<const contestant &> (op1) == op2 &&*/ op1.distance == op2.distance)
	if(strcmp(op1.name, op2.name) == 0)
		return 1;
	return 0;
}
int operator!=(const contestant & op1, const contestant & op2) 
{
	//if(/*static_cast<const contestant &> (op1) != op2 &&*/ op1.distance != op2.distance)
	if(strcmp(op1.name, op2.name) != 0)
		return 1;
	return 0;
}
int operator<(const contestant & op1, const contestant & op2) 
{
	//if(/*static_cast<const contestant &> (op1) < op2 &&*/ op1.distance < op2.distance)
	if(strcmp(op1.name, op2.name) < 0)
		return 1;
	return 0;
}
int operator<=(const contestant & op1, const contestant & op2) 
{
	//if(/*static_cast<const contestant &> (op1) <= op2 &&*/ op1.distance <= op2.distance)
	if(strcmp(op1.name, op2.name) <= 0)
		return 1;
	return 0;
}
int operator>(const contestant & op1, const contestant & op2) 
{
	//if(/*static_cast<const contestant &> (op1) > op2 &&*/ op1.distance > op2.distance)
	if(strcmp(op1.name, op2.name) > 0)
		return 1;
	return 0;
}
int operator>=(const contestant & op1, const contestant & op2) 
{
	//if(/*static_cast<const contestant &> (op1) != op2 &&*/ op1.distance != op2.distance)
	if(strcmp(op1.name, op2.name) >= 0)
		return 1;
	return 0;
}
contestant & contestant::operator+= (const contestant & op2)
{
	distance += op2.speed;
	return *this;
}
int contestant::finish(int finish_distance)					//Determines if contestant is at finish line.
{
	if(distance >= finish_distance)
		return 1;
	return 0;
}
//*********Slime Contestant Class***********
slime::slime(): slime_size(0), amount_absorbed(0), obj_absorbed(nullptr), s_event(" ")
{}
slime::slime(const char * a_name, int a_position, int a_speed, float a_distance, int a_slime_size, int an_amount_absorbed, const char * an_obj_absorbed, const string & a_s_event):
	contestant(a_name, a_position, a_speed, a_distance), slime_size(a_slime_size), amount_absorbed(an_amount_absorbed), s_event(a_s_event)
{}

slime::slime(const slime & source): contestant(source), slime_size(source.slime_size), amount_absorbed(source.amount_absorbed), obj_absorbed(nullptr), s_event(source.s_event)
{
	if(source.obj_absorbed != nullptr)
	{
		obj_absorbed = new char[strlen(source.obj_absorbed) + 1];
		strcpy(obj_absorbed, source.obj_absorbed);
	}
}

slime & slime::operator= (const slime & source)
{
	if(&source == this)
		return *this;
	slime_size = source.slime_size;
	amount_absorbed = source.amount_absorbed;
	if(source.obj_absorbed)
	{
		if(obj_absorbed)
			delete [] obj_absorbed;
		obj_absorbed = new char[strlen(source.obj_absorbed) + 1];
		strcpy(obj_absorbed, source.obj_absorbed);
	}
	s_event = source.s_event;
	return *this;	
}

slime::~slime()
{
	slime_size = 0;
	amount_absorbed = 0;
	if(obj_absorbed)
	{
		delete [] obj_absorbed;
		obj_absorbed = nullptr;
	}
}

ostream & operator<< (ostream & out, const slime & to_display)		//Wrapper for display
{
	out << static_cast<const contestant &>(to_display);
	out << "Slime Size: " << to_display.slime_size << endl;
	out << "Items Absorbed: " << to_display.amount_absorbed << endl;
	out << "Object Absorbed: " << to_display.obj_absorbed << endl;
	return out;
}

void slime::display() const						//Named display function
{}

istream & operator>> (istream & in, slime & to_insert)		//Insertion operator for slime name?
{
	in >> static_cast<contestant &>(to_insert);
	
	cout << "Enter Slime Starting Size (meters^3): ";
	in >> to_insert.slime_size;
	in.ignore(100, '\n');
	
	char temp[] = "Nothing";
	if(to_insert.obj_absorbed)
		delete [] to_insert.obj_absorbed;
	to_insert.obj_absorbed = new char[strlen(temp) + 1];
	strcpy(to_insert.obj_absorbed, temp);


	
	return in;
}

int slime::adjust_size(int amount_absorbed)				//Adjusts size of slime based on amount of items absorbed
{
	return 0;
}
int slime::random_slime_event()						//Random slime events with size being the amount of contestants in the race.
{
	int random {0};
	srand(time(nullptr));
	random = rand() % 10;
	if(random == 1)
	{
		cout << "Slime encountered a warrior!" << endl;
		cout << "-20 meters" << endl;
		distance -= 20;
	}
	else if(random == 2)
	{
		cout << "Slime encountered a trampoline!" << endl;
		cout << "+20 meters" << endl;
		distance += 20;
	}
	else
	{
		cout << "No events to report" << endl;
	}
	return 1;
	
}

//********Zombie Contestant Class**********
zombie::zombie(): brains(0), z_event(" ")
{}
zombie::zombie(const char * a_name, int a_position, int a_speed, float a_distance, int a_brain, const string & a_z_event):
	contestant(a_name, a_position, a_speed, a_distance), brains(a_brain), z_event(a_z_event)
{}
ostream & operator<< (ostream & out, const zombie & to_display)
{
	out << static_cast<const contestant &>(to_display);
	out << "Brains eaten: " << to_display.brains << endl;
	return out;
}
void zombie::display () const
{}
istream & operator>> (istream & in, zombie & to_insert)
{
	in >> static_cast<contestant &>(to_insert);
	cout << "Enter Amount of Starting Brains: ";
	in >> to_insert.brains;
	in.ignore(100, '\n');

	return in;
}
int zombie::adjust_speed(int brains)	//Adjusts speed based on brains eaten
{
	return 0;
}
int zombie::random_zombie_event()	//Randome zombie events for zombies to encounter.
{
	int random {0};
	srand(time(nullptr));
	random = rand() % 10;
	
	if (random == 1)
	{
		cout << "Zombie has eaten a brain!" << endl;
		cout << "+1 Brain" << endl;
		++brains;
	}
	else if (random == 2)
	{
		cout << "Zombie has eaten an energy bar!" << endl;
		cout << "+20 meters" << endl;
		distance += 20;
	}
	else if (random == 3)
	{
		cout << "Zombie has encountered armed survivors!" << endl;
		cout << "-20 meters" << endl;
		distance -= 20;
	}
	else
	{
		cout << "No events to report" << endl;
	}

	return 0;
}

//********Dragon Contestant Class*********
dragon::dragon(): elevation(0), d_event(" ")
{}
dragon::dragon(const char * a_name, int a_position, int a_speed, float a_distance, int an_elevation, const string & a_d_event):
	contestant(a_name, a_position, a_speed, a_distance), elevation(an_elevation), d_event(a_d_event)
{}
ostream & operator<< (ostream & out, const dragon & to_display)
{
	out << static_cast<const contestant &>(to_display);
	out << "Elevation (meters): " << to_display.elevation << endl;
	return out;
}
void dragon::display() const
{}
istream & operator>> (istream & in, dragon & to_insert)
{	
	in >> static_cast<contestant &>(to_insert);

	cout << "Enter starting elevation (meters): ";
	in >> to_insert.elevation;
	in.ignore(100, '\n');

	return in;
}
int dragon::adjust_speed(int elevation)	//Adjusts speed based on elevation
{
	return 0;
}
int dragon::random_dragon_event()		//Random dragon events for dragons to encounter.
{
	int random {0};
	srand(time(nullptr));
	random = rand() % 10;
	
	if(random == 1)
	{
		cout << "Dragon is pushed along by a gust of wind!" << endl;
		cout << "+100 meters in distance" << endl;
		distance += 100;
	}
	else if(random == 2)
	{
		cout << "Dragon has encountered Anti-Air Flak Cannons!" << endl;
		cout << "-200 meters in distance" << endl;
		distance -= 200;
	}
	else if(random == 3)
	{
		cout << "Dragon has to fly up to avoid a mountain!" << endl;
		cout << "+150 meters in elevation" << endl;
		elevation += 150;
	}
	else if(random == 4)
	{
		cout << "Dragon has to fly down to terrorize a village!" << endl;
		cout << "Dragon flew down to 50 meters in elevation" << endl;
		elevation = 50;
	}
	else
	{
		cout << "No events to report" << endl;
	}

	return 0;
}
