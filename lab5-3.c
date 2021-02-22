#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd[2];
    int res = 0;
    int size = 1;
    // Создаем пайп.
    if(pipe(fd) < 0) {
        printf("Can\'t create pipe\n");
        exit(-1);
    }
    // Ставим флаг, чтобы не блокировался поток на запись.
    fcntl(fd[1], F_SETFL, O_NONBLOCK);
    // Записываем символ "a" пока пайп не переполнится.
    while (size == 1) {
        size = write(fd[1], "a", 1);
        res++;
    }
    printf("Pipe size %d bytes\n", res);
    return 0;
}
