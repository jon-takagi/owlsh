#include <stdio.h>
#include <string.h>

int main() {
    char line1[] = {'h', 'e', 'l', 'l', 'o', 'w', 'o','r','l','d','\0'};
    // char *line1 = "helloworld";
    char *reenterant = line1;
    char *foo, *bar;
    foo = strtok_r(line1, " ", &reenterant);
    printf("%s\n", foo);
    bar = strtok_r(NULL, " ", &reenterant);
    if(bar != NULL) {
        printf("%s\n", bar);
    }
    return 0;
}
