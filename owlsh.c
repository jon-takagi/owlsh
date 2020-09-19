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
	char line = (char*) malloc(BUFFER_SIZE);
	size_t len = 0;
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
		while(getline(&line, &len, fp)) {
			printf("%s", line);
	
			//built ins for exit, cd, and path
			char exit[] = "exit"; 
			char *cd = "cd";
			char* path = "path";

			if (strcmp(line, exit) == 0) {
				printf ("sick dude that says exit\n");
			}

			if (strcmp(line, cd) == 0) {
				printf ("sick dude that says cd\n");
			}


			char *args[] = {"ls", "-l", NULL};
			// handle(args);

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
