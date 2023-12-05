#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

void Sort(int *at, int *bt, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (at[i] > at[j])
            {
                int temp = at[i];
                at[i] = at[j];
                at[j] = temp;
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
            }
        }
    }
}

int main() {
    printf("Enter the number of processes: ");
    int n;
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    int tqu;
    scanf("%d", &tqu);

    int pid[n];
    int at[n];
    int bt[n];
    int ct[n];
    int ta[n];
    int wt[n];
    int f[n];
    int k[n];
    int rq[500];
    int i, st = 0, tot = 0, tq=tqu, fp=0, lp=0;
    int flag = 0;

    for(i =0; i<500; i++) {
        rq[i] = -1;
    }

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
        k[i] = bt[i];
        f[i] = 0;
    }

    while (true) {
        int c = -1;
        if (tot == n)
            break;

        if (flag == 0) {
            for (i = 0; i < n; i++) {
                if (at[i] == st && f[i] == 0) {
                    rq[lp] = i;
                    lp++;
                }
            }
        }
        else {
            flag = 0;
        }

        c = rq[fp];

        if (c == -1)
            st++;
        else {
            if(tq != 0 && bt[c] != 0) { //tq=2 bt=1
                tq--;
                bt[c]--;
                st++;
            }
            else if (tq == 0 && bt[c] != 0) {
                rq[lp] = c;
                lp++;
                fp++;
                tq = tqu;
                flag = 1;
            }
            if (bt[c] == 0) {
                ct[c] = st;
                f[c] = 1;
                fp++;
                tot++;
                tq = tqu;
            }
        }
    }

    for (i = 0; i < n; i++) {
        ta[i] = ct[i] - at[i];
        wt[i] = ta[i] - k[i];

    }

    printf("\nPid|Arrival| Burst |Complete | Turn|Waiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], k[i], ct[i], ta[i], wt[i]);
    }
 
  return 0;
}
