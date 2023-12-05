#include <stdio.h>

#define MAX_FRAMES 10

int main() {
    int frames;
    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    int n;
    printf("Enter the length of the reference string: ");
    scanf("%d", &n); 
    int referenceString[n];

    printf("Enter the reference string (space-separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &referenceString[i]);
    }

    int pageFaults = 1; 
    int frameQueue[MAX_FRAMES];
    int front = 0, rear = 0;

    printf("\nPage Reference\tPage Faults\n");

    for (int i = 0; i < n; i++) {
        int page = referenceString[i];
        int pageFound = 0;

        // Check if the page is already in frames
        for (int j = 0; j < frames; j++) {
            if (frameQueue[j] == page) {
                pageFound = 1;
                break;
            }
        }
        if (!pageFound) {
    // Page Fault
    pageFaults++;
    if (rear - front == frames) {
        front = (front + 1) % frames;
    }
    frameQueue[rear] = page;
    rear = (rear + 1) % frames;
}
    printf("%d\t\t%d\n", page, pageFaults);

    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}
