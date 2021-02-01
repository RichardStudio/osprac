#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid, ppid;
    int a = 0;
    pid = fork();
    //Если не получилось создать.
    if (pid == -1){
        printf("Error");
    // Действия для ребенка.
    }else if (pid == 0){
	// В ребенке увеличем а на 1.
	a = a + 1;
	pid  = getpid();
        ppid = getppid();
	printf("My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid, a);
    // Действия для родителя.
    }else{
	// В родителе увеличим а на 5.
	a = a + 5;
	pid  = getpid();
        ppid = getppid();
	printf("My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid, a);
    }

    return 0;
}
