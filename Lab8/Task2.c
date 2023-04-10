// Parent Child Communication using Pipe
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
  int fds[2];
  int fds2[2];

  int numbers[5] = {1, 2, 3, 4, 5};
  int sum[1];

  if (pipe(fds) == -1 || pipe(fds2) == -1)
  {
    exit(EXIT_FAILURE);
  }
  else
  {
    pid_t pid = fork();

    if (pid == 0)
    {
      // Child process
      // Read from pipe line
      close(fds[0]);
      close(fds2[1]);

      write(fds[1], numbers, sizeof(numbers));
      read(fds2[0], sum, sizeof(sum));

      printf("Final Sum from Child: %d", sum[0]);
    }
    else if (pid > 0)
    {
      // Parent process
      // Write on pipe line
      close(fds[1]);
      close(fds2[0]);

      int tempNumbers[5];
      read(fds[0], tempNumbers, sizeof(tempNumbers));

      int tempSum[1];
      for (int i = 0; i < 5; i++)
      {
        tempSum[0] += tempNumbers[i];
      }

      write(fds2[1], tempSum, sizeof(tempSum));
    }
    else
    {
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}