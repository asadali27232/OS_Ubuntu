#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
  // create pipe
  int pipefd[2];
  if (pipe(pipefd) == -1)
  {
    printf("Failed to create pipe.\n");
    return 1;
  }

  // fork process
  pid_t pid = fork();
  if (pid == -1)
  {
    printf("Failed to fork process.\n");
    return 1;
  }

  if (pid == 0)
  {
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);

    execlp("cat", "cat", "input.txt", NULL);
    close(pipefd[1]);

    printf("Failed to exec cat.\n");
    exit(1);
  }
  else
  {
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);

    execlp("sort", "sort", "-u", NULL);
    close(pipefd[0]);

    printf("Failed to exec sort.\n");
    exit(1);
  }

  return 0;
}
