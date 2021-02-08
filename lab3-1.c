#include <stdio.h>

int main(int argc, char *argv[], char *envp[]){
    printf("command line arguments:\n");
    int i = 0;
    while(*(argv + i)){
    printf("argv[%d] = %s\n", i, *(argv + i));
    i++;
    }
    printf("enviromantal params:\n");
    i = 0;
    while(*(envp + i)){
    printf("envp[%d] = %s\n", i, *(envp + i));
    i++;
    }

    return 0;
}
