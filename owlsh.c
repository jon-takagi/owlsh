#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

const int BUFFER_SIZE = 2097152;

int main (int argc, char** argv)
{
	FILE *fp;
	char* line = NULL;
	while(1) {
		//if there be args, then do the batch mode
		if (argc > 1) {
			fp = fopen(argv[1], "r");
		} else {
			//else, it's interactive mode time
			fp = stdin;
		}
		size_t len = 0;
		int read;
		if(fp != NULL) {
			printf("owlsh> ");
			read = getline(&line, &len, fp);
			
			//if end of file:
			if(feof(fp)) {
				return 0;
			}
			printf("%s", line);
			// handle input
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
