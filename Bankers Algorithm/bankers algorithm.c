#include<stdio.h>

void main() {
    int max[10][10], alloc[10][10], need[10][10], avail[10], np, nr;

    printf("Enter the number of processes: ");
    scanf("%d", &np);

    printf("Enter the number of resources: ");
    scanf("%d", &nr);

    printf("Enter the allocation matrix:\n");
    for(int i=0; i<np; i++)
        for(int j=0; j<nr; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter the max matrix:\n");
    for(int i=0; i<np; i++)
        for(int j=0; j<nr; j++)
            scanf("%d", &max[i][j]);

    printf("Enter the available resources:\n");
    for(int i=0; i<nr; i++)
        scanf("%d", &avail[i]);

    for(int i=0; i<np; i++)
        for(int j=0; j<nr; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int finish[10], safeSeq[10];
    for(int i=0; i<np; i++)
        finish[i] = 0;
    
    int work[10];
    for(int i=0; i<nr; i++)
        work[i] = avail[i];

    int count=0;
    while(count < np) {
        int found = 0;
        for(int p=0; p<np; p++) {
            if(finish[p] == 0) {
                int j;
                for(j=0; j<nr; j++) {
                    if(need[p][j] > work[j])
                        break;
                }
                if(j == nr) {
                    for(int k=0 ; k<nr ; k++)
                        work[k] += alloc[p][k];
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
        if(found == 0) {
            printf("System is not in safe state due to process: %d\n", count);
            return;
        }
    }

    printf("System is in safe state.\nSafe sequence is: ");
    for(int i=0; i<np; i++)
        printf("%d ",safeSeq[i]);
}
