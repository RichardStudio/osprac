#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
//Подключил зависимости, которые узнал с помощью man.

int main(){
	//Вывод ID пользователя
	printf("User ID = %d\n",getuid());
	//Вывод ID группы
	printf("Group ID = %d\n", getgid());
	return 0;
}
