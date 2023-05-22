// Mutex Locks
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int product = 0;

void *producer(void *arg)
{
  printf("Producer\n");
  pthread_mutex_lock(&mutex);
  if (product == 1)
  {
    pthread_mutex_unlock(&mutex);
  }
  if (product == 0)
  {
    product = 1;
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *consumer(void *arg)
{
  printf("Consumer\n");
  pthread_mutex_lock(&mutex);
  if (product == 0)
  {
    pthread_mutex_unlock(&mutex);
  }
  if (product == 1)
  {
    product = 0;
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main()
{
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);
  pthrad_t thread1, thread2;

  pthread_create(&thread1, NULL, producer, NULL);
  pthread_create(&thread2, NULL, consumer, NULL);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  pthread_mutex_destroy(&mutex);
  return 0;
}