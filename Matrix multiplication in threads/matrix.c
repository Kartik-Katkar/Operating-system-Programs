#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 10

int matrixA[MAX_SIZE][MAX_SIZE], matrixB[MAX_SIZE][MAX_SIZE], result[MAX_SIZE][MAX_SIZE];
int numRows, numCols, numThreads;

void readMatrices() {
    printf("Enter the number of rows: ");
    scanf("%d", &numRows);
    printf("Enter the number of columns: ");
    scanf("%d", &numCols);

    printf("Enter elements for Matrix A:\n");
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            scanf("%d", &matrixA[i][j]);
        }
    }

    printf("Enter elements for Matrix B:\n");
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            scanf("%d", &matrixB[i][j]);
        }
    }
}

void printMatrix(int matrix[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}

void* matrixMultiply(void* arg) {
    long threadId = (long)arg;
    int startRow = (threadId * numRows) / numThreads;
    int endRow = ((threadId + 1) * numRows) / numThreads;

    for (int i = startRow; i < endRow; i++) {
        for (int j = 0; j < numCols; j++) {
            result[i][j] = 0;
            for (int k = 0; k < numCols; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    return NULL;
}

int main() {
    readMatrices();

    printf("Enter the number of threads to use: ");
    scanf("%d", &numThreads);

    pthread_t threads[numThreads];

    for (long i = 0; i < numThreads; i++) {
        pthread_create(&threads[i], NULL, matrixMultiply, (void*)i);
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nResultant Matrix:\n");
    printMatrix(result);

    return 0;
}