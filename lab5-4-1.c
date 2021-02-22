#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
  int     fd, result;
  size_t  size;
  char    name[] = "aaa.fifo";
  (void)umask(0);
  // Create FIFO
  if (mknod(name, S_IFIFO | 0666, 0) < 0) {
    printf("Can\'t create FIFO\n");
    exit(-1);
  }
  // Open for writing
  if ((fd = open(name, O_WRONLY)) < 0) {
    printf("Can\'t open FIFO for writting\n");
    exit(-1);
  }
  // Write
  size = write(fd, "Hello, world!", 14);
  if (size != 14) {
    printf("Can\'t write all string to FIFO\n");
    exit(-1);
  }
  if (close(fd) < 0) {
    printf("app 1: Can\'t close FIFO\n"); exit(-1);
  }
  printf("app 1 exit.\n");
  return 0;
}


