#include "main_calc.h"
int main(int argc, char *argv[]) {
    int i, j, k;
    int **A = (int **)malloc(N * sizeof(int *));
    int **B = (int **)malloc(N * sizeof(int *));
    int **C = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
    }
    omp_set_dynamic(0);  // запретить библиотеке openmp менять число потоков
                         // во
                         //  время исполнения
    omp_set_num_threads(10);  // установить число потоков в 10

    srand(time(NULL));
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    time_t t0 = time(0);
#pragma omp parallel for shared(A, B, C) private(i, j, k)
    for (i = 0; i < N; i++)  //#pragma omp parallel for private(j)
        for (j = 0; j < N; j++) {
            C[i][j] = 0;
            for (k = 0; k < N; k++) C[i][j] += A[i][k] * B[k][j];
        }
    time_t t1 = time(0);
    double time_in_seconds = difftime(t1, t0);
    printf("time is %f \n", time_in_seconds);
    for (i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
}