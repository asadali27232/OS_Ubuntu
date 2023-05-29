// Mutex with conditional veriables
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t empty;
pthread_cond_t full;

int buffer_index = ;
int product[buffer_index];

void *producer(void *arg)
{
  for (int i = 0; i < 5; i++)
  {
    pthread_mutex_lock(&mutex);
    while (buffer_index == 4)
    {
      pthread_cond_wait(&full, &mutex);
    }
    product[buffer_index] = 1;
    buffer_index++;
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *consumer(void *arg)
{
  for (int i = 0; i < 5; i++)
  {
    pthread_mutex_lock(&mutex);
    while (buffer_index == 0)
    {
      pthread_cond_wait(&empty, &mutex);
    }
    product[buffer_index] = 0;
    buffer_index--;
    pthread_cond_signal(&full);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main()
{
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&empty, NULL);
  pthread_cond_init(&full, NULL);

  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, producer, NULL);
  pthread_create(&thread2, NULL, consumer, NULL);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&empty);
  pthread_cond_destroy(&full);

  return 0;
}