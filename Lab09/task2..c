// Write a program in c that forms a calculator with basic function (+, -, *, /, %) using switch statement. Each function should be performed by a different thread. Take two golble operators.

#include <stdio.h>
#include <pthread.h>

int *a, *b;

void *add(void *arg)
{
  printf("Thread created successfully\n");
  printf("Thread id is: %ld\n", pthread_self()); // returns the thread id of the calling thread
  printf("Sum is: %d\n", a + b);
  return NULL;
}
void *sub(void *arg)
{
  printf("Thread created successfully\n");
  printf("Thread id is: %ld\n", pthread_self()); // returns the thread id of the calling thread
  printf("Difference is: %d\n", a - b);
  return NULL;
}

void *div(void *arg)
{
  printf("Thread created successfully\n");
  printf("Thread id is: %ld\n", pthread_self()); // returns the thread id of the calling thread
  printf("Div is: %d\n", a / b);
  return NULL;
}

void *mul(void *arg)
{
  printf("Thread created successfully\n");
  printf("Thread id is: %ld\n", pthread_self()); // returns the thread id of the calling thread
  printf("Mul is: %d\n", a * b);
  return NULL;
}

int main()
{
  printf("Hello World\n");
  pthread_t thread_id[4];

  int *user_input;
  printf("Enter two numbers: ");
  scanf("%d %d", &a, &b);
  printf("Enter 1 for addition, 2 for subtraction, 3 for division, 4 for multiplication: ");
  scanf("%d", &user_input);

  switch (user_input)
  {
  case 1:
    pthread_create(&thread_id[0], NULL, add, NULL); // id, attributes, function of thread, arguments of funtion
    break;
  case 2:
    pthread_create(&thread_id[1], NULL, sub, NULL); // id, attributes, function of thread, arguments of funtion
    break;
  case 3:
    pthread_create(&thread_id[2], NULL, div, NULL); // id, attributes, function of thread, arguments of funtion
    break;
  case 4:
    pthread_create(&thread_id[3], NULL, mul, NULL); // id, attributes, function of thread, arguments of funtion
  default:
    printf("Invalid input");
    break;
  }

  for (int i = 0; i < 4; i++)
  {
    pthread_join(thread_id[i], NULL); // Wait for all threads to complete
  }

  return 0;
}