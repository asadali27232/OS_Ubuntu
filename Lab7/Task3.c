// Pipe line message pass
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fds[2];
    char message[100];

    if (pipe(fds) == -1)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            printf("Enter message: ");
            scanf("%s", message);
            write(fds[1], message, sizeof(message));
        }

        char output[100];
        char temp[100];

        // Read from pipe lines
        for (int i = 0; i < 3; i++)
        {
            read(fds[0], temp, sizeof(temp));
            strcat(output, temp);
        }

        printf(" %s \n", output);
        exit(EXIT_SUCCESS);
    }

    return 0;
}