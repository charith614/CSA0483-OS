#include <stdio.h>

struct Process {
    int pid; // Process ID
    int burst_time; // Burst time
};

void swap(struct Process *p1, struct Process *p2) {
    struct Process temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sjf(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) { 
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    int waiting_time = 0;
    for (int i = 0; i < n; i++) {
        waiting_time += processes[i].burst_time;
        printf("Process %d: Waiting Time = %d\n", processes[i].pid, waiting_time);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter burst time for Process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
    }

    sjf(processes, n);

    return 0;
}
