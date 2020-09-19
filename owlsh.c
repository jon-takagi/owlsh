#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char** argv)
{
	int BUFFER_SIZE = sysconf(ARG_MAX);
	FILE *fp;
	char line[BUFFER_SIZE];
	while(1) {
		//if there be args, then do the batch mode
		if (argc > 1) {
			fp = fopen(argv[1], "r");
		} else {
			//else, it's interactive mode time
			fp = stdin;
		}
		size_t len = 0;
		char* read;
		if(fp != NULL) {
			printf("owlsh>");
			read = fgets(line, len, fp);
			if(feof(fp)) {
				printf("EOF (CTRL + D) detecting, exiting\n");
				return 0;
			}
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
			//handle(args);

		} else {
			fprintf(stderr, "file could not be opened\n");
			fclose(fp);
			return 1;
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
