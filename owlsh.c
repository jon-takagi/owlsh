#define  _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

const int DEBUG = 1;
// trim takes a string and returns the string without any whitespace on the ends
// because its a return value, its on the heap, so it needs to be free'd
char* trim(char* line) {
	int first = 0;
	int last  = strlen(line);
	int i = 0;
	for(; i < strlen(line); i++) {
		if(!isspace(line[i])) {
			first = i;
            break;
		}
	}
	i = strlen(line);
	for(; i >= 0; i--) {
		if(!isspace(line[i])){
			last = i;
            break;
		}
	}
    char *str = malloc((last + 2) * sizeof(char));
	memcpy(str, line+first, last + 1);
    str[last + 2]='\0';
	return str;
}
// count spaces in line takes a char[] and uses strtok to count the spaces
// only ' ' is counted
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

// parse breakes a line into an array for use with execvp
// it uses count_spaces_in_line to malloc the right number of strings
// strtok returns the next token, space is allocated and the token is copied onto the heap.

char** parse(char *line) {
    char line_arr[strlen(line)];
    strcpy(line_arr, line);
    char *token, *reenterant;
    int spaces = count_spaces_in_line(line);
    // char *args[spaces];
    char **args = (char **)malloc((spaces + 1) * sizeof(char));
    // Note that args[i][j] is same as *(*(args+i)+j)
    int i = 0;
    token = strtok_r(line_arr, " ", &reenterant);
    while(token != NULL) {
        args[i] = (char*)malloc(strlen(token) * sizeof(char));
        strcpy(args[i], token);
        token = strtok_r(NULL, " ", &reenterant);
        i += 1;
    }
    return args;
}
int handle(int argc, char **argv) {
	int i = 0;
	for(; i < argc + 1; i++) {
		printf("%s\n", argv[i]);
		fprintf(stderr, "%s\n", argv[i]);
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
		char* name_of_prompt = "owlsh> ";
		char *prompt = (char*) calloc(261, sizeof(char));
		strcpy(prompt, name_of_prompt);
		printf("%s",prompt);
		while((nread = getline(&line, &len, fp)) != -1) {
			char *cmd, *out;
			cmd = strtok(line, ">");
			out = strtok(NULL, ">");
			if(out != NULL) {
				// printf("%s", out);
				strcpy(line, trim(cmd));
				// freopen(out, "w", stdout);
				freopen(trim(out), "w+", stderr);
			}
			fprintf(stderr, "testing");
			char **args = parse(line);
			// printf("got this far");
			handle(count_spaces_in_line(line), args);
			printf("%s",prompt);
			free(args);
		}
		free(prompt);
	}
	free(line);
	fclose(fp);
	return 0;
}
