// CPU Scheduling
// Array of processes, first come first serve implimentation
// Calculate waiting time and throughput
#include <stdio.h>
#include <stdlib.h>

void waiting_time (int pros[], int wait[], int size) {
    for (int i = 0; i < size; i++) {
        int wait_i;
        for (int j = i; j >= 0; j--) {
            wait_i += pros[j]; 
        }
        wait[i] = wait_i;
        wait_i = 0;
    }
    
}

void throughput_fun(int pros[], int wait[], int throughput[], int size) {
    for (int i = 0; i < size; i++) {
        throughput[i] = wait[i] + pros[i+1];
    }
}

int main () {
    int pros[5] = {0, 2, 3, 6, 1};
    int wait[4] = {};
    int throughput[4] = {};

    waiting_time(pros, wait, 4);
    throughput_fun(pros, wait, throughput, 4);

    printf("Waiting Time    Througput\n");
    for (int i = 0; i < 4; i++){
        printf("%d                %d\n", wait[i], throughput[i]);
    }
    
    return 0; 
}