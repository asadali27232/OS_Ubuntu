// Create a multithreaded program to sum the to matrix 4 by 4 each thread will add each row of the matrix and store the result in the new matrix.
#include <stdio.h>
#include <pthread.h>

int rows = 4;
int columns = 4;

int A[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
int B[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
int C[4][4];

void *add(void *arg)
{
    int row = (int)arg;

    for (int i = 0; i < columns; i++)
    {
        C[row][i] = A[row][i] + B[row][i];
    }
    return NULL;
}

int main()
{
    for (int i = 0; i < rows; i++)
    {
        pthread_t tid[i];
        pthread_create(&tid[i], NULL, add, (void *)i);
        pthread_join(tid[i], NULL);
    }
    return 0;
}