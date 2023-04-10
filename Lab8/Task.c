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

  char parentName[20] = {" Parent"};
  char childName[20] = {"Child"};
  char parentMessage[20] = {"Hello Nephew!"};
  char childMessage[20] = {"Hello Uncle!"};

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
      write(fds[1], childName, sizeof(childName));
      printf("Child has written to pipe!\n");
      read(fds2[0], childMessage, sizeof(childMessage));
      printf("Child has read from pipe!\n");
      printf("Final Output from Child: %s", childMessage);
    }
    else if (pid > 0)
    {
      // Parent process
      // Write on pipe line
      close(fds[1]);
      close(fds2[0]);
      read(fds[0], parentMessage, sizeof(parentMessage));
      printf("Parent has read from pipe!\n");
      char childFullName[100];
      strcat(childFullName, parentMessage);
      strcat(childFullName, parentName);
      write(fds2[1], childFullName, sizeof(childFullName));
      printf("Parent has written to pipe!\n");
    }
    else
    {
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}