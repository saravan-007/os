#include <stdio.h>
typedef struct Process {
    int pid;         
    int arrival_time; 
    int burst_time; 
    int remaining_time; 
    int completion_time; 
    int waiting_time; 
    int turnaround_time; 
} Process;
void round_robin_scheduling(Process processes[], int num_processes, int time_quantum) {
    int current_time = 0;
    int completed_processes = 0;
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = i + 1; j < num_processes; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    while (completed_processes < num_processes) {
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                int executed_time = (processes[i].remaining_time < time_quantum) ? processes[i].remaining_time : time_quantum;

                processes[i].remaining_time -= executed_time;
                current_time += executed_time;

                if (processes[i].remaining_time == 0) {
                    processes[i].completion_time = current_time;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    completed_processes++;
                }
            }
        }
    }

    printf("Round Robin Scheduling Results:\n");
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    for (int i = 0; i < num_processes; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }

    float avg_waiting_time = 0;
    float avg_turnaround_time = 0;

    for (int i = 0; i < num_processes; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }

    avg_waiting_time /= num_processes;
    avg_turnaround_time /= num_processes;

    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int num_processes;
    int time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    Process processes[num_processes];

    for (int i = 0; i < num_processes; i++) {
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;

        printf("Enter arrival time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival_time);

        printf("Enter burst time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    round_robin_scheduling(processes, num_processes, time_quantum);

    return 0;
}

