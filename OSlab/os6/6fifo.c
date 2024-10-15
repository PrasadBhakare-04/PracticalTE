#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 3  // Number of frames

void printFrames(int frames[], int frameCount) {
    printf("Frames: ");
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
    }
    printf("\n");
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2}; // Input pages
    int pageCount = sizeof(pages) / sizeof(pages[0]);

    int frames[FRAME_SIZE];
    for (int i = 0; i < FRAME_SIZE; i++) {
        frames[i] = -1; // Initialize frames
    }

    int hitCount = 0;
    int missCount = 0;
    int pointer = 0; // Pointer for FIFO

    for (int i = 0; i < pageCount; i++) {
        int isHit = 0;

        // Check if the page is already in the frames
        for (int j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] == pages[i]) {
                isHit = 1;
                hitCount++;
                break;
            }
        }

        if (!isHit) {
            // Page fault occurs
            frames[pointer] = pages[i]; // Replace the page
            pointer = (pointer + 1) % FRAME_SIZE; // Move the pointer

            missCount++;
        }

        printFrames(frames, FRAME_SIZE);
    }

    // Calculate hit and miss ratios
    double hitRatio = (double)hitCount / pageCount;
    double missRatio = (double)missCount / pageCount;

    // Output results
    printf("\nTotal Hits: %d\n", hitCount);
    printf("Total Misses: %d\n", missCount);
    printf("Hit Ratio: %.2f\n", hitRatio);
    printf("Miss Ratio: %.2f\n", missRatio);

    return 0;
}

