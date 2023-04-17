#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
  int fd;

  fd = creat("output.txt", 0644);
  if (fd == -1)
  {
    printf("Failed to create file.\n");
    return 1;
  }

  dup2(fd, STDOUT_FILENO);
  close(fd);

  // Write to file using printf()
  printf("Asad for search using grep\n");

  // Write command line arguments to file using printf()
  for (int i = 0; i < argc; i++)
  {
    printf("%s\n", argv[i]);
  }

  // Redirect to a process consisting file name as argument
  execlp("grep", "grep", "Asad", "output.txt", NULL);
  
  return 0;
}
