// Demonstration of Threads

#include <stdio.h>
#include <pthread.h>

void *my_function(void *arg) // function must  be void pointer and take void pointer as argument
{
  printf("Thread created successfully\n");
  printf("Thrwad id is: %ld", pthread_self()); // returns the thread id of the calling thread
  return NULL;
}

int main()
{
  printf("Hello World\n");
  pthread_t thread_id;
  pthread_create(&thread_id, NULL, my_function, NULL); // id, attributes, function of thread, arguments of funtion
  pthread_join(thread_id, NULL);                       // Wait for all threads to complete

  return 0;
}