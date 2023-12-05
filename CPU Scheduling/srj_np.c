#include <stdio.h>

int main() {
    int n;
    printf("Enter no of processes: ");
    scanf("%d", &n);

    int process_id[n],
    bt[n], 
    ar[n], 
    ct[n], 
    ta[n], 
    wt[n], 
    f[n];// check if it is already executed
    int st = 0, tot = 0; // system time and total number of process executed

    float avg_wt = 0, avg_ta = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter process %d arrival time: ", i + 1);
        scanf("%d", &ar[i]);
        printf("Enter process %d burst time: ", i + 1);
        scanf("%d", &bt[i]);
        process_id[i] = i + 1;
        f[i] = 0;
    }

    while (1) {
        int c = n, min = 999999; // track the index of process with min burst time

        if (tot == n)
            break;

        for (int i = 0; i < n; i++) {
            if ((ar[i] <= st) && (f[i] == 0) && (bt[i] < min)) {
                min = bt[i];
                c = i;
            }
        }

        if (c == n)
           { 
            st++;
           }

        else {
            // direct table banare he
            ct[c] = st + bt[c];
            st += bt[c];
            ta[c] = ct[c] - ar[c];
            wt[c] = ta[c] - bt[c];
            f[c] = 1;
            process_id[tot] = c + 1;
            tot++;
        }
    }

    printf("Process\t\tAT\t\tBT\t\tCT\t\tTAT\t\tWT\n");

    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_ta += ta[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, ar[i], bt[i], ct[i], ta[i], wt[i]);
    }

    printf("\nAverage TAT: %.2f\n", (float)(avg_ta / n));
    printf("Average WT: %.2f\n", (float)(avg_wt / n));

    printf("\nGantt chart: ");

    for (int i = 0; i < n; i++) {
        printf("P%d|", process_id[i]);
    }

    return 0;
}
  