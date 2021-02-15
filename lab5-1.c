#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
// Я не убирал большую часть кода, потому что он нужен для обработки ошибок.
int main()
{
  int     fd;
  size_t  size;
  char    string[14];
  //
  // Clear the file creation mask of the current process so that
  // the access rights of the created file exactly match the open () call parameter.
  //
  (void)umask(0);
  //
  // Try to open a file named myfile in the current directory for reading only.
  //
  if ((fd = open("myfile", O_RDONLY)) < 0) {
    printf("Can\'t open file\n");
    exit(-1);
  }
  //
  // Try to read 14 bytes from our file to the array,
  // i.e. the entire string "Hello, world!" along with the end-of-line sign.
  //
  size = read(fd, string, 14);
  if (size != 14) {
    printf("Can\'t read all string\n");
    exit(-1);
  }
  //
  // Output to the console.
  //
  printf("text from file: %s\n", string);
  if (close(fd) < 0) {
    printf("Can\'t close file\n");
  }
  return 0;
}
