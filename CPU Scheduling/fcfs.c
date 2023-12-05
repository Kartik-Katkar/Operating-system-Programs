
#include <stdio.h>

int main() {
    int n;
    printf("Enter no of processes: ");
    scanf("%d", &n);

    int procid[n], 
    bt[n], 
    ar[n], 
    ct[n], 
    ta[n], 
    wt[n];

    for(int i = 0; i < n; i++) {
        printf("Enter process P%d arrival time: ", i+1);
        scanf("%d", &ar[i]);
        printf("Enter process P%d burst time: ", i+1);
        scanf("%d", &bt[i]);
        procid[i] = i + 1;
    }
// MAIN FCFS LOGIC 
    int temp;
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(ar[i] > ar[j]) {
                // swap arrival time
                temp = ar[i];
                ar[i] = ar[j];
                ar[j] = temp;

                // swap procid
                temp = procid[i];
                procid[i] = procid[j];
                procid[j] = temp;

                // swap bt
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
            }
        }
    }

    printf("\n");
    ct[0] = bt[0];

    for(int i = 1; i < n; i++) {
        // check this logic once
        
        ct[i] = ct[i - 1] + bt[i];
    }

    for(int i = 0; i < n; i++) {
        ta[i] = ct[i] - ar[i];
        wt[i] = ta[i] - bt[i];
    }

    printf("Process\t\tAT\t\tBT\t\tCT\t\tTAT\t\tWT\n");
    int avg_wt = 0, avg_ta = 0;

    for(int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_ta += ta[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", procid[i], ar[i], bt[i], ct[i], ta[i], wt[i]);
    }

    printf("\nAverage TAT: %.2f\n", (float)(avg_ta/n));
    printf("Average WT: %.2f\n", (float)(avg_wt/n));

    printf("\nGantt chart: ");
    for(int i = 0; i < n; i++) {
        printf("P%d|", procid[i]);
    }

    return 0;
}
