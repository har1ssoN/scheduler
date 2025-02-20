#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define TIME_QUANTUM 2

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int start_time;
    int finish_time;
    int remaining_burst;
} Process;

Process processes[MAX_PROCESSES];
int num_processes = 0;
int current_time = 0;

void add_process(int id, int arrival_time, int burst_time) {
    processes[num_processes].id = id;
    processes[num_processes].arrival_time = arrival_time;
    processes[num_processes].burst_time = burst_time;
    processes[num_processes].remaining_burst = burst_time;
    num_processes++;
}

void fifo_scheduler() {
    for (int i = 0; i < num_processes; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].start_time = current_time;
        processes[i].finish_time = current_time + processes[i].burst_time;
        printf("Processo %d: executou durante %d períodos de tempo. [Tempo atual: %d]\n", processes[i].id, processes[i].burst_time, processes[i].finish_time);
        current_time = processes[i].finish_time;
    }
}

void sjf_scheduler() {
    bool completed[MAX_PROCESSES] = {false};

    while (true) {
        int shortest_index = -1;
        int shortest_burst = __INT_MAX__;

        for (int j = 0; j < num_processes; j++) {
            if (!completed[j] && processes[j].arrival_time <= current_time && processes[j].remaining_burst < shortest_burst) {
                shortest_burst = processes[j].remaining_burst;
                shortest_index = j;
            }
        }

        if (shortest_index == -1) {
            current_time++;
            continue;
        }

        processes[shortest_index].start_time = current_time;
        processes[shortest_index].finish_time = current_time + processes[shortest_index].remaining_burst;
        printf("Processo %d: executou durante %d períodos de tempo. [Tempo atual: %d]\n", processes[shortest_index].id, processes[shortest_index].remaining_burst, processes[shortest_index].finish_time);
        current_time = processes[shortest_index].finish_time;
        processes[shortest_index].remaining_burst = 0;
        completed[shortest_index] = true;

        bool all_completed = true;
        for (int i = 0; i < num_processes; i++) {
            if (!completed[i]) {
                all_completed = false;
                break;
            }
        }
        if (all_completed) break;
    }
}

void round_robin_scheduler() {
    bool completed[MAX_PROCESSES] = {false};

    printf("\nQuantum = %d\n\n", TIME_QUANTUM);

    while (true) {
        bool all_completed = true;

        for (int i = 0; i < num_processes; i++) {
            if (!completed[i] && processes[i].arrival_time <= current_time) {
                int execution_time = (processes[i].remaining_burst > TIME_QUANTUM) ? TIME_QUANTUM : processes[i].remaining_burst;
                printf("Processo %d: executou durante %d períodos de tempo. [Tempo atual: %d]\n", processes[i].id, execution_time, current_time + execution_time);
                processes[i].remaining_burst -= execution_time;
                current_time += execution_time;

                if (processes[i].remaining_burst == 0) {
                    processes[i].finish_time = current_time;
                    completed[i] = true;
                }
            }
        }

        for (int i = 0; i < num_processes; i++) {
            if (!completed[i]) {
                all_completed = false;
                break;
            }
        }
        if (all_completed) break;
    }
}

int main() {
    int choice;
    printf("Escolha o algoritmo de escalonamento:\n");
    printf("1. FIFO\n");
    printf("2. Shortest-Job-First (SJF)\n");
    printf("3. Round Robin (RR)\n");
    scanf("%d", &choice);

    add_process(1, 0, 6); // ID, Arrival time, Burst time
    add_process(2, 1, 8);
    add_process(3, 2, 7);
    add_process(4, 3, 3);
    add_process(5, 8, 8);
    add_process(6, 5, 2);
    add_process(7, 10, 5);
    add_process(8, 12, 1);
    add_process(9, 13, 7);
    add_process(10, 15, 10);

    switch (choice) {
        case 1:
            fifo_scheduler();
            break;
        case 2:
            sjf_scheduler();
            break;
        case 3:
            round_robin_scheduler();
            break;
        default:
            printf("Escolha inválida!\n");
            break;
    }
    return 0;
}
