//Bradley Chang CS302 Program #3
//This file contains the implementation of the ice cream core hiearchy

#include "ice_cream.h"

//*******ICE CREAM BASE CLASS********
ice_cream::ice_cream(): total_sales(0), price(0), flavor(" "), item_id(0){}

ice_cream::ice_cream(float a_sale, float a_price, const string & a_flavor, int an_id):
	total_sales(a_sale), price(a_price), flavor(a_flavor), item_id(an_id){}

ice_cream::~ice_cream()
{
	total_sales = 0;
	price = 0;
	flavor = " ";
	item_id = 0;
}

void ice_cream::display() const		//Displays info about the dessert.
{
	cout << "Item ID #: " << item_id << endl;
	cout << "Total sales: $" << total_sales << endl;
	cout << "Price: $" << price << endl;
	cout << "Flavor: " << flavor << endl;
}		
int ice_cream::insert()
{
	cout << "Input Item ID #: ";
	cin >> item_id;
	cin.ignore(100, '\n');

	cout << "Input starting sales: $";
	cin >> total_sales;
	cin.ignore(100, '\n');

	cout << "Input price: $";
	cin >> price;
	cin.ignore(100, '\n');

	cout << "Input flavor: ";
	getline(cin, flavor);
	//cin.ignore(100, '\n');
	return 0;
}

float ice_cream::purchase()
{
	
	return 0;
}		

float ice_cream::refund()
{

	return 0;
}	

float ice_cream::discount()
{

	return 0;
}
/*
int ice_cream::eat_dessert()
{
	return 0;
}
*/
bool operator<(const ice_cream & op1, const ice_cream & op2)
{
	if(op1.item_id < op2.item_id)
		return true;
	return false;
}
bool operator>(const ice_cream & op1, const ice_cream & op2)
{
	if(op1.item_id > op2.item_id)
		return true;
	return false;
}
bool operator<=(const ice_cream & op1, const ice_cream & op2)
{
	if(op1.item_id <= op2.item_id)
		return true;
	return false;
}
bool operator>=(const ice_cream & op1, const ice_cream & op2)
{
	if(op1.item_id >= op2.item_id)
		return true;
	return false;
}
//*******ICE CREAM SANDWICH CLASS******
sandwich::sandwich(): cookie_type(" "), shape(" ") {}

sandwich::sandwich(float a_sale, float a_price, const string & a_flavor, int an_id, const string & a_type, const string & a_shape):
	ice_cream(a_sale, a_price, a_flavor, an_id), cookie_type(a_type), shape(a_shape) {}

sandwich::~sandwich()
{
	cookie_type = " ";
	shape = " " ;
}

void sandwich::display() const
{
	ice_cream::display();
	cout << "Cookie Type: " << cookie_type << endl;
	cout << "Cooke Shape: " << shape << endl;
}

int sandwich::insert()
{
	ice_cream::insert();
	cout << "Input Cookie Type: ";
	getline(cin, cookie_type);
	
	cout << "Input Cookie Shape: ";
	getline(cin, shape);
	return 0;
}

float sandwich::purchase()
{
	
	return 0;
}		
float sandwich::refund()
{

	return 0;
}	
float sandwich::discount()
{

	return 0;
}		
int sandwich::eat_dessert()
{
	cout << "You ate an Ice Cream Sandwich!!!" << endl;
	return 0;
}

//******ICE CREAM CAKE CLASS*****
cake::cake(): custom_message(" "), size(" ") {}
cake::cake(float a_sale, float a_price, const string & a_flavor, int an_id, const string & a_message, const string & a_size): 
	ice_cream(a_sale, a_price, a_flavor, an_id), custom_message(a_message), size(a_size) {}
cake::~cake()
{
	custom_message = " ";
	size = " ";
}

void cake::display() const
{
	ice_cream::display();
	cout << "Custom Message: " << custom_message << endl;
	cout << "Cake Size: " << size << endl;
}
float cake::purchase()
{

	return 0;
}

int cake::insert()
{
	ice_cream::insert();
	cout << "Input Custom Cake Message: ";
	getline(cin, custom_message);

	cout << "Input Cake Size (small, medium, large): ";
	getline(cin, size);
	return 0;
}

float cake::refund()
{

	return 0;
}			
float cake::discount()
{

	return 0;
}		

int cake::blow_candles()
{
	cout << "You've Blow out all the candles!!!" << endl;
	
	return 0;
}	
int cake::eat_dessert()
{
	cout << "You ate an Ice Cream Cake!!!" << endl;
	return 0;
}

//******ICE CREAM PANCAKE CLASS******
pancake::pancake(): pancake_amount(0), topping(" ") {}

pancake::pancake(float a_sale, float a_price, const string & a_flavor, int an_id, int a_amount, const string & a_topping): 
	ice_cream(a_sale, a_price, a_flavor, an_id), pancake_amount(a_amount), topping(a_topping) {}
pancake::~pancake()
{
	pancake_amount = 0;
	topping = " ";
}

void pancake::display() const
{
	ice_cream::display();
	cout << "Pancake Amount: " << pancake_amount << endl;
	cout << "Toppings: " << topping << endl;
}
int pancake::insert()
{
	ice_cream::insert();
	cout << "Input Pancake Amount (int): ";
	cin >> pancake_amount;
	cin.ignore(100, '\n');

	cout << "Input Pancake Topping: ";
	getline(cin, topping);
	return 0;
}
float pancake::purchase()
{

	return 0;
}		
float pancake::refund()
{

	return 0;
}	
float pancake::discount()
{

	return 0;
}
int pancake::eat_dessert()
{
	cout << "You ate an Ice Cream Pancake!!!" << endl;
	return 0;
}

