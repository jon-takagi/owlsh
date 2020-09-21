#define  _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // for isspace
#include <sys/wait.h>


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
	i = strlen(line) - 1;
	for(; i >= 0; i--) {
		if(!isspace(line[i])){
			last = i + 1;
            break;
		}
	}
    char *str = malloc((last) * sizeof(char));
	memcpy(str, line+first, last);
    str[last + 1]='\0';
	return str;
}

// count spaces in line takes a char[] and uses strtok to count the spaces
// second arg, izard, is the type of whosamawhatsit u wanna count
int count_char_in_line(char *line, char izard ) {
    int count = 0;
    int i = 0;
    for(; i < (strlen(line) / sizeof(char)); i++) {
        if(line[i] == izard) {
            count += 1;
        }
    }
    return count;
}

// parse breakes a line into an array for use with execvp
// it uses count_char_in_line to malloc the right number of strings
// strtok returns the next token, space is allocated and the token is copied onto the heap.

char** parse(char *line) {
    char line_arr[strlen(line)];
    strcpy(line_arr, line);
    char *token, *reenterant;
    int spaces = count_char_in_line(line, ' ');
    // char *args[spaces];
    char **args = (char **)malloc((spaces + 1) * sizeof(char));
    // Note that args[i][j] is same as *(*(args+i)+j)
    int i = 0;
    token = strtok_r(line_arr, " \n", &reenterant);
    while(token != NULL) {
        args[i] = (char*)malloc(strlen(token) * sizeof(char));
        strcpy(args[i], token);
        token = strtok_r(NULL, " \n", &reenterant);
        i += 1;
    }
    return args;
}


// handles a command and executes either a builtin or searches path for it
// args:
//   argc  - number of things in argv
//   argv  - a list of all the args
//   PATH  - this is the PATH that has all the searchable directories in it
//   prompt- what's shown before "owlsh>" in the prompty thing
// returns -1 if it fails, but that's chill. it's allowed to fail. failures are how the code learns 😊👐
int handle(int argc, char **argv, char *PATH, char *prompt) {
	int i = 0;
	char* token;

	if(DEBUG) {
		printf("number of args is %i\n", argc);
		for(; i < argc; i++) {
			printf("%s\n", argv[i]);
		}
	}

	if (argc == 0){
		return -1;

	}

	token = trim(argv[0]);

	if (strcmp(token, "exit") == 0) {
		if (DEBUG) printf ("sick dude that says exit\n");
		exit(69);
	}

	if (strcmp(token, "cd") == 0) {
		if (DEBUG) printf ("sick dude that says cd\n");

		//execute chdir with the next token

		//first, make sure the next token exists
		//token = strtok(NULL, delim);
		if (argc <= 1) {
			printf("u need to put something after the cd\n");

		}
		else {
			token = argv[1];
			char s[100];
			if (DEBUG) printf("current directory is: %s\n", getcwd(s, 100));
			if (DEBUG) printf("current token is: ~<3%s\n~<3", token);
			int zeroForSuccess = chdir(token);
			if (zeroForSuccess == 0)
			{
				if (DEBUG) printf("nice, your cd command worked\n");
				char *old_prompt = (char*) calloc(261, sizeof(char));
				strcpy(old_prompt, prompt);

				//clearing prompt
				memset (prompt, 0, sizeof(prompt));

				strcpy(prompt, token);
				strcat(prompt,"/");
				strcat(prompt, old_prompt);

				free(old_prompt);
				if (DEBUG) printf( "new prompt is %s\n", prompt);
			}
			else {
				printf("that's not a directory :(\n");
			}
			if (DEBUG) printf("NEW directory is: %s\n", getcwd(s, 100));
		}
	}

	if (strcmp(token, "path") == 0) {
		if (DEBUG) printf ("sick dude that says path\n");
			if (argc == 1) {
				printf("%s\n",PATH);
			} else {
				int i = 1;
				for(; i < argc; i++){
					token = argv[i];
					if (DEBUG) printf("token is '%s'\n", token);
					strcat(PATH, " ");
					strcat(PATH, token);
				}
			}
		}

	execvp(argv[0], argv);
}

int main (int argc, char** argv)
{
	//creating prompt and PATH char*
	char *path_initially = " ";
	char *PATH = (char*) calloc(400, sizeof(char));
	strcpy(PATH, path_initially);

	char* name_of_prompt = "owlsh> ";
	char *prompt = (char*) calloc(261, sizeof(char));
	strcpy(prompt, name_of_prompt);

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
		printf("%s",prompt);
		int pid;
		while((nread = getline(&line, &len, fp)) != -1) {
			int i = 0;
			int pidc = count_char_in_line(line, '&') + 1;
			int pids[pidc];
			int rcs[pidc];
			char *token = strtok(line, "&");
			while (token != NULL) {
				printf("token: %s\n", token);
				pid = fork();
				if(pid == 0) {
					printf("now in child, handling: %s\n", token);
					char *cmd, *out;
					cmd = strtok(token, ">");
					out = strtok(NULL, ">");
					if(out != NULL) {
						freopen(trim(out), "w", stdout);
						freopen(trim(out), "w", stderr);
					}
					char **args = parse(trim(cmd));
					printf("cmd: %s\n", args[0]);
					handle(count_char_in_line(trim(token), ' ') + 1, args, PATH, prompt);
					free(args);
					exit(1);
				} else {
					pids[i] = pid;
					i ++;
				}
				token = strtok(NULL, "&");
			}
			i = 0;
			for(; i < pidc; i++) {
				waitpid(pids[i], &rcs[i], 0);
			}
			for(i = 0; i < pidc; i++) {
				if(WIFEXITED(rcs[i])) {
					printf("exit code: %d\n", WEXITSTATUS(rcs[i]));
					if(WEXITSTATUS(rcs[i]) == 69) {
						exit(0);
					}
				}
			}

			printf("%s",prompt);
		}
	}
	free(prompt);
	free(line);
	fclose(fp);
	return 0;
}
