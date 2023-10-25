#include <stdio.h>

#define num_res 3
#define num_proc 5

int avail[num_res];
int maximum[num_proc][num_res];
int allocated[num_proc][num_res];
int need[num_proc][num_res];

int isSafe() {
    int work[num_res];
    int finish[num_proc] = {0};
    int sequence[num_proc];
    int count = 0;

    for (int i = 0; i < num_res; i++) {
        work[i] = avail[i];
    }

    while (count < num_proc) {
        int found = 0;
        for (int i = 0; i < num_proc; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < num_res; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == num_res) {
                    for (int k = 0; k < num_res; k++) {
                        work[k] += allocated[i][k];
                    }
                    sequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            return 0; 
        }
    }
    return 1; 
}

int main() {
    printf("Enter the available resources (A B C): ");
    scanf("%d %d %d", &avail[0], &avail[1], &avail[2]);

    printf("Enter the maximum matrix:\n");
    for (int i = 0; i < num_proc; i++) {
        for (int j = 0; j < num_res; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter the allocated matrix:\n");
    for (int i = 0; i < num_proc; i++) {
        for (int j = 0; j < num_res; j++) {
            scanf("%d", &allocated[i][j]);
            need[i][j] = maximum[i][j] - allocated[i][j];
        }
    }

    printf("Need Matrix:\n");
    for (int i = 0; i < num_proc; i++) {
        for (int j = 0; j < num_res; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int safe = isSafe();

    if (safe) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is not in a safe state.\n");
    }

    int request[3] = {1, 0, 2};
    int process_id = 0;

    if (request[0] <= need[process_id][0] && request[0] <= avail[0] &&
        request[1] <= need[process_id][1] && request[1] <= avail[1] &&
        request[2] <= need[process_id][2] && request[2] <= avail[2]) {
 
        for (int i = 0; i < num_res; i++) {
            avail[i] -= request[i];
            allocated[process_id][i] += request[i];
            need[process_id][i] -= request[i];
        }

        safe = isSafe();

        if (safe) {
            printf("Request can be granted safely.\n");
        } else {
            printf("Request cannot be granted safely.\n");
        }
    } else {
        printf("Request cannot be granted immediately.\n");
    }

    return 0;
}

