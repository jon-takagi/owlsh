#define  _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

const int DEBUG = 1;

int count_spaces_in_line(char line[]) {
    int count = 0;
    int i = 0;
    for(; i < sizeof(line) / sizeof(char); i++) {
        if(line[i] == ' ') {
            count += 1;
        }
    }
    return count;
}
char** parse(char *line) {
    char line_arr[strlen(line)];
    strcpy(line_arr, line);
    char *token, *reenterant;
    int spaces = count_spaces_in_line(line);
    // char *args[spaces];
    char **args = (char **)malloc((spaces + 1) * 8);
    // Note that args[i][j] is same as *(*(args+i)+j)
    int i = 0;
    token = strtok_r(line_arr, " ", &reenterant);
    while(token != NULL) {
        args[i] = (char*)malloc(strlen(line) * sizeof(char));
        strcpy(args[i], token);
        i += 1;
        token = strtok_r(NULL, " ", &reenterant);
    }
    return args;
}
int handle(int argc, char **args) {
	int i = 0;
	for(; i < argc + 1; i++) {
		printf("%s\n", args[i]);
	}
}
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
		char* name_of_prompt = "owlsh>";
		char *prompt = (char*) calloc(261, sizeof(char));
		strcpy(prompt, name_of_prompt);
		printf("%s",prompt);
		while((nread = getline(&line, &len, fp)) != -1) {
			char **args = parse(line);
			handle(count_spaces_in_line(line), args);
			printf("%s",prompt);
			free(args);
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
