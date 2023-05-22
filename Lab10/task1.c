// Write a Multi-threaded program that search a specific integer in an a rray ofo size 20. The program should create 4 threads and each thread should search 5 elements of the array. If the element is found, the thread should print the index of the element and terminate. If the element is not found, the thread should print a message that the element is not found and terminate.
#include <stdio.h>
#include <pthread.h>
#include <sched.h>

int array[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

int key = 10;
int flag = 0;

void *search(void *arg)
{
  int *n = (int *)arg;
  int num = *n;
  for (int i = num; i < num + 5; i++)
  {
    if (array[i] == key)
    {
      printf("Found %d at index %d\n", key, i);
      flag = 1;
      return NULL;
    }
  }
  return NULL;
}

int main()
{
  pthread_t thread_id[4];
  int n = 0;
  for (int i = 0; i < 4; i++)
  {
    n = i * 5;
    pthread_create(&thread_id[i], NULL, search, (void *)(&n));
    if (flag == 1)
    {
      return 0;
    }
    pthread_join(thread_id[i], NULL); // Wait for all threads to complete
  }

  if (flag == 0)
  {
    printf("Not found %d\n", key);
  }

  return 0;
}