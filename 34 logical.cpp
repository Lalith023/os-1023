#include<stdio.h>

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n], i, j, max;
    
    for(i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    
    for(i = 0; i < n; i++) {
        max = -1;
        for(j = 0; j < m; j++) {
            if(blockSize[j] >= processSize[i]) {
                if(max == -1 || blockSize[j] > blockSize[max]) {
                    max = j;
                }
            }
        }
        if(max != -1) {
            allocation[i] = max;
            blockSize[max] -= processSize[i];
        }
    }
    
    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for(i = 0; i < n; i++) {
        printf(" %d\t\t%d\t\t", i+1, processSize[i]);
        if(allocation[i] != -1) {
            printf("%d\n", allocation[i]+1);
        }
        else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int blockSize[] = {40, 10, 30, 60};
    int processSize[] = {100, 50, 30, 120, 35};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);
    
    printf("Memory partitions: ");
    for(int i=0; i<m; i++) {
        printf("%d KB ", blockSize[i]);
    }
    printf("\n\nWorst Fit:\n");
    worstFit(blockSize, m, processSize, n);
    
    return 0;
}
