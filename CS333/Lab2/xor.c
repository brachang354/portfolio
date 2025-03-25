//Bradley Chang Xor Cipher CS333
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include <fcntl.h>

#define MAX_TEXT 10000

int main(int argc, char *argv[])
{
	char key[MAX_TEXT] = "Xerographic";
	
	char text[MAX_TEXT];
	char output[MAX_TEXT];
	ssize_t num_bytes;
	int key_length;
	//char * default_key = "Xerographic";
	
	//Starting with command line parsing
	int opt = 0;
	while((opt = getopt(argc, argv, "k:")) != -1)
	{
		switch(opt)
		{
		case 'k':
			//Copy the key from the command line into key
			strcpy(key, optarg);
			break;
		
		default:
			fprintf(stderr, "Usage: ./xor [-k key] (TEXT)");
			exit(EXIT_FAILURE);
			break;
		}
	}
	
	//Time to do the encryption/decryption
	key_length = strlen(key);
	

	while((num_bytes = read(STDIN_FILENO, text, MAX_TEXT)) > 0) 
	{ 
		for(int i = 0; i < num_bytes; ++i)
		{
			output[i] = text[i] ^ key[i % key_length];
		}

		if(write(STDOUT_FILENO, output, num_bytes) != num_bytes)
		{
			perror("Write Failure");
			exit(EXIT_FAILURE);
		}
	}
	if(num_bytes < 0)
	{
		perror("Read Failure");
		exit(EXIT_FAILURE); 
	}

	return 0;
}
