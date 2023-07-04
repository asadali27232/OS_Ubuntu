// Pipe line message pass
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
    int fds[2];

    char message[20] = {"Hello World!"};
    char output[20];

    if (pipe(fds) == -1)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
    // Write on pipe line 
    write (fds[1], message, sizeof(message));

    // Read from pipe line
    read(fds[0], output, sizeof(output));

    printf("%s", output);
    exit(EXIT_SUCCESS);
    }

    return 0;
}