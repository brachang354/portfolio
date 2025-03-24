//Bradley Chang CS 302 Program #3
//This ice_cream.h file will contain the core hierachy for the ice cream application.
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cstring>
using namespace std;

class ice_cream
{
	public:
		//Constructor, constructor with args, and destructor
		ice_cream();
		ice_cream(float a_sale, float a_price, const string & a_flavor, int an_id);
		virtual ~ice_cream();
		
		virtual void display() const;		//Displays info about the dessert.
		virtual int insert();			//Allows user to input information about a dessert.
		virtual float purchase();		//Allows a customer to purchase a dessert and increment total sales by the price
		virtual float refund();			//Allows a customer to refund a purchase, decrementing total_sales by the price.
		virtual float discount();		//Gives a discount on a purchase for promotions or coupons. Modifies the price.
		virtual int eat_dessert() = 0;		//Allows a customer to eat their dessert

		friend bool operator<(const ice_cream & op1, const ice_cream & op2);
		friend bool operator>(const ice_cream & op1, const ice_cream & op2);
		friend bool operator<=(const ice_cream & op1, const ice_cream & op2);
		friend bool operator>=(const ice_cream & op1, const ice_cream & op2);
	
	protected:
		float total_sales;			//Total amount of sales for a dessert
		float price;				//Given price for a dessert
		string flavor;				//Ice cream flavor for a dessert
		int item_id;				//ID number for ice cream product
};

class sandwich: public ice_cream
{
	public:	
		sandwich();
		sandwich(float a_sale, float a_price, const string & a_flavor, int an_id, const string & a_type, const string & a_shape);
		~sandwich();
		
		//Virtual functions
		void display() const;
		int insert();
		float purchase();		//Allows a customer to purchase a dessert and increment total sales by the price
		float refund();			//Allows a customer to refund a purchase, decrementing total_sales by the price.
		float discount();		//Gives a discount on a purchase for promotions or coupons. Modifies the price.
		int eat_dessert();
	protected:
		string cookie_type;		//Type of cookie a sandwich can have.
		string shape;			//Shape of the cookie, can be classic rectangle, square or circular.
};

class cake: public ice_cream
{
	public:
		cake();
		cake(float a_sale, float a_price, const string & a_flavor, int an_id, const string & a_message, const string & a_size);
		~cake();
		
		//Virtual functions
		void display() const;
		int insert();
		float purchase();		//Allows a customer to purchase a dessert and increment total sales by the price
		float refund();			//Allows a customer to refund a purchase, decrementing total_sales by the price.
		float discount();		//Gives a discount on a purchase for promotions or coupons. Modifies the price.
		int eat_dessert();
		
		int blow_candles();		//Allows a customer to blow out candles on a cake. Requires RTTI.
	
	protected:
		string custom_message;		//Custom message for customer to write on a cake
		string size;			//Size of the cake. Small, medium or large.
};

class pancake: public ice_cream
{
	public:
		pancake();
		pancake(float a_sale, float a_price, const string & a_flavor, int an_id, int a_amount, const string & a_topping);
		~pancake();

		//Virtual
		void display() const;
		int insert();
		float purchase();		//Allows a customer to purchase a dessert and increment total sales by the price
		float refund();			//Allows a customer to refund a purchase, decrementing total_sales by the price.
		float discount();		//Gives a discount on a purchase for promotions or coupons. Modifies the price.
		int eat_dessert();
	
	protected:
		int pancake_amount;		//Amount of pancakes for a single purchase.
		string topping;			//Topping that customer can pick to have.
};
