/*
Task 14. Parallelization of the initialization
Parallelize the initialization of the matrices also, i.e., the function init_matrix. Use one thread to initialize each of the
rows in the matrices a and b. Compile, link, and execute your program.
Which is the execution time and speedup for the application now?
Did the program run faster or slower now, and why?
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 1024

double a[SIZE][SIZE];
double b[SIZE][SIZE];
double c[SIZE][SIZE];

static void* init_matrix_parallel(void *arg) {
    int i = *(int*)arg;
    for (int j = 0; j < SIZE; j++){
        a[i][j] = 1;
        b[i][j] = 1;
    }

    return NULL;
}

static void matmul_seq()
{
    int i, j, k;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            c[i][j] = 0.0;
            for (k = 0; k < SIZE; k++)
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
        }
    }
}

int main() {
    pthread_t threads[SIZE];
    int ids[SIZE];

    for (int i = 0; i < SIZE; i++){
        ids[i] = i;
        pthread_create(&threads[i],
            NULL,
            init_matrix_parallel, 
            &ids[i]);
    }

    for (int i = 0; i < SIZE; i++)
    {
        pthread_join(threads[i], NULL);
    }

    matmul_seq();

    return 0;
}
