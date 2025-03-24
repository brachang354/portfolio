//Bradley Chang CS350 Horspool's Algorithm implementation

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 1000

//int compare(char pattern[], char text[], char table[], char pattern_values[], int pattern_size, int text_size);

int main()
{
	//Data members
	char pattern[MAX];
	char text[MAX];
	char table[MAX];
	char pattern_values[MAX];

	int pattern_size;
	int text_size;
	
	//Getting input and outputting 
	printf("Input string for pattern: \n");
	scanf("%s", pattern);

	printf("Input string for text: \n");
	scanf("%s", text);

	printf("Inputted pattern: %s\n", pattern);
	printf("Inputted text: %s\n", text);

	//Setting text and pattern size;
	pattern_size = strlen(pattern);
	text_size = strlen(text);
	printf("Size of pattern: %d\n", pattern_size);
	printf("Size of text: %d\n", text_size);

	//Initializing table with length of pattern
	for(int i = 0; i < MAX; ++i)
	{
		table[i] = pattern_size;
	}

	//Initializing pattern values
	pattern_values[pattern_size - 1] = pattern_size;
	for(int i = 0; i < pattern_size - 1; ++i)
	{
		pattern_values[i] = pattern_size - (i + 1);
	}

	//Setting each character in table to its assigned value in pattern
	for(int i = pattern_size - 1; i >= 0; --i)
	{
		table[(int) pattern[i]] = pattern_values[i];
	}

	//Comparing the pattern to the text
	//int start_mark = pattern_size - 1;
	int found_index = -1;
	int compares = 0;
	int keep_comparing = 1;
	int j = pattern_size - 1;
	//while(start_mark < text_size && index < pattern_size){}
	

	//First loop to traverse through start mark through text
	for(int start_mark = pattern_size - 1; start_mark < text_size; start_mark += table[(int) text[start_mark]])
	{
		keep_comparing = 1;
		j = pattern_size - 1;
		//Nested loop to compare pattern to text
		for(int i = start_mark; i > start_mark - pattern_size && keep_comparing == 1; --i)
		{ 
			if(text[i] != pattern[j])
				keep_comparing = 0;
			if(i == start_mark - pattern_size + 1 && text[i] == pattern[j])
				found_index = i;
			
			++compares;
			--j;
		}
	}
	if(found_index == -1)
		printf("Pattern not found in text.\n");
	else
		printf("Pattern found at index %d\n", found_index);

	printf("Number of compares %d\n", compares);

	return 0;
}

/*int compare(char pattern[], char text[], char table[], char pattern_values[], int pattern_size, int text_size)
{
	int start_mark = pattern_size - 1;
	




}*/
