#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int finish_time;
    int turnaround_time;
    int waiting_time;
};

struct Queue {
    int front, rear, size;
    unsigned capacity;
    struct Process** array;
};

struct Queue* create_queue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (struct Process**)malloc(capacity * sizeof(struct Process*));
    return queue;
}

void enqueue(struct Queue* queue, struct Process* process) {
    if (queue->size == queue->capacity) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = process;
    queue->size++;
}

struct Process* dequeue(struct Queue* queue) {
    if (queue->size == 0) {
        printf("Queue is empty. Cannot dequeue.\n");
        return NULL;
    }
    struct Process* process = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return process;
}

struct MinHeap {
    struct Process* array;
    int size;
};

void display_results(const char* scheduler_name, struct Process processes[], int n) {
    printf("Results of %s Scheduling:\n", scheduler_name);
    printf("----------------------------------------------------------------------------------------------\n");
    printf("Process | Arrival Time | Burst Time | Priority | Finish Time | Turnaround Time | Waiting Time\n");
    printf("----------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%7d | %12d | %10d | %7d | %11d | %15d | %12d\n",
            processes[i].id, processes[i].arrival_time,
            processes[i].burst_time, processes[i].priority,
            processes[i].finish_time, processes[i].turnaround_time,
            processes[i].waiting_time);
    }
    printf("----------------------------------------------------------------------------------------------\n\n");
}

struct Process create_process(int id, int arrival_time, int burst_time, int priority) {
    struct Process process;
    process.id = id;
    process.arrival_time = arrival_time;
    process.burst_time = burst_time;
    process.priority = priority;
    process.remaining_time = burst_time;
    return process;
}

struct MinHeap* create_min_heap(int capacity) {
    struct MinHeap* min_heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    min_heap->size = 0;
    min_heap->array = (struct Process*)malloc(capacity * sizeof(struct Process));
    return min_heap;
}

void swap(struct Process* a, struct Process* b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(struct MinHeap* min_heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < min_heap->size && min_heap->array[left].priority < min_heap->array[smallest].priority) {
        smallest = left;
    }

    if (right < min_heap->size && min_heap->array[right].priority < min_heap->array[smallest].priority) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&min_heap->array[index], &min_heap->array[smallest]);
        min_heapify(min_heap, smallest);
    }
}

void insert_min_heap(struct MinHeap* min_heap, struct Process process) {
    ++min_heap->size;
    int i = min_heap->size - 1;
    min_heap->array[i] = process;

    while (i != 0 && min_heap->array[(i - 1) / 2].priority > min_heap->array[i].priority) {
        swap(&min_heap->array[i], &min_heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

struct Process extract_min(struct MinHeap* min_heap) {
    struct Process min = min_heap->array[0];
    min_heap->array[0] = min_heap->array[min_heap->size - 1];
    --min_heap->size;
    min_heapify(min_heap, 0);
    return min;
}

void run_FCFS(struct Process processes[], int n) {
    int total_time = 0;

    for (int i = 0; i < n; i++) {
        if (total_time < processes[i].arrival_time) {
            total_time = processes[i].arrival_time;
        }
        processes[i].finish_time = total_time + processes[i].burst_time;
        total_time = processes[i].finish_time;
    }

    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].finish_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }

    display_results("First Come First Serve (FCFS)", processes, n);
}

void run_SJF_NonPreemptive(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    int total_time = 0;

    for (int i = 0; i < n; i++) {
        if (total_time < processes[i].arrival_time) {
            total_time = processes[i].arrival_time;
        }
        processes[i].finish_time = total_time + processes[i].burst_time;
        total_time = processes[i].finish_time;
    }

    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].finish_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }

    display_results("Shortest Job First (SJF - Non-Preemptive)", processes, n);
}

void run_SJF_Preemptive(struct Process processes[], int n) {
    struct MinHeap* min_heap = create_min_heap(n);
    int total_time = 0;
    int completed_processes = 0;
    int current_index = 0;

    while (completed_processes < n) {
        while (current_index < n && processes[current_index].arrival_time <= total_time) {
            insert_min_heap(min_heap, processes[current_index]);
            current_index++;
        }

        if (min_heap->size == 0) {
            total_time++;
        } else {
            struct Process shortest_job = extract_min(min_heap);
            shortest_job.remaining_time--;

            total_time++;

            if (shortest_job.remaining_time == 0) {
                completed_processes++;
                shortest_job.finish_time = total_time;
                shortest_job.turnaround_time = shortest_job.finish_time - shortest_job.arrival_time;
                shortest_job.waiting_time = shortest_job.turnaround_time - shortest_job.burst_time;
            } else {
                insert_min_heap(min_heap, shortest_job);
            }
        }
    }

    display_results("Shortest Job First (SJF - Preemptive)", processes, n);

    free(min_heap->array);
    free(min_heap);
}

void run_Priority_NonPreemptive(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    int total_time = 0;

    for (int i = 0; i < n; i++) {
        if (total_time < processes[i].arrival_time) {
            total_time = processes[i].arrival_time;
        }
        processes[i].finish_time = total_time + processes[i].burst_time;
        total_time = processes[i].finish_time;
    }

    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].finish_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }

    display_results("Priority Scheduling (Non-Preemptive)", processes, n);
}

void run_Priority_Preemptive(struct Process processes[], int n) {
    struct MinHeap* min_heap = create_min_heap(n);
    int total_time = 0;
    int completed_processes = 0;
    int current_index = 0;

    while (completed_processes < n) {
        while (current_index < n && processes[current_index].arrival_time <= total_time) {
            insert_min_heap(min_heap, processes[current_index]);
            current_index++;
        }

        if (min_heap->size == 0) {
            total_time++;
        } else {
            struct Process highest_priority = extract_min(min_heap);
            highest_priority.remaining_time--;

            total_time++;

            if (highest_priority.remaining_time == 0) {
                completed_processes++;
                highest_priority.finish_time = total_time;
                highest_priority.turnaround_time = highest_priority.finish_time - highest_priority.arrival_time;
                highest_priority.waiting_time = highest_priority.turnaround_time - highest_priority.burst_time;
            } else {
                insert_min_heap(min_heap, highest_priority);
            }
        }
    }

    display_results("Priority Scheduling (Preemptive)", processes, n);

    free(min_heap->array);
    free(min_heap);
}

void run_RoundRobin(struct Process processes[], int n, int time_quantum) {
    int total_time = 0;
    int completed_processes = 0;
    int current_index = 0;

    struct Queue* queue = create_queue(n);

    while (completed_processes < n) {
        while (current_index < n && processes[current_index].arrival_time <= total_time) {
            enqueue(queue, &processes[current_index]);
            current_index++;
        }

        if (queue->size == 0) {
            total_time++;
        } else {
            struct Process* current_process = dequeue(queue);

            if (current_process->remaining_time <= time_quantum) {
                total_time += current_process->remaining_time;
                current_process->finish_time = total_time;
                current_process->remaining_time = 0;
                completed_processes++;
                current_process->turnaround_time = current_process->finish_time - current_process->arrival_time;
                current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;
            } else {
                total_time += time_quantum;
                current_process->remaining_time -= time_quantum;
                enqueue(queue, current_process);
            }
        }
    }

    display_results("Round Robin Scheduling", processes, n);

    free(queue->array);
    free(queue);
}

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        int arrival_time, burst_time, priority;
        scanf("%d %d %d", &arrival_time, &burst_time, &priority);
        processes[i] = create_process(i + 1, arrival_time, burst_time, priority);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    run_FCFS(processes, n);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    run_SJF_NonPreemptive(processes, n);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    run_SJF_Preemptive(processes, n);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    run_Priority_NonPreemptive(processes, n);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    run_Priority_Preemptive(processes, n);

    printf("Enter the time quantum for Round Robin: ");
    scanf("%d", &time_quantum);

    run_RoundRobin(processes, n, time_quantum);

    return 0;
}
