/*
Task 14. Parallelization of the initialization
Parallelize the initialization of the matrices also.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 2048

double a[SIZE][SIZE];
double b[SIZE][SIZE];
double c[SIZE][SIZE];

void* init_matrix_parallel(void* arg) {
    int row = *(int*)arg;
    for (int j = 0; j < SIZE; j++) {
        a[row][j] = 1.0;
        b[row][j] = 1.0;
    }
    return NULL;
}

void*
matmul_parallel(void* arg)
{
    int row = *(int*)arg;
    int j, k;

    for (j = 0; j < SIZE; j++) {
        c[row][j] = 0.0;
        for (k = 0; k < SIZE; k++)
            c[row][j] = c[row][j] + a[row][k] * b[k][j];
    }
    return NULL;
}

int main(int argc, char **argv) {
    pthread_t threads[SIZE];
    int ids[SIZE];

    for (int i = 0; i < SIZE; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL,
                       init_matrix_parallel, &ids[i]);
    }
    for (int i = 0; i < SIZE; i++)
        pthread_join(threads[i], NULL);

    for (int i = 0; i < SIZE; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL,
                       matmul_parallel, &ids[i]);
    }
    for (int i = 0; i < SIZE; i++)
        pthread_join(threads[i], NULL);

    printf("c[0][0] = %.2f (expected %.2f)\n", c[0][0], (double)SIZE);
    return 0;
}
