#include<stdio.h>
#include<stdlib.h>

void fcfs(int arr[], int head, int size) {
    int seek_time = 0;
    int curr_track;
    for(int i = 0; i < size; i++) {
        curr_track = arr[i];
        seek_time += abs(curr_track - head);
        head = curr_track;
    }
    printf("Total Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %f\n", (float)seek_time/size);
}

void scan(int arr[], int head, int size, int max_track) {
    int seek_time = 0;
    int curr_track;
    int direction = 1; // 1 for right, -1 for left
    int index = 0;
    int temp[size+1];
    for(int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }
    temp[size] = head;
    size++;
    for(int i = 0; i < size; i++) {
        for(int j = i+1; j < size; j++) {
            if(temp[i] > temp[j]) {
                int temp_var = temp[i];
                temp[i] = temp[j];
                temp[j] = temp_var;
            }
        }
    }
    for(int i = 0; i < size; i++) {
        if(temp[i] == head) {
            index = i;
            break;
        }
    }
    if(direction == 1) {
        for(int i = index; i < size; i++) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
        seek_time += abs(max_track - head);
        head = max_track;
        for(int i = index-1; i >= 0; i--) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
    }
    else {
        for(int i = index; i >= 0; i--) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
        seek_time += abs(0 - head);
        head = 0;
        for(int i = index+1; i < size; i++) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
    }
    printf("Total Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %f\n", (float)seek_time/size);
}

void c_scan(int arr[], int head, int size, int max_track) {
    int seek_time = 0;
    int curr_track;
    int direction = 1; // 1 for right, -1 for left
    int index = 0;
    int temp[size+2];
    for(int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }
    temp[size] = 0;
    temp[size+1] = max_track;
    size += 2;
    for(int i = 0; i < size; i++) {
        for(int j = i+1; j < size; j++) {
            if(temp[i] > temp[j]) {
                int temp_var = temp[i];
                temp[i] = temp[j];
                temp[j] = temp_var;
            }
        }
    }
    for(int i = 0; i < size; i++) {
        if(temp[i] == head) {
            index = i;
            break;
        }
    }
    if(direction == 1) {
        for(int i = index; i < size; i++) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
        seek_time += abs(max_track - head);
        head = max_track;
        for(int i = 0; i < index; i++) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
    }
    else {
        for(int i = index; i >= 0; i--) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
        seek_time += abs(0 - head);
        head = 0;
        for(int i = size-1; i > index; i--) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
    }
    printf("Total Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %f\n", (float)seek_time/size);
}

void sstf(int arr[], int head, int size) {
    int seek_time = 0;
    int curr_track;
    int temp[size];
    for(int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }
    for(int i = 0; i < size; i++) {
        int min_index = i;
        for(int j = i+1; j < size; j++) {
            if(abs(temp[j] - head) < abs(temp[min_index] - head)) {
                min_index = j;
            }
        }
        curr_track = temp[min_index];
        seek_time += abs(curr_track - head);
        head = curr_track;
        temp[min_index] = temp[i];
        temp[i] = curr_track;
    }
    printf("Total Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %f\n", (float)seek_time/size);
}

void look(int arr[], int head, int size, int max_track) {
    int seek_time = 0;
    int curr_track;
    int direction = 1; // 1 for right, -1 for left
    int index = 0;
    int temp[size];
    for(int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }
    for(int i = 0; i < size; i++) {
        for(int j = i+1; j < size; j++) {
            if(temp[i] > temp[j]) {
                int temp_var = temp[i];
                temp[i] = temp[j];
                temp[j] = temp_var;
            }
        }
    }
    for(int i = 0; i < size; i++) {
        if(temp[i] == head) {
            index = i;
            break;
        }
    }
    if(direction == 1) {
        for(int i = index; i < size; i++) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
        for(int i = size-2; i >= index; i--) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
    }
    else {
        for(int i = index; i >= 0; i--) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
        for(int i = 1; i <= index; i++) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
    }
    printf("Total Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %f\n", (float)seek_time/size);
}

void c_look(int arr[], int head, int size, int max_track) {
    int seek_time = 0;
    int curr_track;
    int direction = 1; // 1 for right, -1 for left
    int index = 0;
    int temp[size+1];
    for(int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }
    temp[size] = head;
    size++;
    for(int i = 0; i < size; i++) {
        for(int j = i+1; j < size; j++) {
            if(temp[i] > temp[j]) {
                int temp_var = temp[i];
                temp[i] = temp[j];
                temp[j] = temp_var;
            }
        }
    }
    for(int i = 0; i < size; i++) {
        if(temp[i] == head) {
            index = i;
            break;
        }
    }
    if(direction == 1) {
        for(int i = index; i < size; i++) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
        for(int i = 0; i < index-1; i++) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
    }
    else {
        for(int i = index; i >= 0; i--) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
        for(int i = size-2; i >= index; i--) {
            curr_track = temp[i];
            seek_time += abs(curr_track - head);
            head = curr_track;
        }
    }
    printf("Total Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %f\n", (float)seek_time/size);
}

int main() {
    int size, head, max_track;
    printf("Enter the number of requests: ");
    scanf("%d", &size);
    int arr[size];
    printf("Enter the requests: ");
    for(int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the maximum track number: ");
    scanf("%d", &max_track);
    printf("\nFCFS:\n");
    fcfs(arr, head, size);
    printf("\nSCAN:\n");
    scan(arr, head, size, max_track);
    printf("\nC-SCAN:\n");
    c_scan(arr, head, size, max_track);
    printf("\nSSTF:\n");
    sstf(arr, head, size);
    printf("\nLOOK:\n");
    look(arr, head, size, max_track);
    printf("\nC-LOOK:\n");
    c_look(arr, head, size, max_track);
    return 0;
}
