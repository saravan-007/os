#include <stdio.h>
typedef struct Process {
    int pid;         
    int arrival_time; 
    int burst_time;   
    int priority;     
    int completion_time; 
    int waiting_time;  
    int turnaround_time; 
} Process;

void swap(Process* p1, Process* p2) {
    Process temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void priority_scheduling(Process processes[], int num_processes) {
    int current_time = 0;
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = i + 1; j < num_processes; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                swap(&processes[i], &processes[j]);
            }
        }
    }

    for (int i = 0; i < num_processes; i++) {
        int highest_idx = i;
        for (int j = i + 1; j < num_processes; j++) {
            if (processes[j].arrival_time <= current_time && processes[j].priority > processes[highest_idx].priority) {
                highest_idx = j;
            }
        }

        swap(&processes[i], &processes[highest_idx]);

        processes[i].completion_time = current_time + processes[i].burst_time;

        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;

        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        current_time = processes[i].completion_time;
    }

    printf("Priority Scheduling Results:\n");
    printf("PID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    for (int i = 0; i < num_processes; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].priority,
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

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    Process processes[num_processes];

    for (int i = 0; i < num_processes; i++) {
        processes[i].pid = i + 1;

        printf("Enter arrival time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival_time);

        printf("Enter burst time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);

        printf("Enter priority for process %d (higher value means higher priority): ", processes[i].pid);
        scanf("%d", &processes[i].priority);
    }

    priority_scheduling(processes, num_processes);

    return 0;
}

