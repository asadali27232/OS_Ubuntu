// Write a c program that takes a value n from user then create a thread that prints odd number till n and another thread that prints even number till n.

#include <stdio.h>
#include <pthread.h>
#include <sched.h>

void *odd(void *arg)
{
  int *n = (int *)arg;
  int num = *n;
  for (int i = 1; i <= num; i++)
  {
    if (i % 2 == 1)
    {
      printf("%d ", i);
    }
    sched_yield(); // Context Switching
  }
  return NULL;
}

void *even(void *arg)
{
  int *n = (int *)arg;
  int num = *n;
  for (int i = 1; i <= num; i++)
  {
    if (i % 2 == 0)
    {
      printf("%d ", i);
    }
    sched_yield(); // Context Switching
  }
  return NULL;
}

int main()
{
  int n = 10;
  pthread_t thread_id[2];

  pthread_create(&thread_id[0], NULL, odd, (void *)(&n));
  pthread_create(&thread_id[1], NULL, even, (void *)(&n));

  pthread_join(thread_id[0], NULL);
  pthread_join(thread_id[1], NULL);

  return 0;
}
