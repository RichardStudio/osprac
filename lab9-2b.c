#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
int main()
{
  int     *array;
  int     shmid;
  int     new = 1;
  char    pathname[] = "lab9-2a.c";
  key_t   key;
  long    i;
  int semid;
  // Создаем переменные для увеличения и уменьшения семафора
  struct sembuf inc;
  struct sembuf dec;
  inc.sem_num = 0;
  inc.sem_op = 1;
  inc.sem_flg = 0;
  dec.sem_num = 0;
  dec.sem_op = -1;
  dec.sem_flg = 0;

  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

   // Создаем новый или получаем уже существующий семафор.

  if ((semid = semget(key, 1, 0666)) < 0) {
    printf("Semaphore with this key does not exist\n");
    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
      printf("Can not create new semaphore");
      exit(-1);
    }
  // После создания увеличиваем на 1.
    printf("Semaphore was created\n");
    if (semop(semid, &inc, 1) < 0) {
      printf("Can not wait for condition\n");
      exit(-1);
    }
  }

  if ((shmid = shmget(key, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0) {
    if (errno != EEXIST) {
      printf("Can\'t create shared memory\n");
      exit(-1);
    } else {
      if ((shmid = shmget(key, 3*sizeof(int), 0)) < 0) {
        printf("Can\'t find shared memory\n");
        exit(-1);
      }
      new = 0;
    }
  }
  if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
    printf("Can't attach shared memory\n");
    exit(-1);
  }

  // Уменеьшаем семафор, чтобы другой процесс не получал доступ.
  if (semop(semid, &dec, 1) < 0) {
    printf("Can\'t wait for condition\n");
    exit(-1);
  }
  printf("Program B running\n");
  if (new) {
    array[0] =  0;
    array[1] =  1;
    array[2] =  1;
  } else {
    array[1] += 1;
    for(i=0; i<2000000000L; i++);
    array[2] += 1;
  }
  printf
    ("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n",
    array[0], array[1], array[2]);
  printf("Program B ended\n");

  // Увеличиваем семиафор и даем доступ.
  if (semop(semid, &inc, 1) < 0) {
 		printf("Can\'t wait for condition\n");
   	exit(-1);
  }

  if (shmdt(array) < 0) {
    printf("Can't detach shared memory\n");
    exit(-1);
  }
  return 0;
}
