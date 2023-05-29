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

  pthread_mutex_lock(&mutex);
  if (product[5] == 1)
  {
    printf("Buffer Full\n");
    pthread_mutex_unlock(&mutex);
  }
  else
  {
    for (int i = 0; i < 5; i++)
    {
      printf("Producer\n");
      product[i] = 1;
    }
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *consumer(void *arg)
{
  pthread_mutex_lock(&mutex);
  if (product[0] == 0)
  {
    printf("Buffer Empty\n");
    pthread_mutex_unlock(&mutex);
  }
  else
  {
    for (int i = 4; i <= 0; i++)
    {
      printf("Consumer\n");
      product[i] = 0;
    }
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