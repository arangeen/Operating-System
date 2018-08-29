/****************************************************************
 * Name        : Ahmad Rangeen                                               *
 * Class       : CSC 415                                        *
 * Date        : 7/6/2018                                               *
 * Description :  Writting a simple bash shell program          *
 * 	          that will execute simple commands. The main   *
 *                goal of the assignment is working with        *
 *                fork, pipes and exec system calls.            *
 ****************************************************************/
//May add more includes
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//Max amount allowed to read from input
#define BUFFERSIZE 256   // buffermax
//Shell prompt
#define PROMPT "myShell >> "
//sizeof shell prompt
#define PROMPTSIZE sizeof(PROMPT)

#define DELIM " \t"
#define MAX_ARGS 32


int main(int* argc, char** argv)
{

	int ofile;  // outfile
	int nfile;  // infile
	char *token;
	char *toks[MAX_ARGS];  // tokens 
	char buffer[BUFFERSIZE];  
	char copyof_buffer[BUFFERSIZE];  // buffer_copy
	
	pid_t pid;
	int background; 
	int errorr;      // err    
	int i; // keep track of arguments    // count
	
	
	do {
		printf("Myshell> ");
		
		ofile = 0;
		nfile = 0;
		background = 0;
		errorr = 0;
		i = 0;

		fgets(buffer, BUFFERSIZE, stdin);
		strncpy(copyof_buffer, buffer, BUFFERSIZE);
		
		token = strtok(buffer, DELIM);
		while(token != NULL) {
			if (strcmp(token, "&") == 0 )
			{
				background = 1;

			}else if(strcmp(token, ">") == 0){ // open file 
				
				token = strtok(NULL, DELIM);  // get file name
				ofile = open(token, O_WRONLY|O_CREAT|O_TRUNC);  		
			
			}else if (strcmp(token, "<") == 0) {
				token = strtok(NULL, DELIM);  
				nfile = open(token, O_RDONLY);
				
			}else if (strcmp(token, ">>") == 0){  // open file 
				
				token = strtok(NULL, DELIM);  // get file name
				ofile = open(token, O_WRONLY|O_APPEND|O_CREAT);
				
			}else{
				i++;
			}
			token = strtok(NULL, DELIM);	
		}
			
			
		
		if (i > 0) {  
			char *args[i + 1]; // plus 1 because last element is NULL
			args[0] = strtok(copyof_buffer, DELIM);
			int a = 0;
			while (args[a] != NULL) {
				if(background){
					if(strcmp(args[a], "&") == 0){
						args[a] = strtok(NULL, DELIM);
						break;
					}
				}
				if(ofile){
					if(strcmp(args[a], ">") == 0 || strcmp(args[i], ">>") == 0 ){
						strtok(NULL, DELIM);
						args[a] = strtok(NULL, DELIM);  
						break;
					}
				}					
				if(nfile){
					if(strcmp(args[a], "<") == 0){
						strtok(NULL, DELIM);
						args[a] = strtok(NULL, DELIM);  
						break;
					}
				}
				
				a++;
				args[a] = strtok(NULL, DELIM);
			}
		
			if (strcmp(args[0], "exit") == 0)
			{
				return 0;  // quit shell
			}

			pid = fork();
			if (pid < 0) {
				printf("Error in fork\n");
				exit(0);
				
			} else if (pid == 0) { // child process
			
				if(ofile){
					close(STDOUT_FILENO);
					dup(ofile);
				}
				if(nfile){
					close(STDIN_FILENO);
					dup(nfile);
				}
				if(errorr){
					dup2(ofile,STDERR_FILENO);
				}
				
				if(ofile){
					close(ofile);
				}
				
				if(nfile){
					close(nfile);
				}
			} else {  // parent process
				if (background == 0) {
					int exit_;
					pid_t resultw = waitpid(pid, &exit_, 0);
				
					
				}
			}
		}		
		

	} while (1);
  

  
    
    return 0;
}
