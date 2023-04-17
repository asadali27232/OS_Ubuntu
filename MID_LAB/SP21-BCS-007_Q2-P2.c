#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("File name not passed");
    return 1;
  }

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
    close(pipefd[1]);

    execlp("cat", "cat", argv[1], NULL);
    printf("Failed to exec cat.\n");
    exit(1);
  }
  else
  {
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);

    execlp("grep", "grep", "Asad", NULL);
    printf("Failed to exec grep.\n");
    exit(1);
  }

  return 0;
}
