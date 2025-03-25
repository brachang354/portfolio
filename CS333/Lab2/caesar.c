//Bradley Chang Caesar Cipher CS333

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 

#include <ctype.h>

#define MAX_SHIFT 95 
#define MIN_SHIFT 0
#define MAX_TEXT 10000

int main(int argc, char *argv[])
{
	char text[MAX_TEXT];
	long int shift = 3;	//Shift value
	int encode = 1;		//Encrypt == 1, Decrypt == 0
	//int bytes_read;

	//Setting up ascii tables
	char ascii[MAX_TEXT];
	char encrypt_ascii[MAX_TEXT];
	
	//initializing printable sections of ascii tables
	for(int i = ' '; i <= '~'; ++i)
	{
		ascii[i] = i;
		encrypt_ascii[i] = i;
	}

	//Starting with getopt command line reading
	{
		int opt = 0;
		while ((opt = getopt(argc, argv, "s:ed")) != -1)
		{
			switch (opt)
			{
			// -s The shifter. Indicates how many characters to shift by from 0 to 95
			case 's':
				char *endptr;
				shift = strtol(optarg, &endptr, 10);
				if(endptr == optarg)
				{
					fprintf(stderr, "No digits found\n");
					exit(EXIT_FAILURE);
				}
				else if(*endptr != '\0')
				{
					fprintf(stderr, "Invalid character. Must be an integer from 0 to 95\n");
					exit(EXIT_FAILURE);
				}
				else if(shift < 0 || shift > 95)
				{
					fprintf(stderr, "Shift number must be between 0 and 95\n");
					exit(EXIT_FAILURE);
				}
				else
				{
					//printf("Shift amount is %ld\n", shift);
				}
				break;
			// -e Argument to encrypt text by the shifter amount indicated with -s
			case 'e':
				encode = 1;
				break;
			// -d Argument to decrypt text by the shifter amount indicated with -s
			case 'd':
				encode = 0;
				break;
			// Default case for any erronous actions
			default:
				fprintf(stderr, "Usage ./caesar [-s shift] [-e] [-d]\n");
				exit(EXIT_FAILURE);
				break;
			}
		}
	}

	// process input
	//
	//Time to encrypt
	if(encode == 1)
	{
		read(STDIN_FILENO, text, MAX_TEXT);
		//Time to shift the encrypt_ascii table
		for(int i = ' '; i <= '~'; ++i)
		{
			int shifted_value = (int) shift + ascii[i];
			if(shifted_value > 126)
				shifted_value -= 95;
			encrypt_ascii[i] = shifted_value;
			fprintf(stderr, "%d: %d  %c  %c\n", __LINE__, i, ascii[i], encrypt_ascii[i]);
		}
		
		//Time to shift the text using the encrypt_ascii table.
		for(int i = 0; i < MAX_TEXT; ++i)
		{
		  if (isprint(text[i])) {
		    text[i] = encrypt_ascii[(int) text[i]];
		  }
		  else {
		    //text[i] = encrypt_ascii[i];
		  }
		}
	
		write(STDOUT_FILENO, text, strlen(text));
		//printf("\n");
	}
	
	//Time to decrypt
	if(encode == 0)
	{
		read(STDIN_FILENO, text, MAX_TEXT);
		//Time to shift encrypt_ascii table in the reverse
		for(int i = ' '; i <= '~'; ++i)
		{
			int shifted_value = ascii[i] - (int) shift;
			if(shifted_value < 32)
				shifted_value += 95;
			encrypt_ascii[i] = shifted_value;
			fprintf(stderr, "%d: %d  %c  %c\n", __LINE__, i, ascii[i], encrypt_ascii[i]);
		}
		for(int i = 0; i < MAX_TEXT; ++i)
		{
		  if (isprint(text[i])) {
			text[i] = encrypt_ascii[(int) text[i]];
		  }
		  else {
		    //text[i] = encrypt_ascii[i];
		  }
		}
		
		write(STDOUT_FILENO, text, strlen(text));
		//printf("\n");
	}

	return 0;
}
