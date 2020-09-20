#define  _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

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
        // printf("line[%d]: %c\n", i, line[i]);
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

int main() {
    char *line1 = "hello";
    char *line;
    size_t len = 0;
    getline(&line, &len, stdin);
    line = trim(line);
    int i = 0;
    for(; i < strlen(line); i++) {
        printf("%c, %c\n", line[i], line1[i]);
    }
    // printf("%d", strcmp(trim(line), line1));
    freopen(line, "w+", stdout);
    char *args[] = {"ls", "-l", NULL};
    execvp(args[0], args);
    return 0;
}
