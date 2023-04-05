#include <stdio.h>

struct Process {
    int arrivalTime;
    int burstTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
    int remainingTime;
};

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];

    printf("Enter the arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
        processes[i].remainingTime = processes[i].burstTime;
    }

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int shortestJobIndex = -1;
        int highestPriority = 9999;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                shortestJobIndex = i;
            }
        }

        if (shortestJobIndex == -1) {
            currentTime++;
            continue;
        }

        processes[shortestJobIndex].remainingTime--;
        if (processes[shortestJobIndex].remainingTime == 0) {
            completedProcesses++;
            int processCompletionTime = currentTime + 1;
            processes[shortestJobIndex].turnaroundTime = processCompletionTime - processes[shortestJobIndex].arrivalTime;
            processes[shortestJobIndex].waitingTime = processes[shortestJobIndex].turnaroundTime - processes[shortestJobIndex].burstTime;
            printf("Process %d completed at time %d. Turnaround time: %d. Waiting time: %d\n", shortestJobIndex + 1, processCompletionTime, processes[shortestJobIndex].turnaroundTime, processes[shortestJobIndex].waitingTime);
        }
        currentTime++;
    }

    float averageWaitingTime = 0;
    float averageTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        averageWaitingTime += processes[i].waitingTime;
        averageTurnaroundTime += processes[i].turnaroundTime;
    }
    averageWaitingTime /= n;
    averageTurnaroundTime /= n;
    printf("Average waiting time: %.2f\nAverage turnaround time: %.2f\n", averageWaitingTime, averageTurnaroundTime);

    return 0;
}
