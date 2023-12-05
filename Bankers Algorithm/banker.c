#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int work[MAX_RESOURCES];
int finish[MAX_PROCESSES];

int num_processes, num_resources;

void inputData() {
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter the available resources: ");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
        work[i] = available[i];
    }

    printf("Enter the maximum resource allocation for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("For process P%d: ", i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter the current resource allocation for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("For process P%d: ", i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
        finish[i] = 0;
    }
}

int isSafe() {
    
    int work_copy[MAX_RESOURCES];
 for (int i = 0; i < num_resources; i++) {
        work_copy[i] = work[i];
    }
    int sequence[MAX_PROCESSES];
    int count = 0;
    while (count < num_processes) {
        int found = 0;
        for (int i = 0; i < num_processes; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < num_resources; j++) {
                    if (need[i][j] > work_copy[j]) {
                        break;
                    }
                }
                 if (j == num_resources) {
                    for (int k = 0; k < num_resources; k++) {
                        work_copy[k] += allocation[i][k];
                    }
                    sequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is in an unsafe state.\n");
            return 0;
        }
    }

    printf("System is in a safe state. Safe sequence: ");
    for (int i = 0; i < num_processes; i++) {
        printf("P%d", sequence[i]);
        if (i < num_processes - 1) {
            printf(" -> ");
        }
    }
    printf("\n");

    return 1;
}

int main() {
    inputData();
    if (isSafe()) {
        printf("Resource allocation is safe.\n");
    } else {
        printf("Resource allocation is not safe.\n");
    }
    return 0;       
}
