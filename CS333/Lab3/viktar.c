//Bradley Chang CS333 Lab3 Viktar

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <md5.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <getopt.h>
#include <stdint.h>
#include <errno.h>

#include "viktar.h"

#define BUFFER_SIZE 10

void small_toc(char * filename);
void long_toc(char * filename);
void create_archive(char * filename, int argc, char *argv[]);
void extract_archive(const char * archive_name, char * argv[], int argc);
void extract_files(int iarch, viktar_header_t * head);
void validate(char * filename);

int main(int argc, char *argv[])
{
	viktar_action_t flag = ACTION_NONE;
	//viktar_header_t viktar_header;
	char *filename = NULL;
	/*char **files = NULL;
	int fsi = -1;
	int fcount = 0;
	*/
	int verbose_mode = 0;
	{
		int opt = 0;

		while((opt = getopt(argc, argv, OPTIONS)) != -1)
		{
			switch(opt)
			{
				case 'x':	//Extract files
					flag = ACTION_EXTRACT;
					break;
				case 'c':	//Create files
					flag = ACTION_CREATE;
					break;
				case 't':	//Small table of contents
					flag = ACTION_TOC_SHORT; 
					break;
				case 'T':	//Long table of contents
					flag = ACTION_TOC_LONG;
					break;
				case 'f':	//Specify name of viktar file
					filename = optarg;
					//strncpy(filename, optarg, VIKTAR_MAX_FILE_NAME_LEN);
					break;
				case 'V':	//Validate content of archive
					flag = ACTION_VALIDATE;
					break;
				case 'h':	//Help text
					fprintf(stderr, "help text"
						"\n\t./viktar"
						"\n\tOptions: xctTf:Vhv\n"
						"\t\t-x\t\textract file/files from archive\n"
						"\t\t-c\t\tcreate an archive file\n"
						"\t\t-t\t\tdisplay a short table of contents of the archive file\n"
						"\t\t-T\t\tdisplay a long table of contents of the archive file\n"
						"\t\tOnly one of xctTV can be specified\n"
						"\t\t-f filename\tuse filename as the archive file\n"
						"\t\t-V\t\tvalidate the MD5 values in the viktar file\n"
						"\t\t-v\t\tgive verbose diagnostic messages\n"
						"\t\t-h\t\tdisplay this AMAZING help message\n");
					return EXIT_SUCCESS;
					break;
				case 'v':	//Verbose mode
					//fprintf(stderr, "verbose level: 1\n");
					verbose_mode = 1;
					break;
				default:	//Default action
					fprintf(stderr, "no action supplied\nexiting without doing ANYTHING...\n");
					exit(EXIT_FAILURE);
					break;
			}
		}
	}
	
	if(verbose_mode == 1)
		fprintf(stderr, "verbose level: 1\n");
	//Small toc function call
	if (flag == ACTION_TOC_SHORT)
	{
		small_toc(filename);
	}
	//Long toc function call
	else if(flag == ACTION_TOC_LONG)
	{
		long_toc(filename);
	}
	//Create function call
	else if(flag == ACTION_CREATE)
	{
		create_archive(filename, argc, argv);
	}
	else if(flag == ACTION_VALIDATE)
	{
		validate(filename);
	}




	return EXIT_SUCCESS;
}

void small_toc(char * filename)
{
	int iarch = STDIN_FILENO;
	char buf[100] = {'\0'};
	viktar_header_t md;
	
	if(filename != NULL)
	{
		iarch = open(filename, O_RDONLY);
	}

	//validate tag
	read(iarch, buf, strlen(VIKTAR_TAG));
	if(strncmp(buf, VIKTAR_TAG, strlen(VIKTAR_TAG)) != 0)
	{
		//not a valid viktar file
		//print snarky message and exit(1)
		//fprintf(stderr, "snarky message\n");	
		if(filename != NULL)
		{
			fprintf(stderr, "reading archive file: \"%s\"\n", filename);
			fprintf(stderr, "not a viktar file: \"%s\"\n", filename);
		}
		else
		{
			fprintf(stderr, "reading archive from stdin\n");
			fprintf(stderr, "not a viktar file: \"stdin\"\n");
		}

		exit(EXIT_FAILURE);
	}
	
	//printf("reading archive from  \"%s\"\n", filename != NULL ? filename : "stdin");
	
	//process the archive file metadata
	printf("Contents of viktar file: \"%s\"\n"
		, filename != NULL ? filename : "stdin");
	while (read(iarch, &md, sizeof(viktar_header_t)) > 0)
	{
		//print archive member name
		memset(buf, 0, 100);
		strncpy(buf, md.viktar_name
			, VIKTAR_MAX_FILE_NAME_LEN);
		printf("\tfile name: %s\n", buf);
		lseek(iarch, md.st_size + sizeof(viktar_footer_t)
			, SEEK_CUR);
	}
	// we finished processing all the archive
	// members in the archive file.
	// the call to read() returned 0, indicating that
	// we hit end-of-file
	if (filename != NULL ) 
	{
		close(iarch);
	}

	return;
}

void long_toc(char * filename)
{
	int iarch = STDIN_FILENO;
	char buf[100] = {'\0'};
	viktar_header_t md;
	viktar_footer_t footer;
	struct passwd *pws;
	struct group *grp;
	struct tm *timeinfo;
	char time_buf[100] = {'\0'};
	

	if(filename != NULL)
	{
		iarch = open(filename, O_RDONLY);
	}

	//validate tag
	read(iarch, buf, strlen(VIKTAR_TAG));
	if(strncmp(buf, VIKTAR_TAG, strlen(VIKTAR_TAG)) != 0)
	{
		//not a valid viktar file
		//print snarky message and exit(1)
		//fprintf(stderr, "snarky message\n");
		if(filename != NULL)
		{
			fprintf(stderr, "reading archive file: \"%s\"\n", filename);
			fprintf(stderr, "not a viktar file: \"%s\"\n", filename);
		}
		else
		{
			fprintf(stderr, "reading archive from stdin\n");
			fprintf(stderr, "not a viktar file: \"stdin\"\n");
		}
		exit(EXIT_FAILURE);
	}
	
	//printf("reading archive from  \"%s\"\n", filename != NULL ? filename : "stdin");

	//process the archive file metadata
	printf("Contents of viktar file: \"%s\"\n"
		, filename != NULL ? filename : "stdin");
	while (read(iarch, &md, sizeof(viktar_header_t)) > 0)
	{
		//print archive member name
		memset(buf, 0, sizeof(buf));
		strncpy(buf, md.viktar_name
			, VIKTAR_MAX_FILE_NAME_LEN);
		printf("\tfile name: %s\n", buf);

		//Print mode
		printf("\t\tmode:\t\t");
		printf((S_ISDIR(md.st_mode)) ? "d" : "-");
		//Owner permissions
	        printf((md.st_mode & S_IRUSR) ? "r" : "-");
	        printf((md.st_mode & S_IWUSR) ? "w" : "-");
	        printf((md.st_mode & S_IXUSR) ? "x" : "-");
	        //Group permissions
	        printf((md.st_mode & S_IRGRP) ? "r" : "-");
	        printf((md.st_mode & S_IWGRP) ? "w" : "-");
	        printf((md.st_mode & S_IXGRP) ? "x" : "-");
	        //Other permissions
	        printf((md.st_mode & S_IROTH) ? "r" : "-");
	        printf((md.st_mode & S_IWOTH) ? "w" : "-");
	        printf((md.st_mode & S_IXOTH) ? "x\n" : "-\n");
		
		//Print user id
		printf("\t\tuser:\t\t");
		pws = getpwuid(md.st_uid);
		printf("%s\n", pws->pw_name);
		
		//Print group id
		printf("\t\tgroup:\t\t");
		grp = getgrgid(md.st_gid);
		printf("%s\n", grp->gr_name);
	
		//Print size
		printf("\t\tsize:\t\t%ld\n", md.st_size);
		
		//Print mtime
		timeinfo = localtime(&md.st_mtime);
		strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S %Z", timeinfo);
		printf("\t\tmtime:\t\t%s\n", time_buf);
		
		//Print atime
		timeinfo = localtime(&md.st_atime);
		strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S %Z", timeinfo);
		printf("\t\tatime:\t\t%s\n", time_buf);
	
		//Print md5 header	
		//Skips the metadata section.
		lseek(iarch, md.st_size, SEEK_CUR);
		read(iarch, &footer, sizeof(viktar_footer_t));

		printf("\t\tmd5 sum header:\t");
		for(int j = 0; j < MD5_DIGEST_LENGTH; ++j)
			printf("%02x", footer.md5sum_header[j]);
		
		printf("\n\t\tmd5 sum data:\t");
		for(int j = 0; j < MD5_DIGEST_LENGTH; ++j)
			printf("%02x", footer.md5sum_data[j]);
		printf("\n");

	//	lseek(iarch, /*md.st_size +*/ sizeof(viktar_footer_t), SEEK_CUR);
	}
	// we finished processing all the archive
	// members in the archive file.
	// the call to read() returned 0, indicating that
	// we hit end-of-file
	if (filename != NULL ) 
	{
		close(iarch);
	}

	return;

}

void create_archive(char * filename, int argc, char * argv[])
{
	int out_fd = STDOUT_FILENO;
	struct stat file_stat;
	viktar_header_t header;
	viktar_footer_t footer;
	int file_fd = 0;

	//md5 Variables
	//int ifd = 0;
	unsigned char head_buffer[sizeof(viktar_header_t)] = {'\0'};
	unsigned char data_buffer[sizeof(viktar_footer_t)] = {'\0'};
	ssize_t bytes_read = 0;
	MD5_CTX context;
	//uint8_t digest[MD5_DIGEST_LENGTH];


	if(filename != NULL)
	{
	  out_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if(out_fd < 0)
		{
			fprintf(stderr, "Could not open archive file for writing: %s\n", filename);
			exit(EXIT_FAILURE);
		}
	}
	
	fchmod(out_fd, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	
	if(write(out_fd, VIKTAR_TAG, strlen(VIKTAR_TAG)) < 0)
	{
		fprintf(stderr, "Failed to write VIKTAR_TAG to archive\n");
		close(out_fd);
		exit(EXIT_FAILURE);
	}

	for(int i = optind; i < argc; ++i)
	{
		//Error check when file cant open
		file_fd = open(argv[i], O_RDONLY);
		if(file_fd < 0)
		{
			fprintf(stderr, "Could not open input file: %s\n", argv[i]);
			close(file_fd);
			exit(EXIT_FAILURE); 
		}

		//Error check when file's stats aren't obtainable
		if(fstat(file_fd, &file_stat) < 0)
		{
			fprintf(stderr, "Failed to get files stats for: %s \n", argv[i]);
			close(file_fd);
			exit(EXIT_FAILURE);
		}

		//Copy all into appropriate VIKTAR file struct members
		strncpy(header.viktar_name, argv[i], VIKTAR_MAX_FILE_NAME_LEN);
		header.st_size = file_stat.st_size;
		header.st_mode = file_stat.st_mode;
		header.st_uid = file_stat.st_uid;
		header.st_gid = file_stat.st_gid;
		header.st_atim = file_stat.st_atim;
		header.st_mtim = file_stat.st_mtim;

		//Error handling for when a file header fails to write
		if(write(out_fd, &header, sizeof(viktar_header_t)) < 0)
		{
			fprintf(stderr, "Failed to write file header for: %s\n", argv[i]);
			close(file_fd);
			exit(EXIT_FAILURE);
		}
		memcpy(head_buffer, &header, sizeof(viktar_header_t));

		//MD5 Calculations
		MD5Init(&context);
		MD5Update(&context, head_buffer, sizeof(viktar_header_t));
		MD5Final(footer.md5sum_header, &context);
		
		MD5Init(&context);

		while ((bytes_read = read(file_fd, data_buffer, sizeof(viktar_footer_t))) > 0)
		{
			//Writing data into archive
			if(write(out_fd, data_buffer, bytes_read) != bytes_read)
			{
				fprintf(stderr, "Failed to write file data to archive for %s\n", argv[i]);
				perror("Error. Failed to write file data into archive.\n");
				exit(EXIT_FAILURE);
			}
			MD5Update(&context, data_buffer, bytes_read);
		}
		
		MD5Final(footer.md5sum_data, &context);

		//Handle errors after loop
		if(bytes_read < 0)
		{
			fprintf(stderr, "Error reading from file: %s\n", argv[i]);
			perror("Error. Couldn't read from file.\n");
			exit(EXIT_FAILURE);
		}
		
		//MD5Final(digest, &context);

		//Write footer including MD5 checksum
		//memcpy(footer.md5sum_data, digest, MD5_DIGEST_LENGTH);
		if(write(out_fd, &footer, sizeof(viktar_footer_t)) < 0)
		{
			fprintf(stderr, "Failed to write file footer for: %s\n", argv[i]);
			perror("Error. Failed to write file footer. \n");
			exit(EXIT_FAILURE);
		}
		close(file_fd);

		/*if(out_fd != STDOUT_FILENO)
		{
			close(out_fd); //Close the archive file if it isn't STDOUT.
		}*/

	}
	if(out_fd > -1)
		close(out_fd);
	return;
}

void validate(char * filename)
{
	int iarch = STDIN_FILENO;
	char buf[5000] = {'\0'};
	viktar_header_t md;
	viktar_footer_t footer;
	int file_member = 1;
	int match_h = 1;
	int match_d = 1;
	
	//MD5 Variables
	MD5_CTX context;
	unsigned char head_buffer[sizeof(viktar_header_t)] = {'\0'};
	unsigned char data_buffer[sizeof(viktar_footer_t)] = {'\0'};
	ssize_t bytes_read = 0;
//	uint8_t found_digest_h[MD5_DIGEST_LENGTH];
	uint8_t calc_digest_h[MD5_DIGEST_LENGTH];
//	uint8_t found_digest_d[MD5_DIGEST_LENGTH];
	uint8_t calc_digest_d[MD5_DIGEST_LENGTH];
	

	if(filename != NULL)
	{
		iarch = open(filename, O_RDONLY);
	}

	//validate tag
	read(iarch, buf, strlen(VIKTAR_TAG));
	if(strncmp(buf, VIKTAR_TAG, strlen(VIKTAR_TAG)) != 0)
	{
		//not a valid viktar file
		//print snarky message and exit(1)
		//fprintf(stderr, "snarky message\n");
		if(filename != NULL)
		{
			fprintf(stderr, "reading archive file: \"%s\"\n", filename);
			fprintf(stderr, "not a viktar file: \"%s\"\n", filename);
		}
		else
		{
			fprintf(stderr, "reading archive from stdin\n");
			fprintf(stderr, "not a viktar file: \"stdin\"\n");
		}
		exit(EXIT_FAILURE);
	}
	
	//printf("reading archive from  \"%s\"\n", filename != NULL ? filename : "stdin");

	//process the archive file metadata
	//printf("Contents of viktar file: \"%s\"\n", filename != NULL ? filename : "stdin");
	while (read(iarch, &md, sizeof(viktar_header_t)) > 0)
	{				
		match_h = 1;
		match_d = 1;
		
		//Calculating header	
		memcpy(head_buffer, &md, sizeof(viktar_header_t));
		
		MD5Init(&context);
		MD5Update(&context, head_buffer, sizeof(viktar_header_t));
		MD5Final(calc_digest_h, &context);
		
		//Calculating data
		memcpy(data_buffer, &footer, sizeof(viktar_footer_t));
		MD5Init(&context);
		bytes_read = read(iarch, data_buffer, md.st_size); 
		
    		MD5Update(&context, data_buffer, bytes_read);
		
		MD5Final(calc_digest_d, &context);
		
		//Seek to footer to retrieve file's md5 data
		//lseek(iarch, md.st_size, SEEK_CUR);
		read(iarch, &footer, sizeof(viktar_footer_t));

		//Comparing the in file md5 data to the calculated md5 data
		if(memcmp(calc_digest_h, footer.md5sum_header, MD5_DIGEST_LENGTH) != 0)
		{
			match_h = 0;
		}
		if(memcmp(calc_digest_d, footer.md5sum_data, MD5_DIGEST_LENGTH) != 0)
		{
			match_d = 0;
		}
		
		printf("Validation for data member %d:\n", file_member);
		
		//Print Header
		if(match_h == 1)
			printf("\tHeader MD5 does match:\n");
		else
			printf("\t*** Header MD5 does not match:\n");

		printf("\t\tfound:   ");
		for(int j = 0; j < MD5_DIGEST_LENGTH; ++j)
		{
			printf("%02x", calc_digest_h[j]);
		}
		printf("\n");

		printf("\t\tin file: ");
		for(int j = 0; j < MD5_DIGEST_LENGTH; ++j)
		{
			printf("%02x", footer.md5sum_header[j]);
		}
		printf("\n");
		
		//Print Data
		if(match_d == 1)
			printf("\tData MD5 does match:\n");
		else
			printf("\t*** Data MD5 does not match:\n");

		printf("\t\tfound:   ");
		for(int j = 0; j < MD5_DIGEST_LENGTH; ++j)
		{
			printf("%02x", calc_digest_d[j]);
		}
		printf("\n");
		
		printf("\t\tin file: ");
		for(int j = 0; j < MD5_DIGEST_LENGTH; ++j)
		{
			printf("%02x", footer.md5sum_data[j]);
		}
		printf("\n");
	
		//print archive member name
		memset(buf, 0, sizeof(buf));
		strncpy(buf, md.viktar_name, VIKTAR_MAX_FILE_NAME_LEN);
		if(match_h == 1 && match_d == 1)
			printf("\tValidation success:\t%s for member %d\n", filename != NULL ? filename : "stdin", file_member);
		else
			printf("\t*** Validation failure:\t%s for member %d\n", filename != NULL ? filename : "stdin", file_member);
	
		++file_member;
	}

	if (filename != NULL ) 
	{
		close(iarch);
	}

	return;


}

/*
void extract_archive(const char * archive_name, char * argv[], int argc)
{

}
void extract_files(int iarch, viktar_header_t * head)
{
	unsigned char * buff = NULL;
	viktar_header_t header = *head;
	struct timespec time[2];
	int oarch = STDOUT_FILENO;
	ssize_t bytes_read = 0;
	
	oarch = open(header.viktar_name, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	fchmod(oarch, header.st_mode);
	time[0] = header.st_atim;
	time[1] = header.st_mtim;
	
	bytes_read = 1;

	buff = (unsigned char *) malloc(header.st_size * sizeof(unsigned char));
	
	memset(buf, 0 header.st_size);

	//bytes_read = read(iarch
}
*/

















