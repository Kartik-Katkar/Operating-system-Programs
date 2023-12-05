#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// gcc -o matrix_operations matrix_operations.c -lpthread


#define MATRIX_SIZE 3

typedef struct {
    int row;
    int col;
    int (*matrix_a)[MATRIX_SIZE];
    int (*matrix_b)[MATRIX_SIZE];
    int (*result)[MATRIX_SIZE];
} ThreadData;

void *calculateMatrixAddition(void *arg) {
    ThreadData *threadData = (ThreadData *)arg;
    threadData->result[threadData->row][threadData->col] =
        threadData->matrix_a[threadData->row][threadData->col] + threadData->matrix_b[threadData->row][threadData->col];
    pthread_exit(NULL);
}

void *calculateMatrixMultiplication(void *arg) {
    ThreadData *threadData = (ThreadData *)arg;
    int sum = 0;
    for (int k = 0; k < MATRIX_SIZE; ++k) {
        sum += threadData->matrix_a[threadData->row][k] * threadData->matrix_b[k][threadData->col];
    }
    threadData->result[threadData->row][threadData->col] = sum;
    pthread_exit(NULL);
}

int main() {
    int matrixA[MATRIX_SIZE][MATRIX_SIZE] = {
        {5, 2, 2},
        {4, 3, 4},
        {-1, 8, 8}
    };

    int matrixB[MATRIX_SIZE][MATRIX_SIZE] = {
        {5, 2, 5},
        {3, -3, 3},
        {2, -1, -1}
    };

    int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];

    pthread_t threads[MATRIX_SIZE][MATRIX_SIZE];
    ThreadData threadData[MATRIX_SIZE][MATRIX_SIZE];

    // Matrix Addition
    printf("Matrix Addition:\n");
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            threadData[i][j].row = i;
            threadData[i][j].col = j;
            threadData[i][j].matrix_a = matrixA;
            threadData[i][j].matrix_b = matrixB;
            threadData[i][j].result = resultMatrix;
            pthread_create(&threads[i][j], NULL, calculateMatrixAddition, &threadData[i][j]);
        }
    }

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            pthread_join(threads[i][j], NULL);
            printf("%d ", resultMatrix[i][j]);
        }
        printf("\n");
    }

    // Matrix Multiplication
    printf("\nMatrix Multiplication:\n");
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            threadData[i][j].row = i;
            threadData[i][j].col = j;
            threadData[i][j].matrix_a = matrixA;
            threadData[i][j].matrix_b = matrixB;
            threadData[i][j].result = resultMatrix;
            pthread_create(&threads[i][j], NULL, calculateMatrixMultiplication, &threadData[i][j]);
        }
    }

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            pthread_join(threads[i][j], NULL);
            printf("%d ", resultMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
