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
    printf("first non space: %d\n", first);
    printf("last non space: %d\n", last);
    // char *str = ":(";
    // char *str = malloc((last - first) * sizeof(char));
    char *str = malloc((last + 2) * sizeof(char));

	memcpy(str, line+first, last + 1);
    str[last + 2]='\0';
    printf("%s\n", str);
	return str;
}

int main() {
    char *line = "hello";
    trim(line);
    // freopen("hello.txt", "w", stdout);
    // char *args[] = {"ls", "-l", NULL};
    // execvp(args[0], args);
    return 0;
}
