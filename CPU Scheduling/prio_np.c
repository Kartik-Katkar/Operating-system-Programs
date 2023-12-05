#include <stdio.h>
#include <stdlib.h>

struct process
{
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int finish_time;
    int turn_around_time;
    int priority;
};

int main()
{
    int n, i, j;
    int bt = 0, k = 1,min, mini;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process proc[n], temp;

    printf("Enter data (AT BT Pr):\n");
    for (i = 0; i < n; i++)
    {
        proc[i].process_id = i + 1;
        scanf("%d %d %d", &proc[i].arrival_time, &proc[i].burst_time, &proc[i].priority);
    }

//Ye bhi fcfs hee 
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (proc[i].arrival_time < proc[j].arrival_time)
            {
                temp = proc[j];
                proc[j] = proc[i];
                proc[i] = temp;
            }
        }
    }


    for (i = 0; i < n; i++)
    {
        bt += proc[i].burst_time;
        min = proc[k].burst_time;
        mini = proc[k].priority;

        for (j = k; j < n; j++)
        {
            if (bt >= proc[j].arrival_time && proc[j].priority < mini)
            {
                temp = proc[k];
                proc[k] = proc[j];
                proc[j] = temp;
            }  
        }
        k++;
    } 
      
    // SAME AS FCFS 
    proc[0].finish_time = proc[0].burst_time;

    for (i = 1; i < n; i++)
    {
        proc[i].finish_time = proc[i - 1].finish_time + proc[i].burst_time;
    }

    for (i = 0; i < n; i++)
    {
        proc[i].turn_around_time = proc[i].finish_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turn_around_time - proc[i].burst_time;
    }

    printf("Process\tArrival Time\tBurst Time\tFinish Time\tTurn-Around Time\tWaiting Time\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].process_id, proc[i].arrival_time,
               proc[i].burst_time, proc[i].finish_time, proc[i].turn_around_time, proc[i].waiting_time);
    }

    return 0;
}
