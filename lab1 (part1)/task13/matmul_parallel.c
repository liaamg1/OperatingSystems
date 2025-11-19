/*
Task 13. Parallel matrix multiplication
We will now parallelize the matrix multiplication program using threads. Parallelize the program according to the following
assumptions:
• Parallelize only the matrix multiplication, but not the initialization.
• A new thread shall be created for each row to be calculated in the matrix.
• The row number of the row that a thread shall calculate, shall be passed to the new thread as a parameter to the new
thread.
• The main function shall wait until all threads have terminated before the program terminates.
Compile and link your parallel version of the matrix multiplication program. Don’t forget to add -lpthread when you
link your program. We will now measure how much faster the parallel program is as compared to the sequential one.
Execute the program and measure the execution time.
How long was the execution time of your parallel program?
Which speedup did you get (as compared to the execution time of the sequential version,
where Speedup = Tsequential/Tparallel)?
*/
/***************************************************************************
 *
 * Sequential version of Matrix-Matrix multiplication
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 1024

static double a[SIZE][SIZE];
static double b[SIZE][SIZE];
static double c[SIZE][SIZE];

static void
init_matrix(void)
{
    int i, j;

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++) {
	        /* Simple initialization, which enables us to easy check
	         * the correct answer. Each element in c will have the same
	         * value as SIZE after the matmul operation.
	         */
	        a[i][j] = 1.0;
	        b[i][j] = 1.0;
        }
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

static void
print_matrix(void)
{
    int i, j;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++)
	        printf(" %7.2f", c[i][j]);
	    printf("\n");
    }
}

int
main(int argc, char **argv)
{
    
    pthread_t threads[SIZE];
    int rows_id[SIZE];
    
    init_matrix();
    
    for(int i=0; i<SIZE; ++i){
        rows_id[i]=i;
        pthread_create(&threads[i],NULL,matmul_parallel,&rows_id[i]);
    }

    for(int i =0; i<SIZE; ++i){
        pthread_join(threads[i],NULL);
    }
    printf("%.2f (expected %.2f)\n", c[0][0], (double)SIZE);
    //print_matrix()
}
