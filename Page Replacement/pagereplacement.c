#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10

int stack[MAX_FRAMES];
int top = -1;

int isPageInFrame(int page, int frames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page) {
            return 1; // Page found
        }
    }
    return 0; // Page not found
}

void displayStack() {
    if (top == -1) {
        printf("Stack is empty.\n");
    } else {
        printf("Stack Contents: ");
        for (int i = 0; i <= top; i++) {
            printf("%d ", stack[i]);
        }
        printf("\n");
    }
}

// FIFO Page Replacement Algorithm
int fifo(int referenceString[], int numPages, int numFrames) {
    int pageFaults = 0;
    int frameIndex = 0;

    for (int i = 0; i < numPages; i++) {
        int page = referenceString[i];
        if (!isPageInFrame(page, stack, numFrames)) {
            pageFaults++;
            if (top < numFrames - 1) {
                // Frame is not full, push the page in stack
                top++;
                stack[top] = page;
            } else {
                // Frame is full, replace the oldest page (FIFO)
                stack[frameIndex] = page;
                frameIndex = (frameIndex + 1) % numFrames;
            }
        }
        displayStack();
    }
    return pageFaults;
}

// LRU Page Replacement Algorithm
int lru(int referenceString[], int numPages, int numFrames) {
    int pageFaults = 0;

    for (int i = 0; i < numPages; i++) {
        int page = referenceString[i];
        if (!isPageInFrame(page, stack, numFrames)) {
            pageFaults++;
            if (top < numFrames - 1) {
                // Frame is not full, push the page onto the stack
                top++;
                stack[top] = page;
            } else {
                // Frame is full, find (LRU) page and replace it
                int lruIndex = -1;
                int minTime = numPages;
                for (int j = 0; j < numFrames; j++) {
                    int currentPage = stack[j];
                    for (int k = i - 1; k >= 0; k--) {
                        if (referenceString[k] == currentPage) {
                            if (k < minTime) {
                                minTime = k;
                                lruIndex = j;
                            }
                            break;
                        }
                    }
                }
                stack[lruIndex] = page;
            }
        }
        displayStack();
    }

    return pageFaults;
}

// Optimal Page Replacement Algorithm
int optimal(int referenceString[], int numPages, int numFrames) {
    int pageFaults = 0;
    
    // Initialize stack with -1 for empty frames
    for (int i = 0; i < numFrames; i++) {
        stack[i] = -1;
    }

    for (int i = 0; i < numPages; i++) {
        int page = referenceString[i];
        if (!isPageInFrame(page, stack, numFrames)) {
            pageFaults++;
            if (top < numFrames - 1) {
                // Frame is not full, push the page onto the stack
                top++;
                stack[top] = page;
            } else {
                // Frame is full, find the page that will not be used for the longest time (Optimal)
                int optimalIndex = -1;
                int maxDistance = -1;
                for (int j = 0; j < numFrames; j++) {
                    int currentPage = stack[j];
                    int distance = 0;
                    for (int k = i + 1; k < numPages; k++) {
                        distance++;
                        if (referenceString[k] == currentPage) {
                            break;
                        }
                    }
                    if (distance > maxDistance) {
                        maxDistance = distance;
                        optimalIndex = j;
                    }
                }
                stack[optimalIndex] = page;
            }
        }
        displayStack();
    }

    return pageFaults;
}


int main() {
    int referenceString[] = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5};
    int numPages = sizeof(referenceString) / sizeof(referenceString[0]);
    int numFrames = 3;

    printf("Reference String: ");
    for (int i = 0; i < numPages; i++) {
        printf("%d ", referenceString[i]);
    }
    printf("\n\n");

    printf("FIFO Page Replacement Algorithm:\n");
    int fifoPageFaults = fifo(referenceString, numPages, numFrames);
    printf("\nTotal Page Faults (FIFO): %d\n\n", fifoPageFaults);

    top = -1; // Reset stack

    printf("LRU Page Replacement Algorithm:\n");
    int lruPageFaults = lru(referenceString, numPages, numFrames);
    printf("\nTotal Page Faults (LRU): %d\n\n", lruPageFaults);

    top = -1; 

    printf("Optimal Page Replacement Algorithm:\n");
    int optimalPageFaults = optimal(referenceString, numPages, numFrames);
    printf("\nTotal Page Faults (Optimal): %d\n\n", optimalPageFaults);

    return 0;
}
