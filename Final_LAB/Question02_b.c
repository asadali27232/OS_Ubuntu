#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_CARS 10
#define MAX_TRUCKS 10

int cars = 0;
int trucks = 0;

pthread_mutex_t mutex;
pthread_cond_t carCond;
pthread_cond_t truckCond;

void *car(void *arg)
{
  int *id1 = (int *)arg;
  int id = (int)id1;
  pthread_mutex_lock(&mutex);
  while (trucks > 0)
  {
    pthread_cond_wait(&carCond, &mutex);
  }
  cars++;
  printf("Car %d is crossing the bridge\n", id);
  if (cars == 3)
  {
    cars = 0;
    pthread_cond_signal(&carCond);
  }
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void *truck(void *arg)
{
  int *id1 = (int *)arg;
  int id = (int)id1;
  pthread_mutex_lock(&mutex);
  while (cars > 0 || trucks > 0)
  {
    pthread_cond_wait(&truckCond, &mutex);
  }
  trucks++;
  printf("Truck %d is crossing the bridge\n", id);
  trucks = 0;
  pthread_cond_signal(&truckCond);
  pthread_cond_signal(&carCond);
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main()
{
  pthread_t carTid[MAX_CARS];
  pthread_t truckTid[MAX_TRUCKS];

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&carCond, NULL);
  pthread_cond_init(&truckCond, NULL);

  for (int i = 0; i < MAX_CARS; i++)
  {
    pthread_create(&carTid[i], NULL, car, (void *)i);
  }

  for (int i = 0; i < MAX_TRUCKS; i++)
  {
    pthread_create(&truckTid[i], NULL, truck, (void *)i);
  }

  for (int i = 0; i < MAX_CARS; i++)
  {
    pthread_join(carTid[i], NULL);
  }

  for (int i = 0; i < MAX_TRUCKS; i++)
  {
    pthread_join(truckTid[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&carCond);
  pthread_cond_destroy(&truckCond);

  return 0;
}