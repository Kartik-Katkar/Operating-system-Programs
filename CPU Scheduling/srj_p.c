#include <stdio.h>

int main() {
    int at[10], bt[10],
    rt[10], 
    remain = 0, 
    t, 
    smallest = -1;
    int completionTime, sum_wait = 0;

int n;
    printf("Enter no of Processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for Process P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("\n\nProcess\t| Turnaround Time | Waiting Time\n\n");

    for (t = 0; remain != n; t++) {
        smallest = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= t && rt[i] && (smallest == -1 || rt[i] < rt[smallest])) {
                smallest = i;
            }
        }

        if (smallest == -1) 
        { 
            continue;
        }

        rt[smallest]--;

        if (rt[smallest] == 0) {
            remain++;
            completionTime = t + 1;
            printf("P[%d]\t| %d\t\t | %d\n", smallest + 1, completionTime - at[smallest], completionTime - bt[smallest] - at[smallest]);
            sum_wait += completionTime - bt[smallest] - at[smallest];
        }
    }

    printf("\n\nAverage waiting time = %lf\n", sum_wait * 1.0 / n);
    
    return 0;
}
