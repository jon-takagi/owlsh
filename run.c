#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char delim = " ";
    char *buff = NULL;
    size_t len = 0;
    getline(&buff, &len, stdin);
    char *token;
    token = strtok(buff, &delim);
    while (token != NULL) {
        printf("%s", token);
        token = strtok(NULL, &delim);
    }
    // char *args[] = {"ls", "-l", NULL};
    // execvp(args[0], args);
    return 0;
}
