// Make 2 Threads, first thread should take an array of size 10, second thread should sort the array.

#include <stdio.h>
#include <pthread.h>

int *a[10];

void *input(void *arg)
{
  printf("Thread created successfully\n");
  printf("Thread id is: %ld\n", pthread_self());
  printf("Enter 10 numbers: ");
  for (int i = 0; i < 10; i++)
  {
    &a[i] = rand() % 100; // [0, 99]
  }
  return NULL;
}

void *sort(void *arg)
{
  printf("Thread created successfully\n");
  printf("Thread id is: %ld\n", pthread_self());
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (a[j] > a[j + 1])
      {
        int temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
      }
    }
  }
  printf("Sorted array: ");
  for (int i = 0; i < 10; i++)
  {
    printf("%d ", a[i]);
  }
  printf("\n");
  return NULL;
}

int main()
{
  printf("Hello World\n");
  pthread_t thread_id[2];

  pthread_create(&thread_id[0], NULL, input, NULL);
  pthread_join(thread_id[0], NULL); // Place join here to make sure that the array is filled before sorting

  pthread_create(&thread_id[1], NULL, sort, NULL);
  pthread_join(thread_id[1], NULL);

  return 0;
}