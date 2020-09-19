#define  _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int count_spaces_in_line(char line[]) {
    int count = 0;
    for(int i = 0; i < sizeof(line) / sizeof(char); i++) {
        if(line[i] == ' ') {
            count += 1;
        }
    }
    return count;
}
char** parse(char *line) {
    char line_arr[sizeof(line)];
    strcpy(line_arr, line);
    char *token, *reenterant;
    int spaces = count_spaces_in_line(line);
    char **args = (char **)calloc(spaces + 1, 4096*32);
    // Note that args[i][j] is same as *(*(args+i)+j)

    int i = 0;
    token = strtok_r(line_arr, " ", &reenterant);
    while(token != NULL) {
        // strcpy((char*)(*(args + 4096*32*i)), token);
        // *(args + 4096*32*i) = *token;
        // for(int j = 0; j < sizeof(token); j++) {
        //     *(args + 4096*32*i + j) = token[j];
        // }
        strcpy(args[i], token);
        i += 1;
        token = strtok_r(NULL, " ", &reenterant);
    }
    return args;
}

int main() {
    char *line, **args;
    // size_t len = 10;
    // getline(&line, &len, stdin);
    line = "ls -l ~/docs";
    printf("there are %d spaces in the line\n", count_spaces_in_line(line));
    args = parse(line);
    // printf("args has: %ld items\n", sizeof(args));
    // for(int i = 0; i < count_spaces_in_line(line) + 1; i++) {
    //     printf("%s\n", args[i]);
    //     free(args[i]);
    // }
    // free(args);
    return 0;
}
