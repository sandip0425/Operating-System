#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

bool isSafe(int processes[], int avail[], int max[][MAX_R], int allot[][MAX_R], int P, int R) {
    int need[MAX_P][MAX_R];
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];

    bool finish[MAX_P] = {0};
    int safeSeq[MAX_P];
    int work[MAX_R];
    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;
                
                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];

                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }

        if (found == false) {
            printf("System is not in a safe state\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");

    return true;
}

int main() {
    int P, R;
    printf("Enter the number of processes: ");
    scanf("%d", &P);
    printf("Enter the number of resources: ");
    scanf("%d", &R);

    int processes[MAX_P];
    for (int i = 0; i < P; i++) {
        processes[i] = i;
    }

    int avail[MAX_R];
    printf("Enter the available resources: ");
    for (int i = 0; i < R; i++) {
        scanf("%d", &avail[i]);
    }

    int max[MAX_P][MAX_R], allot[MAX_P][MAX_R];
    printf("Enter the maximum resource matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocated resource matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &allot[i][j]);
        }
    }

    isSafe(processes, avail, max, allot, P, R);

    return 0;
}
