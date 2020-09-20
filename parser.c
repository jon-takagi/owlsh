#define  _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

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

int main() {
    char *line, **args;
    line = "ls -l ~/docs";
    printf("there are %d spaces in the line\n", count_spaces_in_line(line));
    args = parse(line);
    printf("args has: %ld items\n", sizeof(args));
    for(int i = 0; i < count_spaces_in_line(line) + 1; i++) {
        printf("%s\n", args[i]);
        free(args[i]);
    }
    free(args);
    return 0;
}
