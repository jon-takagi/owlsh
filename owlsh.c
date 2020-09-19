#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>

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
		

		printf("\nowlsh>");
		while((nread = getline(&line, &len, fp))!= -1) {
			const char delim[2] = " ";
			char* token;
			// this just prints what was last typed in
			printf("this is what was just inputted:%s", line);
	

			//iterate through the tokens
			token = strtok(line, delim);
			printf("this is the first token:%s!!", token);

			
			//built ins for exit, cd, and path
			char exit_str[] = "exit\n"; 
			if (strcmp(token, exit_str) == 0) {
				printf ("sick dude that says exit\n");
				exit(0);
			}
/*			char *cd = "cd";
			char* path = "path";

			

			if (strcmp(token, cd) == 0) {
				printf ("sick dude that says cd\n");
			}

			if (strcmp(token, path) == 0) {
				printf ("sick dude that says path\n");
			}
*/
			//start with the other tokens
			while (token != NULL) {


				token = strtok(NULL, delim);
				printf("\nmoAR toKenS!!!:%s", token);
			}

			//char *args[] = {"ls", "-l", NULL};
			// handle(args);
			printf("\nowlsh>");
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
