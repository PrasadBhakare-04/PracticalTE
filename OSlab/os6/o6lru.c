#include <stdio.h>
#include <limits.h>

int checkHit(int incomingPage, int queue[], int occupied) {
    for (int i = 0; i < occupied; i++) {
        if (incomingPage == queue[i])
            return 1; // Hit
    }
    return 0; // Miss
}

void printFrame(int queue[], int occupied) {
    for (int i = 0; i < occupied; i++)
        printf("%d\t\t\t", queue[i]);
}

int main() {
    int incomingStream[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    
    int n = sizeof(incomingStream) / sizeof(incomingStream[0]);
    int frames = 3;
    int queue[n];
    int distance[n];
    int occupied = 0;
    int pagefault = 0;
    int hits = 0; // To count hits

    printf("Page\t Frame1 \t Frame2 \t Frame3\n");
    
    for (int i = 0; i < n; i++) {
        printf("%d:  \t\t", incomingStream[i]);
        
        if (checkHit(incomingStream[i], queue, occupied)) {
            hits++; // Increment hits
            printFrame(queue, occupied);
        } else {
            if (occupied < frames) {
                queue[occupied] = incomingStream[i];
                pagefault++;
                occupied++;
                printFrame(queue, occupied);
            } else {
                int max = INT_MIN;
                int index;

                // Get LRU distance for each item in frame
                for (int j = 0; j < frames; j++) {
                    distance[j] = 0;
                    for (int k = i - 1; k >= 0; k--) {
                        ++distance[j];
                        if (queue[j] == incomingStream[k])
                            break;
                    }
                    
                    // Find frame item with max distance for LRU
                    if (distance[j] > max) {
                        max = distance[j];
                        index = j;
                    }
                }
                queue[index] = incomingStream[i];
                pagefault++;
                printFrame(queue, occupied);
            }
        }
        
        printf("\n");
    }
    
    printf("Page Fault: %d\n", pagefault);
    printf("Hits: %d\n", hits); // Print hits
    printf("Misses: %d\n", pagefault); // Misses equal to page faults

    // Calculate and print hit and miss ratios
    float hit_ratio = (float)hits / n;
    float miss_ratio = (float)pagefault / n;

    printf("Hit Ratio: %.2f\n", hit_ratio);
    printf("Miss Ratio: %.2f\n", miss_ratio);

    return 0;
}

