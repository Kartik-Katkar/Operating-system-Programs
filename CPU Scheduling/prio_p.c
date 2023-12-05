#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int main() {
    printf("Enter the number of processes: ");
    int n;
    scanf("%d", &n);

    int pid[n];
    int at[n];
    int bt[n];
    int ct[n];
    int ta[n];
    int wt[n];
    int f[n];
    int k[n];
    int pr[n];
    int i, st = 0, tot = 0;

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &pr[i]);
        k[i] = bt[i];
        f[i] = 0;
    }

    while (true) {
        int min = INT_MAX, c = -1;
        if (tot == n)
            break;

        for (i = 0; i < n; i++) {
            if (at[i] <= st && f[i] == 0 && pr[i] < min) {
                min = pr[i];
                c = i;
            }
        }

        if (c == -1)
            st++;
        else {
            bt[c]--;
            st++;
            if (bt[c] == 0) {
                ct[c] = st;
                f[c] = 1;
                tot++;
            }
        }
    }

    for (i = 0; i < n; i++) {
        ta[i] = ct[i] - at[i];
        wt[i] = ta[i] - k[i];

    }

    printf("\nPid|Arrival| Burst |Priority |  Complete | Turn|Waiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], k[i], pr[i], ct[i], ta[i], wt[i]);
    }
 
  return 0;
}
