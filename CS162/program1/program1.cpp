//Bradley Chang CS162 Rent Space Calculator Jan19

/*Purpose of this program is to calculate the rent cost of a shop in a mall depending on its size,
time rented, foot traffic. The program will first welcome the user and explain its purpose. It will then prompt the user of how much the
base price per square inch is. The program then asks the user the length and width of their stall. It then asks for the amount of time they want to rent, how much foot traffic they want, and if they want enclosed walls. The program then calculates the renting cost with 
deductions and surcharge included.



*/

#include <iostream>
#include <cctype>
using namespace std;

int main()
{
	//Initializing variables 
  int length {0};    //Length of the booth in feet
  int width {0};     //Width of the booth in feet
  int time {0};      //Amount of time user wants to rent in months
  int popularity {0};//Amount of foot traffic user wants
  int rent {0};      //The final rent per month that user wants to calculate
  int base_rent {0}; //The base price per square foot 
  char walls {' '};  //For the user to choose if they want enclosed walls or not
  char option {'y'}; //Menu option to prompt user if they want to do calculations again or not
  

  //Welcome message
  cout << "Welcome to the Shop Rent Space Calculator \n"
       << "This program will help calculate the rent cost of a shop based off of shop size,\n"
       << "rent time, foot traffic popularity, and the choice of having enclosed walls." << endl << endl;
       
  
       
  //Gathering input from user      
  while (option == 'y')
  {
    do	//Gathering base rent per square feet input
    {
      cout << "Please input the base price per square feet: ";
      cin >> base_rent;
      if (base_rent < 0)
      {
        cout << "Cannot have a negative base rent! Try again." << endl;
      }
    }while (base_rent < 0);
  
    
    do	//Gathering length input
    {
      cout << "Please insert the length of your booth in whole numbers (feet) : ";
      cin >> length;
      if (length < 0)
      {
        cout << "Cannot have a negative length! Try again." << endl;
      }
    }while (length < 0);
  
    cout << "Length of booth: " << length << " feet" << endl;
    
    do	//Gathering Width input
    {
      cout << "Please insert the width of your booth in whole numbers (feet) : ";
      cin >> width;
      if (width < 0)
      {
        cout << "Cannot have a negative width! Try again." << endl;
      }
    }while (width < 0);
  
    cout << "Width of booth: " << width << " feet" << endl;
    
    do	//Gathering months input
    {
      cout << "Please insert amount of months you'd like to rent (Maximum of 12): ";
      cin >> time;
      if (time < 1)
      {
        cout << "Cannot have a negative, or zero time rented! Try again." << endl;
      }
      if (time > 12)
      {
        cout << "Cannot rent for more than 12 months! Try again." << endl;
      }
    }while (time < 1 || time > 12);
  
    cout << "Time Rented: " << time << " months" << endl;
    
     do	//Gathering Foot traffic input
    {
      cout << "Please insert the percentage of foot traffic you'd like (0 to 100): ";
      cin >> popularity;
      if (popularity < 0)
      {
        cout << "Cannot have negative foot traffic! Try again." << endl;
      }
      if (popularity > 100)
      {
        cout << "Cannot have more than 100% foot traffic! Try again." << endl;
      }
    }while (popularity < 0 || popularity > 100);
    
    cout << "Foot Traffic: " << popularity << "%" << endl;
    
    // Gathering walls input
    do
    {  
      cout << "Do you want enclosed walls for your stall? (y/n): ";
      cin >> walls;
      if (walls != 'y' && walls != 'n')
      {
        cout << "Error. Please enter either a 'y' for yes or 'n' for no" << endl;
      }
    }while (walls != 'y' && walls != 'n');
    cout << "Enclosed walls: " << walls <<endl << endl;
    
    //Calculating rent before deductions and surcharges
    rent = (length * width) * base_rent; 
    cout << "Before deductions and surcharges, your rent is $" << rent << " per month" << endl;
    
    //Time discount
    if (time > 1 && time < 5)
    {
      rent = rent * 0.95;
      cout << "Since you've rented between 1 to 4 months, you get a 5% discount. New rent is $" << rent << " per month" << endl; 
    }
    if (time >= 5)
    {
      rent = rent * 0.8;
      cout << "Since you've rented between 5 and 12 months, you get a 20% discount. New rent is $" << rent << " per month" << endl; 
    }
    
    //Walls surcharge
    if (walls == 'y')
    {
      rent = rent * 1.30;
      cout << "There is a 30% surcharge for having enclosed walls. New rent is $" << rent << " per month" << endl;
    }
    if (walls == 'n')
    {
      cout << "There is no extra charge or deduction for opting out of enclosed. Current rent is $" << rent << " per month" << endl;
    }
    
    //Adjusting base price per square feet based on foot traffic
    rent =((popularity/100.00)+1.00) * rent;
    cout << "Rent increased by desired foot traffic of " << popularity << "%. New rent is now $" << rent << " per month." << endl << endl;
    cout << "Final rent is $" << rent << " per month." << endl;
    
    //Ask if user wants to calculate again
    do
    {
      cout << "Do you want to calculate again? (y/n): ";
      cin >> option;
      if(option != 'y' && option != 'n')
      {
         cout << "Error. Please enter either a 'y' for yes or 'n' for no" << endl;
      }
    }while (option != 'y' && option != 'n');
    
    if (option == 'n')
    {
      cout << "Closing program. Thank you for using the rent space calculator! :)" << endl;
    }
  }   


  return 0;
}


