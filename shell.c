/*
 ============================================================================
 Name        : shell.c
 Author      : Alexander Duong
 Version     : 1.0
 Description : A C program to serve as a shell interface that accepts user
 	 	 	   commands and then executes each command in a separate process.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <signal.h>
// The maximum length command
#define MAXLINE 80

int main(void) {
	//command line with max 40 arguments
	char *args[MAXLINE/2 + 1];
	//flag to determine when to exit program
	int should_run = 1;
	int should_Wait;

	printf("CS149 Shell from Alexander Duong\n");

	while (should_run) {
		//prompt user
		printf("Alexander-131> ");
		fflush(stdout);

		//get user input
		char input[MAXLINE];
		fgets(input, MAXLINE, stdin);

		//split user input into tokens and store in args[]
		char* token;
		token = strtok(input, " \n");
		int counter = 0;
		should_Wait = 1;

		while (token != NULL) {
			args[counter] = token;
			counter++;
			token = strtok(NULL, " \n");
		}
		if (strcmp(args[counter-1], "&") == 0) {
			should_Wait = 0;
			args[counter-1] = NULL;
		}

		args[counter] = NULL;

		pid_t pid;
		pid_t parentpid = getppid();

		int child_status;
		if (strcmp(args[0], "exit") == 0) {
			should_run = 0;
			exit(0);
		}
		//child process
		if ((pid = fork()) == 0) {
			execvp(args[0], args);
			printf("Error: Unknown command. :(\n");
			exit(1);
		}
		//parent process
		else {
			if (should_Wait == 1) {
				wait(&child_status);
			}
		}
	}
	return 0;
}
