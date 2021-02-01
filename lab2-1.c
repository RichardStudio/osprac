#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    // ID родителя не меняется, ID процесса меняется.
    printf("My pid = %d, my ppid = %d", (int)getpid(), (int)getppid());

    return 0;
}

