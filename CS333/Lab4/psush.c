//Bradley Chang CS333 Lab 4 PSUSH
//

#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#include "cmd_parse.h"

#define PROMPT_LEN 100
#define DIRECT_LEN 50
#define ENV_LEN 20
#define HIST 15

// I have this a global so that I don't have to pass it to every
// function where I might want to use it. Yes, I know global variables
// are frowned upon, but there are a couple useful uses for them.
// This is one.
unsigned short is_verbose = 0;
char *hist[HIST] = {0};
static volatile sig_atomic_t num_fork = 0;

void sigint_handler(int sig);
void sigchld_handler(int sig);
void free_history(void);

int 
process_user_input_simple(void)
{
    char str[MAX_STR_LEN] = {'\0'};
    char *ret_val = NULL;
    char *raw_cmd = NULL;
    cmd_list_t *cmd_list = NULL;
    int cmd_count = 0;
    char prompt[PROMPT_LEN] = {'\0'};
    char directory[DIRECT_LEN] = {'\0'};
    char sys_name[ENV_LEN] = {'\0'};
    memset(hist, 0, sizeof(hist));

    for ( ; ; ) {
        // Set up a cool user prompt.
        // test to see of stdout is a terminal device (a tty)
	
	//Check if stdout is connected to a terminal
	if(isatty(fileno(stdout)))
	{
		getcwd(directory, DIRECT_LEN);
		gethostname(sys_name, ENV_LEN);
		sprintf(prompt, " %s %s\n%s@%s # "
			,PROMPT_STR
			,directory
			,getenv("LOGNAME")
			,sys_name
		    );
		fputs(prompt, stdout);
        }
	memset(str, 0, MAX_STR_LEN);
        ret_val = fgets(str, MAX_STR_LEN, stdin);

        if (NULL == ret_val) {
            // end of input, a control-D was pressed.
            // Bust out of the input loop and go home.
            break;
        }

        // STOMP on the pesky trailing newline returned from fgets().
        if (str[strlen(str) - 1] == '\n') {
            // replace the newline with a NULL
            str[strlen(str) - 1] = '\0';
        }
        if (strlen(str) == 0) {
            // An empty command line.
            // Just jump back to the promt and fgets().
            // Don't start telling me I'm going to get cooties by
            // using continue.
            continue;
        }

        if (strcmp(str, BYE_CMD) == 0) {
            // Pickup your toys and go home. I just hope there are not
            // any memory leaks. ;-)
		free_list(cmd_list);
		cmd_list = NULL;

            break;
        }

        // I put the update of the history of command in here.
	free(hist[HIST - 1]);
	//memmove(&(hist[1]), &(hist[0]), (HIST - 1) * sizeof(char *));
	for(int i = HIST - 2; i >= 0; i--)
	{
		hist[i+1] = hist[i];
	}
	hist[0] = strdup(str);

        // Basic commands are pipe delimited.
        // This is really for Stage 2.
        raw_cmd = strtok(str, PIPE_DELIM);

        cmd_list = (cmd_list_t *) calloc(1, sizeof(cmd_list_t));

        // This block should probably be put into its own function.
        cmd_count = 0;
        while (raw_cmd != NULL ) {
            cmd_t *cmd = (cmd_t *) calloc(1, sizeof(cmd_t));

            cmd->raw_cmd = strdup(raw_cmd);
            cmd->list_location = cmd_count++;

            if (cmd_list->head == NULL) {
                // An empty list.
                cmd_list->tail = cmd_list->head = cmd;
            }
            else {
                // Make this the last in the list of cmds
                cmd_list->tail->next = cmd;
                cmd_list->tail = cmd;
            }
            cmd_list->count++;

            // Get the next raw command.
            raw_cmd = strtok(NULL, PIPE_DELIM);
        }
        // Now that I have a linked list of the pipe delimited commands,
        // go through each individual command.
        parse_commands(cmd_list);

        // This is a really good place to call a function to exec the
        // the commands just parsed from the user's command line.
        exec_commands(cmd_list);

        // We (that includes you) need to free up all the stuff we just
        // allocated from the heap. That linked list of linked lists looks
        // like it will be nasty to free up, but just follow the memory.
        free_list(cmd_list);
        cmd_list = NULL;
    }

    free_history();
    return(EXIT_SUCCESS);
}

void 
simple_argv(int argc, char *argv[] )
{
    int opt;

    while ((opt = getopt(argc, argv, "hv")) != -1) {
        switch (opt) {
        case 'h':
            // help
            // Show something helpful
            fprintf(stdout, "You must be out of your Vulcan mind if you think\n"
                    "I'm going to put helpful things in here.\n\n");
            exit(EXIT_SUCCESS);
            break;
        case 'v':
            // verbose option to anything
            // I have this such that I can have -v on the command line multiple
            // time to increase the verbosity of the output.
            is_verbose++;
            if (is_verbose) {
                fprintf(stderr, "verbose: verbose option selected: %d\n"
                        , is_verbose);
            }
            break;
        case '?':
            fprintf(stderr, "*** Unknown option used, ignoring. ***\n");
            break;
        default:
            fprintf(stderr, "*** Oops, something strange happened <%c> ... ignoring ...***\n", opt);
            break;
        }
    }
}

void 
exec_commands( cmd_list_t *cmds ) 
{
    cmd_t *cmd = cmds->head;
    /*
    int i;
    int j;
*/

    if (1 == cmds->count) {
        if (!cmd->cmd) {
            // if it is an empty command, bail.
            return;
        }
        if (0 == strcmp(cmd->cmd, CD_CMD)) {
            if (0 == cmd->param_count) {
                // Just a "cd" on the command line without a target directory
                // need to cd to the HOME directory.

                // Is there an environment variable, somewhere, that contains
                // the HOME directory that could be used as an argument to
                // the chdir() fucntion?
		if(chdir(getenv("HOME")) != 0)
		{
			fprintf(stderr, "cd error");
		}

            }
            else {
                // try and cd to the target directory. It would be good to check
                // for errors here.
                if (0 == chdir(cmd->param_list->param)) {
                    // a happy chdir!  ;-)

                }
                else {
                    // a sad chdir.  :-(

                }
            }
        }
        else if (0 == strcmp(cmd->cmd, CWD_CMD)) {
            char str[MAXPATHLEN];

            // Fetch the Current Working Wirectory (CWD).
            // aka - get country western dancing
            getcwd(str, MAXPATHLEN); 
            printf(" " CWD_CMD ": %s\n", str);
        }
        else if (0 == strcmp(cmd->cmd, ECHO_CMD)) {
            // insert code here
            // insert code here
            // Is that an echo?
	    
	    param_t * temp = cmd->param_list;
	    while(temp)
	    {
		    printf("%s ", temp->param);
		    temp = temp->next;
	    }
	    printf("\n");
	
			
        }
        else if (0 == strcmp(cmd->cmd, HISTORY_CMD)) {
            // display the history here
	    /*
	    i = 0;
	    j = 1;
	    while(i <= HIST)
	    {
		    if(hist[HIST-i] != NULL)
		    {
			    printf("%d %s\n", j, hist[HIST-i]);
			    ++j;
		    }
		    ++i;
	    }
	    */
	    int count = 0;
	    for(int i = HIST - 1; i >= 0; --i)
	    {
		    if(hist[i])
		    {
			    printf("   %d  %s\n", ++count, hist[i]);
		    }
	    }
        }
        else {
            // A single command to create and exec
            // If you really do things correctly, you don't need a special call
            // for a single command, as distinguished from multiple commands.
	    pid_t pid = fork();
	    param_t * curr_param = NULL;
		
	    //Check to see if forking failed.
	    if (pid < 0) 	
	    {
		perror("fork failed");
		exit(EXIT_FAILURE);
	    }
	    
	    else if (pid == 0)
    	    {
		int cmd_argc = 0;
		char * cmd_argv[cmd->param_count + 2];
		
		cmd_argv[cmd_argc++] = cmd->cmd;
		
		curr_param = cmd->param_list;
		
		while(curr_param != NULL)
		{
			cmd_argv[cmd_argc++] = curr_param->param;
			curr_param = curr_param->next;
		}

		cmd_argv[cmd_argc] = NULL;
		
		//Handle child redirection.	
		//Input redirection
		if(REDIRECT_FILE == cmd->input_src)
		{
			int fd;

			fd = open(cmd->input_file_name, O_RDONLY);
			if(fd < 0)
			{
				fprintf(stderr, "******* redir in failed %d *******\n", errno);
				free_list(cmds);
				free_history();
				exit(EXIT_FAILURE);
				//exit(7);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		
		//Output redirection
		if(REDIRECT_FILE == cmd->output_dest)
		{
			int fd;
			fd = open(cmd->output_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(fd < 0)
			{
				fprintf(stderr, "******* redir out failed %d *******\n", errno);
				free_list(cmds);
				free_history();
				exit(EXIT_FAILURE);
				//exit(7);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		//Execute 
		if (execvp(cmd->cmd, cmd_argv) == -1) 
		{
			perror("Failed to execute command");
			free_list(cmds);
			free_history();
			exit(EXIT_FAILURE);
		}
	    }

	   else
	   {
		//Parent process.
		int status;
		waitpid(pid, &status, 0);

		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			printf("child killed by signal\n");
		}
	   }
	}
    }
    else {
        // Other things???
        // More than one command on the command line. Who'da thunk it!
        // This really falls into Stage 2.
    	
	pid_t pid = 0;
	int pipes[2] = {-1, -1};
	int p_trail = -1;
	
	while(cmd)
	{
		//if not last then create pipe
		if(cmd != cmds->tail)
		{
			pipe(pipes);
		}
		switch((pid = fork()))	//Now forking
		{
		case -1:
			//Fail to fork
			perror("Failed to fork new process");
			exit(EXIT_FAILURE);
			break;
		case 0:
		{	
			int cmd_argc = 0;
			char * cmd_argv[cmd->param_count + 2];	
	    		param_t * curr_param = NULL;
			
			//Child code???
			if(cmd != cmds->head)	//If not first
			{
				dup2(p_trail, STDIN_FILENO);
			}
			if(cmd != cmds->tail)	//If not last
			{
				dup2(pipes[STDOUT_FILENO],STDOUT_FILENO);
				close(pipes[STDIN_FILENO]);
				close(pipes[STDOUT_FILENO]);
			}

			cmd_argv[cmd_argc++] = cmd->cmd;
			curr_param = cmd->param_list;
			while(curr_param != NULL)
			{
				cmd_argv[cmd_argc++] = curr_param->param;
				curr_param = curr_param->next;
			}
			cmd_argv[cmd_argc] = NULL;
			
			//Input redirection
			if(REDIRECT_FILE == cmd->input_src)
			{
				int fd;

				fd = open(cmd->input_file_name, O_RDONLY);
				if(fd < 0)
				{
					fprintf(stderr, "******* redir in failed %d *******\n", errno);
					free_list(cmds);
					free_history();
					exit(EXIT_FAILURE);
					//exit(7);
				}
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			//Output redirection
			if(REDIRECT_FILE == cmd->output_dest)
			{
				int fd;
				fd = open(cmd->output_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if(fd < 0)
				{
					fprintf(stderr, "******* redir out failed %d *******\n", errno);
					free_list(cmds);
					free_history();
					exit(EXIT_FAILURE);
					//exit(7);
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}

			if (execvp(cmd->cmd, cmd_argv) == -1) 
			{
				perror("Failed to execute command");
				free_list(cmds);
				free_history();
				exit(EXIT_FAILURE);
			}
			break;
		}
		default:
			//Parent code
			if (cmd != cmds->head)
				close(p_trail);
			if(cmd != cmds->tail)
			{
				close(pipes[STDOUT_FILENO]);
				p_trail = pipes[STDIN_FILENO];
			}
			break;
		}
		cmd = cmd->next;
	
	}
   
        while (wait(NULL) >= 0);
	
    }
}

void
free_list(cmd_list_t *cmd_list)
{
    // Proof left to the student.
    // You thought I was going to do this for you! HA! You get
    // the enjoyment of doing it for yourself.
	cmd_t * hold;

	if(!cmd_list)
	    return;
	while(cmd_list->head)
	{
		hold = cmd_list->head;
		cmd_list->head = hold->next;
		
		free_cmd(hold);

		free(hold);
	}
	cmd_list->head = NULL;
	cmd_list->tail = NULL;

	free(cmd_list);

	return;
}

void
print_list(cmd_list_t *cmd_list)
{
    cmd_t *cmd = cmd_list->head;

    while (NULL != cmd) {
        print_cmd(cmd);
        cmd = cmd->next;
    }
}

void
free_cmd (cmd_t *cmd)
{
    // Proof left to the student.
    // Yep, on yer own.
    // I beleive in you.
	if(!cmd)
		return;
	if(cmd->raw_cmd)
		free(cmd->raw_cmd);
	
	if(cmd->cmd)
		free(cmd->cmd);

	//Traverse list of params
	while(cmd->param_list)
	{
		param_t * hold = cmd->param_list;
		cmd->param_list = hold->next;

		//Dealloc string with param
		if(hold->param)
			free(hold->param);
		//Dealloc the current node
		if(hold)
			free(hold);
	}
	if(cmd->input_file_name)
		free(cmd->input_file_name);
	if(cmd->output_file_name)
		free(cmd->output_file_name);
	return;

}

// Oooooo, this is nice. Show the fully parsed command line in a nice
// easy to read and digest format.
void
print_cmd(cmd_t *cmd)
{
    param_t *param = NULL;
    int pcount = 1;

    fprintf(stderr,"raw text: +%s+\n", cmd->raw_cmd);
    fprintf(stderr,"\tbase command: +%s+\n", cmd->cmd);
    fprintf(stderr,"\tparam count: %d\n", cmd->param_count);
    param = cmd->param_list;

    while (NULL != param) {
        fprintf(stderr,"\t\tparam %d: %s\n", pcount, param->param);
        param = param->next;
        pcount++;
    }

    fprintf(stderr,"\tinput source: %s\n"
            , (cmd->input_src == REDIRECT_FILE ? "redirect file" :
               (cmd->input_src == REDIRECT_PIPE ? "redirect pipe" : "redirect none")));
    fprintf(stderr,"\toutput dest:  %s\n"
            , (cmd->output_dest == REDIRECT_FILE ? "redirect file" :
               (cmd->output_dest == REDIRECT_PIPE ? "redirect pipe" : "redirect none")));
    fprintf(stderr,"\tinput file name:  %s\n"
            , (NULL == cmd->input_file_name ? "<na>" : cmd->input_file_name));
    fprintf(stderr,"\toutput file name: %s\n"
            , (NULL == cmd->output_file_name ? "<na>" : cmd->output_file_name));
    fprintf(stderr,"\tlocation in list of commands: %d\n", cmd->list_location);
    fprintf(stderr,"\n");
}

// Remember how I told you that use of alloca() is
// dangerous? You can trust me. I'm a professional.
// And, if you mention this in class, I'll deny it
// ever happened. What happens in stralloca stays in
// stralloca.
#define stralloca(_R,_S) {(_R) = alloca(strlen(_S) + 1); strcpy(_R,_S);}

void
parse_commands(cmd_list_t *cmd_list)
{
    cmd_t *cmd = cmd_list->head;
    char *arg;
    char *raw;

    while (cmd) {
        // Because I'm going to be calling strtok() on the string, which does
        // alter the string, I want to make a copy of it. That's why I strdup()
        // it.
        // Given that command lines should not be tooooo long, this might
        // be a reasonable place to try out alloca(), to replace the strdup()
        // used below. It would reduce heap fragmentation.
        //raw = strdup(cmd->raw_cmd);

        // Following my comments and trying out alloca() in here. I feel the rush
        // of excitement from the pending doom of alloca(), from a macro even.
        // It's like double exciting.
        stralloca(raw, cmd->raw_cmd);

        arg = strtok(raw, SPACE_DELIM);
        if (NULL == arg) {
            // The way I've done this is like ya'know way UGLY.
            // Please, look away.
            // If the first command from the command line is empty,
            // ignore it and move to the next command.
            // No need free with alloca memory.
            //free(raw);
            cmd = cmd->next;
            // I guess I could put everything below in an else block.
            continue;
        }
        // I put something in here to strip out the single quotes if
        // they are the first/last characters in arg.
        if (arg[0] == '\'') {
            arg++;
        }
        if (arg[strlen(arg) - 1] == '\'') {
            arg[strlen(arg) - 1] = '\0';
        }
        cmd->cmd = strdup(arg);
        // Initialize these to the default values.
        cmd->input_src = REDIRECT_NONE;
        cmd->output_dest = REDIRECT_NONE;

        while ((arg = strtok(NULL, SPACE_DELIM)) != NULL) {
            if (strcmp(arg, REDIR_IN) == 0) {
                // redirect stdin

                //
                // If the input_src is something other than REDIRECT_NONE, then
                // this is an improper command.
                //

                // If this is anything other than the FIRST cmd in the list,
                // then this is an error.

                cmd->input_file_name = strdup(strtok(NULL, SPACE_DELIM));
                cmd->input_src = REDIRECT_FILE;
            }
            else if (strcmp(arg, REDIR_OUT) == 0) {
                // redirect stdout
                //
                // If the output_dest is something other than REDIRECT_NONE, then
                // this is an improper command.
                //

                // If this is anything other than the LAST cmd in the list,
                // then this is an error.

                cmd->output_file_name = strdup(strtok(NULL, SPACE_DELIM));
                cmd->output_dest = REDIRECT_FILE;
            }
            else {
                // add next param
                param_t *param = (param_t *) calloc(1, sizeof(param_t));
                param_t *cparam = cmd->param_list;

                cmd->param_count++;
                // Put something in here to strip out the single quotes if
                // they are the first/last characters in arg.
                if (arg[0] == '\'') {
                    arg++;
                }
                if (arg[strlen(arg) - 1] == '\'') {
                    arg[strlen(arg) - 1] = '\0';
                }
                param->param = strdup(arg);
                if (NULL == cparam) {
                    cmd->param_list = param;
                }
                else {
                    // I should put a tail pointer on this.
                    while (cparam->next != NULL) {
                        cparam = cparam->next;
                    }
                    cparam->next = param;
                }
            }
        }
        // This could overwite some bogus file redirection.
        if (cmd->list_location > 0) {
            cmd->input_src = REDIRECT_PIPE;
        }
        if (cmd->list_location < (cmd_list->count - 1)) {
            cmd->output_dest = REDIRECT_PIPE;
        }

        // No need free with alloca memory.
        //free(raw);
        cmd = cmd->next;
    }

    if (is_verbose > 0) {
        print_list(cmd_list);
    }
}
void sigint_handler(int sig)
{
	//printf("Signal for %d caught\n", sig);
	sig++;
	sig--;
}
/*void sigchld_handler(int sig)
{
	int status;
	pid_t cpid;

	//while ((cpid = waitpid(-1, &status, WNOHANG)) > 0)
	while ((cpid = wait(NULL)) >= 0)
	{
		//printf("\nParent signal handler: Found child exit %d: pid: %d exit value: %d\n", sig, cpid, WEXITSTATUS(status));
		num_fork--;
	}
	if (num_fork == 0)
	{
		printf("all child processes reaped\n");
		printf("Control-\\ to exit\n");
	}
	
}
*/
void free_history(void)
{
	for(int i = 0; i < HIST; ++i)
	{
		if(hist[i])
		{
			free(hist[i]);
			hist[i] = NULL;
		}
	}
}

int 
main( int argc, char *argv[] )
{
    int ret = 0;

    signal(SIGINT, sigint_handler);
    //signal(SIGCHLD, sigchld_handler);

    simple_argv(argc, argv);
    ret = process_user_input_simple();

    return ret;
}
