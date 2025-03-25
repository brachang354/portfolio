//Bradley Chang CS333 Lab5 thread crypt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <pthread.h>
#include <crypt.h>
#include <fcntl.h>
#include <string.h>
#include "thread_hash.h"

#ifndef DEFAULT_NUM_THREADS
# define DEFAULT_NUM_THREADS 1
#endif

#ifndef MAX_NUM_THREADS
# define MAX_NUM_THREADS 24
#endif

#define BUF_SIZE 1000


//Function prototypes
char ** read_file(char * input_file, int * num_words); 	//Function to store the input values into an array
char ** parse_input(char * buf, int num_words);		//Function to read and parse through the input file.
void * crack_password(void * vid); //Function to crack passwords
void free_text(char ** array, int num_words);
double elapse_time(struct timeval *, struct timeval *);
int get_next_row(void);

//Global variables (SCARY!)
//int word_count = 0;
char ** dict_array = NULL;
char ** hash_array = NULL;
static int num_threads = DEFAULT_NUM_THREADS;
static int dict_words = 0;
static int hash_words = 0;
static long thread_process = 0;
char * out_file = NULL;
static int total_hash_count = 0;
static int total_hash_fails = 0;
int total_algorithm_count[8];
FILE * fp = NULL;
//struct hash_counter hash_c_g;

int
main(int argc, __attribute__((unused)) char *argv[])
{
	int opt = 0;
	char * hash_file = NULL;
	char * dict_file = NULL;
	//char * out_file = NULL;
	//int threads = 1;
	int nice_num = 0;
	//int flag = 0;
	pthread_t *threads = NULL;
	long tid = 0;
	//FILE *fp = NULL;

	struct timeval et0;
	struct timeval et1;
	double thread_time = 0;

	memset(total_algorithm_count, 0, sizeof(total_algorithm_count));

	while((opt = getopt(argc, argv, OPTIONS)) != -1)
	{
		switch(opt)
		{
			case 'i':
				//flag = 1;
				hash_file = optarg;
				break;
			case 'o':
				//flag = 2;
				out_file = optarg;
				break;
			case 'd':
				//flag = 3;
				dict_file = optarg;
				break;
			case 't':
				//flag = 4;
				num_threads = atoi(optarg);
				if(num_threads < DEFAULT_NUM_THREADS)
				{
					fprintf(stderr, "Invalid number of threads\n");
					exit(EXIT_FAILURE);
				}
				if(num_threads > MAX_NUM_THREADS)
				{
					fprintf(stderr, "Invalid number of threads\n");
					exit(EXIT_FAILURE);
				}
				break;
			case 'v':
				//flag = 5;
				printf("Verbose mode is enabled\n");
				break;
			case 'h':
				//flag = 6;
			       printf("\nhelp text "
				      "\n\t%s ..."
				      "\n\tOptions: %s"
				      "\n\t\t-i file\t\thash file name (required)"
				      "\n\t\t-o file\t\toutput file name (default stdout)"
				      "\n\t\t-d file\t\tdictionary file name (default stdout)"
				      "\n\t\t-t #\t\tnumber of threads to create (default 1)"
				      "\n\t\t-v\t\tenable verbose mode"
				      "\n\t\t-h\t\thelpful text\n", argv[0], OPTIONS
				     );
				break;
			case 'n':
				//flag = 7;
				nice_num = NICE_VALUE;
				break;
			default:
				fprintf(stderr, "Failure to parse command line\n");
				exit(EXIT_FAILURE);
				break;

		}
	}

	//Handling command line arguments after parsing
	if(hash_file != NULL)
	{
		hash_array = read_file(hash_file, &hash_words);
		//fprintf(stderr, "Word count: %d\n", hash_words);
	}
	if(dict_file != NULL)
	{
		dict_array = read_file(dict_file, &dict_words);
		//fprintf(stderr, "Word count: %d\n", dict_words);
		/*for(int i = 0; i < dict_words; ++i)
		{
			fprintf(stderr, "%s\n", dict_array[i]);
		}*/
	}
	if(out_file != NULL)
	{
		fp = fopen(out_file, "w");
		//fclose(fp);
	}
	else {
		fp = stdout;
	}
	if(nice_num != 0)
	{
		if(nice(NICE_VALUE) == -1)
		{
			fprintf(stderr, "Failed to set nice value\n");
		}
	}
	//Time to start decrypting
	if(hash_array != NULL && dict_array != NULL)
	{
		threads = malloc(num_threads * sizeof(pthread_t));
		//crack_password(dict_words, hash_words);
		
		gettimeofday(&et0, NULL);
		for(tid = 0; tid < num_threads; ++tid)
		{
			pthread_create(&threads[tid], NULL, crack_password, (void *) tid);
		}
		for(tid = 0; tid < num_threads; ++tid)
		{
			pthread_join(threads[tid], NULL);
			//thread_time = elapse_time(&et0, &et1);
		}
		gettimeofday(&et1, NULL);
		thread_time = elapse_time(&et0, &et1);

		fprintf(stderr, "total: %3d %8.2lf sec", num_threads, thread_time);
		for (hash_algorithm_t k = DES; k < ALGORITHM_MAX; ++k)
		{
			fprintf(stderr, "%17s: %5d", algorithm_string[k], total_algorithm_count[k]);
		}	
		fprintf(stderr, "  total: %8d  failed: %8d\n", total_hash_count, total_hash_fails);

	}
	
	//Freeing memory once we're done.
	if(hash_array != NULL)
	{
		free_text(hash_array, hash_words);
	}
	if(dict_array != NULL)
	{
		free_text(dict_array, dict_words);
	}
	if(threads != NULL)
	{
		free(threads);
	}
	if(out_file != NULL)
	{
		fclose(fp);
	}
	return EXIT_SUCCESS;
	
}

void * crack_password(void * vid)
{
	//char buf[BUF_SIZE] = {'\0'};
	char *plain_text = NULL;
	char *setting = NULL;
	char *crypt_return = NULL;
	struct crypt_data crypt_stuff;
	int j = -1;
	int i = -1;
	int cracked;
	int hash_count = 0;
	int fails = 0;
	//FILE * fp = stdout;
	//struct hash_counter hash_c;
	char *hash_pre = NULL;
        
	//static pthread_mutex_t out_lock = PTHREAD_MUTEX_INITIALIZER;

	struct timeval et0;
	struct timeval et1;
	double thread_time = 0;
	
	int algorithm_count[8];
	memset(algorithm_count, 0, sizeof(algorithm_count));

	//if(out_file != NULL)
	//{
	//	fp = fopen(out_file, "a");
	//}

	gettimeofday(&et0, NULL);
	//First for loop to traverse hash array
	for(j = get_next_row(); j < hash_words; j = get_next_row())
	{
		cracked = 0;
		setting = hash_array[j];
		//Second loop to traverse dict array
		for(i = 0; i < dict_words; ++i)
		{

			plain_text = dict_array[i];

			memset(&crypt_stuff, 0, sizeof(crypt_stuff));
			strncpy(crypt_stuff.setting, setting, CRYPT_OUTPUT_SIZE);
			strncpy(crypt_stuff.input, plain_text, CRYPT_MAX_PASSPHRASE_SIZE);
			crypt_return = crypt_rn(plain_text, setting, &crypt_stuff, sizeof(crypt_stuff));
			
			//Checking when a password is cracked
			if (strcmp(crypt_stuff.setting, crypt_return) == 0) 
			{
			    //pthread_mutex_lock(&out_lock);
			    //fprintf(fp, "cracked  %s  %s\n", plain_text, crypt_stuff.output);
			    fprintf(fp, "cracked  %s  %s\n", dict_array[i], hash_array[j]);
			    //printf("\t%s\t%s\n", crypt_stuff.setting, crypt_stuff.output);
			    cracked = 1;
			    //++successes;
			    //pthread_mutex_unlock(&out_lock);
			    break;
			}
		}
		++hash_count;
		++total_hash_count;
		
		//Checking when a password fails
		if(cracked != 1)
		{
		    //pthread_mutex_lock(&out_lock);
		    //printf("*** failed to crack %s\t%s\n", plain_text, crypt_stuff.output);
		    //printf("\t%s\t%s\n", crypt_stuff.setting, crypt_stuff.output);
		    //fprintf(fp, "*** failed to crack  %s\n", crypt_stuff.output);
		    //fprintf(fp, "*** failed to crack  %s\n", crypt_stuff.setting);
		    fprintf(fp, "*** failed to crack  %s\n", hash_array[j]);
		    ++fails;
		    ++total_hash_fails;
		    //pthread_mutex_unlock(&out_lock);
		}

		//Counting all hash algorithms
		hash_pre = strtok(crypt_stuff.setting, "$");
		//fprintf(stderr, "\n%s\n\n", hash_pre);
		if(strcmp(hash_pre, "1") == 0)		//MD5
		{
			++algorithm_count[2];
			++total_algorithm_count[2];
		}
		else if(strcmp(hash_pre, "3") == 0)	//NT
		{
			++algorithm_count[1];
			++total_algorithm_count[1];
		}
		else if(strcmp(hash_pre, "5") == 0)	//SHA256
		{
			++algorithm_count[3];
			++total_algorithm_count[3];
		}
		else if(strcmp(hash_pre, "6") == 0)	//SHA512
		{
			++algorithm_count[4];
			++total_algorithm_count[4];
		}
		else if(strcmp(hash_pre, "y") == 0)	//Yes
		{
			++algorithm_count[5];
			++total_algorithm_count[5];
		}
		else if(strcmp(hash_pre, "gy") == 0)	//Gost
		{
			++algorithm_count[6];
			++total_algorithm_count[6];
		}
		else if(strcmp(hash_pre, "2b") == 0)	//Bcrypt
		{
			++algorithm_count[7];
			++total_algorithm_count[7];
		}
		else					//DES
		{
			++algorithm_count[0];
			++total_algorithm_count[0];
		}
	}

	gettimeofday(&et1, NULL);
	thread_time = elapse_time(&et0, &et1);
	
	//Output thread info
	//fprintf(stderr, "thread\t%d: %8.2lf sec\t", thread_process,  thread_time);
	fprintf(stderr, "thread: %2ld %8.2lf sec", thread_process, thread_time);
	for (hash_algorithm_t k = DES; k < ALGORITHM_MAX; ++k)
	{
		fprintf(stderr, "%17s: %5d", algorithm_string[k], algorithm_count[k]);
	}	
	//fprintf(stderr, "\ttotal: %d\tfailed: %d\n", hash_count, fails);
	fprintf(stderr, "  total: %8d  failed: %8d\n", hash_count, fails);	
	++thread_process;
	//if(out_file != NULL)
	//	fclose(fp);
	pthread_exit(EXIT_SUCCESS);
}

char ** read_file(char * input_file, int * num_words) 	//Function to store the input values into an array
{
	int input_fd;
	char ** text;
	char * buf;
	struct stat md;
	//int word_count = 0;
	
	//Open input file to start reading
	if(input_file != NULL)
	{
		input_fd = open(input_file, O_RDONLY);
		if(input_fd < 0)
		{
			fprintf(stderr, "Could not open file for input.\n");
			exit(EXIT_FAILURE);
		}
	}
	
	//Get the file stats of the file.
	if(fstat(input_fd, &md) < 0)
	{
		fprintf(stderr, "Failed to get file stats for %s\n", input_file);
		close(input_fd);
		exit(EXIT_FAILURE);
	}
	
	//Dynamically allocate the buffer based on the size of file
	buf = (char *) calloc (md.st_size + 1, sizeof(char));
	//Read in the file into the buffer
	read(input_fd, buf, md.st_size);
	//Count the number of words in the buf
	for(int i = 0; buf[i] != '\0'; ++i)
	{
		if(buf[i] == '\n')
			++(*num_words);
	}
	
	//Pass in the buf, and num words into parse_input
	text = parse_input(buf, *num_words);

	free(buf);

	close(input_fd);

	return text;

}
char ** parse_input(char * buf, int num_words)		//Function to read and parse through the input file.
{
	char ** text;
	char * token;
	
	//Creating dynamic array of strings
	text = (char **) calloc (num_words, sizeof(char*));
	//memset(text, NULL, text*sizeof(text[0]));
	
	//Creating a dynamic array of chars to hold \n delimted words in buf
	//and creating storing the first word into text ragged array
	token = strtok(buf, "\n");
	//text[0] = (char *) calloc ((sizeof(token)/sizeof(token[0])) + 1, sizeof(char));
	text[0] = strdup(token);

	//Loop through all of buf to store all words into text
	for(int i = 1; i < num_words /*buf[i] != '\0'*/; ++i)
	{
		//text[i] = (char *) calloc((sizeof(token)/sizeof(token[0])) + 1, sizeof(char));
		token = strtok(NULL, "\n");
		text[i] = strdup(token);
	}
	
	return text;

}
void free_text(char ** array, int num_words)
{	
	for(int i = 0; i < num_words; ++i)
	{
		free(array[i]);
	}
	free(array);
}
double elapse_time(struct timeval *t0, struct timeval *t1)
{
        double et = (((double) (t1->tv_usec - t0->tv_usec))
                        / MICROSECONDS_PER_SECOND)
                +((double) (t1->tv_sec - t0->tv_sec));
        return et;
}
int get_next_row(void)
{
        static int next_row = 0;
        static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
        int cur_row = 0;

        pthread_mutex_lock(&lock);
        cur_row = next_row++;
        pthread_mutex_unlock(&lock);

        return cur_row;
}

