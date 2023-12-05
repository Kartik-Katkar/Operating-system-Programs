#include <stdio.h>
#include <stdlib.h>

#define max 199
#define min 0

void cScan(int arr[], int head, int n) {
    int seek = 0;

    // Sort the array
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // Find the index of the head
    int index;
    for (int i = 0; i < n; i++) {
        if (arr[i] == head) {
            index = i;
            break;
        }
    }

    // C-Scan
    for (int i = index; i < n; i++) {
        printf("\nHead moved from %d to %d", arr[i], arr[i + 1]);
        seek += abs(arr[i] - arr[i + 1]);
    }
    
    printf("\nHead moved from %d to %d", arr[n - 1], max);
    seek += abs(arr[n - 1] - max);
    
    printf("\nHead moved from %d to %d", max, min);
    seek += abs(max - min);
    
    printf("\nHead moved from %d to %d", min, arr[0]);
    seek += abs(min - arr[0]);

    printf("\nC-Scan Seek time = %d", seek);
}

int main() {
    int arr[25];
    int n;

    printf("Enter no. of requests: ");
    scanf("%d", &n);

    printf("\nEnter requests: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int head;
    printf("\nEnter head: ");
    scanf("%d", &head);

    arr[n] = head;
    cScan(arr, head, n + 1);

    return 0;
}
