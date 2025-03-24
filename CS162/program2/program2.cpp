//Program 2 Paragraph Shortener
//Bradley Chang CS 162

#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

//Max size of paragraph array
const int SIZE {250};

//Prototype, function declaration
void wordCount(char paragraph[], char letter, int & space_count);
void findReplace(char paragraph[], char word[], char newPara[], char replacement[]);


//*************************

int main()
{
  //Variables
  char paragraph[SIZE];  //Array for paragraph that user inputs
  char newPara[SIZE];    //Array for the new paragraph
  int max_word_count {0};  //User inputted max_word_count
  int space_count {0};   //Counter for spaces in paragraph.
  char letter {' '};    //For the word counter function. "letter" is set to spaces which the word counter counts.

  
  
  //Welcome message
  cout << "Welcome to the Paragraph Shortener! \n"
       << "The purpose of this program is to shorten paragraphs by removing unneccessary words \n"
       << "such as 'and' 'the' 'a' and 'or' \n"
       << "To get started, start by typing in your paragraph and then your max word count." << endl << endl;
  

  //Paragraph input
  cout << "Type paragraph: ";
  cin.get(paragraph, SIZE, '\n');
  cin.ignore(100, '\n');
  cout << "Your paragraph is: " << paragraph << endl;
  
  //Max word count input
  do
  {
    cout << "Enter Max Word Count: ";
    cin >> max_word_count;
    if(max_word_count < 0)
    {
      cerr << "Error. Can't have a negative word count. Try again." << endl;
    }
    
  }while(max_word_count < 0);
  cout << "Max word count is: " << max_word_count << endl;
  
  //Word counter
  
  wordCount(paragraph, letter, space_count);

  //Find words and replace them in the new paragraph
  char dash[5] = "\b \b-";  //To replace a word with a dash
  char space[5] = "\b \b ";  //To replace a word with spaces
  char onespace[2] = "\b"; //To replace a letter with one space
  
      //Replacing any instance of "the"
  char word1[6] = " the ";
  findReplace(paragraph, word1, newPara, space);
  char word2[6] = " The ";
  findReplace(paragraph, word2, newPara, space);
  
      //Replacing any instance of "and"
  char word3[6] = " and ";
  findReplace(paragraph, word3, newPara, dash);
  char word4[6] = " and,";
  findReplace(paragraph, word4, newPara, dash);
  char word5[6] = " And ";
  findReplace(paragraph, word5, newPara, space);
  char word6[6] = " And,";
  findReplace(paragraph, word6, newPara, space);
  
      //Replacing any instance of "a"
  char word7[4] = " a ";
  findReplace(paragraph, word7, newPara, onespace);
  char word8[4] = " A ";
  findReplace(paragraph, word8, newPara, onespace);
  
  cout << "New paragraph is: " << newPara << endl;




	return 0;
}



//Functions go here
//Word counter function
void wordCount(char paragraph[], char letter, int & space_count)
{
  for(int i {0}; i < SIZE; ++i)
  {
    if (paragraph[i] == letter)
    {
      space_count += 1;
    }
  }
  space_count += 1;
  cout << "Word count for paragraph is: " << space_count << endl;
  
}

//Find and replace function

void findReplace(char paragraph[], char word[], char newPara[], char replacement[])
{
  int i {0};
  int n {0};
  
  int wordSize {0};
  wordSize = strlen(word);
  
  while (i < SIZE)
  {
    if (paragraph[i] == word[0] && paragraph[i+1] == word[1] && paragraph[i+2] == word[2] && paragraph[i+3] == word[3] && paragraph[i+4] == word[4])
    {
      paragraph[i+1] = replacement[0];
      paragraph[i+2] = replacement[1];
      paragraph[i+3] = replacement[2];
      paragraph[i+4] = replacement[3];
    }

    else if (paragraph[i] == word[0] && paragraph[i+1] == word[1] && paragraph[i+2] == word[2] && wordSize != 5)
    {
      paragraph[i+1] = replacement[0];
    }
    
    else
    {
      newPara[n] = paragraph[i];
    }
    
    ++i;
    ++n;
  }
  
  
}




