#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int     fd[2], fd2[2], result;
  size_t size;
  char  resstring[14];
  if (pipe(fd) < 0) {
    printf("Can\'t open pipe\n");
    exit(-1);
  }
  if (pipe(fd2) < 0){
    printf("Can\'t open 2nd pipe\n");
  }
  result = fork();
  if (result < 0) {
    printf("Can\'t fork child\n");
    exit(-1);
  } else if (result > 0) {
   /* Parent process */
    // Close reading side of 1st pipe.
    if (close(fd[0]) < 0) {
      printf("parent: Can\'t close reading side of pipe\n"); exit(-1);
    }
    // Close writing side of 2nd pipe.
    if (close(fd2[1]) < 0) {
      printf("parent: Can\'t close writing side of 2nd pipe\n"); exit(-1);
    }
    // Write to 1st pipe.
    size = write(fd[1], "Hello, world!", 14);
    if (size != 14) {
      printf("Can\'t write all string to pipe\n");
      exit(-1);
    }
    if (close(fd[1]) < 0) {
      printf("parent: Can\'t close writing side of pipe\n"); exit(-1);
    }
    //Write to 2nd pipe.
    size = read(fd2[0], resstring, 14);
    if (size != 14) {
      printf("Can\'t read all string from 2nd pipe\n");
      exit(-1);
    }
    printf("Parent exit, resstring: %s\n", resstring);
    if (close(fd2[0]) < 0) {
      printf("parent: Can\'t close reading side of 2nd pipe\n"); exit(-1);
    }
  } else {
    /* Child process */
    // Close writing side of 1st pipe.
    if (close(fd[1]) < 0) {
      printf("child: Can\'t close writing side of pipe\n"); exit(-1);
    }
    // Close reading side of 2nd pipe.
    if (close(fd2[0]) < 0) {
      printf("child: Can\'t close reading side of 2nd pipe\n"); exit(-1);
    }
    // Read from 1st pipe.
    size = read(fd[0], resstring, 14);
    if (size < 0) {
      printf("Can\'t read string from pipe\n");
      exit(-1);
    }
    // Write to 2nd pipe.
    size = write(fd2[1], "World, hello!", 14);
    if (size < 0) {
      printf("Can\'t write string to 2nd pipe\n");
      exit(-1);
    }
    if (close(fd2[1]) < 0) {
      printf("child: Can\'t close writing side of 2nd pipe\n"); exit(-1);
    }
    printf("Child exit, resstring: %s\n", resstring);
    if (close(fd[0]) < 0) {
      printf("child: Can\'t close reading side of pipe\n"); exit(-1);
    }
  }
  return 0;
}
