#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int availableTickets = 10;
pthread_mutex_t mutex;

void *ticketBooker(void *arg)
{
  if (availableTickets == 0)
  {
    printf("No tickets available\n");
    return NULL;
  }
  while (availableTickets > 0)
  {
    pthread_mutex_lock(&mutex);
    if (availableTickets > 0)
    {
      printf("Ticket Booked by client_%d\n", (int)arg);
      availableTickets--;
    }
    pthread_mutex_unlock(&mutex);
    sleep(1);
  }
  return NULL;
}

void *ticketChecker(void *arg)
{
  if (availableTickets == 10)
  {
    printf("No tickets booked yet\n");
    return NULL;
  }
  while (availableTickets < 10)
  {
    pthread_mutex_lock(&mutex);
    if (availableTickets < 10)
    {
      printf("Ticket Cancelled by client_%d\n", (int)arg);
      availableTickets++;
    }
    pthread_mutex_unlock(&mutex);
    sleep(1);
  }
  return NULL;
}

int main()
{
  pthread_t tid[20];
  pthread_mutex_init(&mutex, NULL);

  for (int i = 0; i < 10; i++)
  {
    pthread_create(&tid[i], NULL, ticketBooker, (void *)i);
  }

  for (int i = 10; i < 20; i++)
  {
    pthread_create(&tid[i], NULL, ticketChecker, (void *)i);
  }

  for (int i = 0; i < 20; i++)
  {
    pthread_join(tid[i], NULL);
  }

  pthread_mutex_destroy(&mutex);

  return 0;
}