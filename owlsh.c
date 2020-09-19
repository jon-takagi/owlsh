#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>

const int DEBUG = 0;

int main (int argc, char** argv)
{
	char error_message[30] = "An error has occurred\n";
	int BUFFER_SIZE = sysconf(ARG_MAX);
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	//if there be args, then assume it's a file and read from the first one
	if (argc > 1) {
		fp = fopen(argv[1], "r");
	} else {
		//else, it's interactive mode time
		fp = stdin;
	}
	if(fp == NULL) {
    	write(STDERR_FILENO, error_message, strlen(error_message));
		fclose(fp);
		free(line);
		exit(1);
	} else {

		printf("owlsh>");
		while((nread = getline(&line, &len, fp))!= -1) {
			const char delim[] = " \t\r\n\v\f";
			char* token;
			// this just prints what was last typed in
			if (DEBUG) printf("this is what was just inputted:%s", line);
	

			//iterate through the tokens
			token = strtok(line, delim);
			if (token != NULL) 
			{
				if (DEBUG) printf("this is the first token:%s!!", token);

				
				//built ins for exit, cd, and path
				char exit_str[] = "exit"; 
				if (strcmp(token, exit_str) == 0) {
					if (DEBUG) printf ("sick dude that says exit\n");
					exit(0);
				}

				char *cd = "cd"; // I want to try all the different ways of making strings
				if (strcmp(token, cd) == 0) {
					if (DEBUG) printf ("sick dude that says cd\n");
					
					//execute chdir with the next token

					//first, make sure the next token exists
					token = strtok(NULL, delim);
					if (token == NULL) { printf("bruh u gotta put something after the cd\n"); }
					else { 
						char s[100];
						if (DEBUG) printf("current directory is: %s\n", getcwd(s, 100));
						if (DEBUG) printf("current token is: ~<3%s\n~<3", token);
						int zeroForSuccess = chdir(token);
						if (zeroForSuccess == 0)
						{
							printf("nice, your cd command worked\n");
						}
						else {
							printf("ah your cd failed\n");
						}
						if (DEBUG) printf("NEW directory is: %s\n", getcwd(s, 100));
					}
				}
	/*			char* path = "path";

				

				

				if (strcmp(token, path) == 0) {
					printf ("sick dude that says path\n");
				}
	*/
				//start with the other tokens
				while (token != NULL) {


					token = strtok(NULL, delim);
					if (DEBUG) printf("\nmoAR toKenS!!!:%s", token);
				}
			}
			//char *args[] = {"ls", "-l", NULL};
			// handle(args);
			printf("owlsh>");
		}
	}
	free(line);
	fclose(fp);
	return 0;
	//this is the size of the buffer when reading commands

	//interactive mode time
	// while (1)
	// {
	// 	printf("\nowlsh> ");
	// 	//make a buffer (aka a c style array) that is big
	// 	char buffer[BUFFER_SIZE * sizeof(char)];
	//
	//
	//
	// 	//source: https://c-for-dummies.com/blog/?p=1112
	// 	ssize_t getline(buffer, BUFFER_SIZE, stdin);
	//
	// }
}
