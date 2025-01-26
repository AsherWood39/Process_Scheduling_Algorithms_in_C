#include <stdio.h>

#define MAX_PROCESS 10

// Structure to represent a process
struct Process
{
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
};

// Function to calculate average turnaround time
float calculate_average_turnaround_time(struct Process processes[], int n)
{
    int total_turnaround_time = 0;

    for (int i = 0; i < n; i++)
        total_turnaround_time += processes[i].turn_around_time;

    return (float)total_turnaround_time / n;
}

// Function to calculate average waiting time
float calculate_average_waiting_time(struct Process processes[], int n)
{
    int total_waiting_time = 0;

    for (int i = 0; i < n; i++)
        total_waiting_time += processes[i].waiting_time;

    return (float)total_waiting_time / n;
}

// Function to calculate completion time, turnaround time and waiting time for each process
void calculate_completion_turnaround_waiting_time(struct Process processes[], int n)
{
    int current_time = 0;

    for (int i = 0; i < n; i++)
    {
        if (current_time < processes[i].arrival_time)
            current_time = processes[i].arrival_time;

        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;

        current_time = processes[i].completion_time;
    }
}

// Function to print the resultant table
void print_resultant_table(struct Process processes[], int n)
{
    printf("\nResultant Table:\n");

    printf("-------------------------------------------------------------------------------------------------\n");
    printf("|  Process ID   |     A . T     |     B . T     |     C . T     |   T . A . T   |     W . T     |\n");
    printf("-------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
        printf("|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turn_around_time, processes[i].waiting_time);

    printf("-------------------------------------------------------------------------------------------------\n");    
}

// Function to print the Gantt Chart
void print_gantt_chart(struct Process processes[], int n)
{
    printf("\nGantt Chart:\n ");

    for (int i = 0; i < n; i++)
    {
        printf("----------------");
    }
    
    printf("\n|");

    for (int i=0; i<n; i++)
    {
        printf("\tP%d\t|", processes[i].process_id);
    }

    printf("\n ");

    for (int i = 0; i < n; i++)
    {
        printf("----------------");
    }

    printf("\n0\t");
    for (int i=0; i<n; i++)
    {
        printf("\t%d\t", processes[i].completion_time);
    }
    printf("\n");
}

// Main function
int main()
{
    int n;
    struct Process processes[MAX_PROCESS];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        processes[i].process_id = i + 1;
        printf("Enter the arrival time of process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    calculate_completion_turnaround_waiting_time(processes, n);

    print_gantt_chart(processes, n);
    
    print_resultant_table(processes, n);

    printf("\nAverage Turnaround Time: %f\n", calculate_average_turnaround_time(processes, n));
    printf("Average Waiting Time: %f\n", calculate_average_waiting_time(processes, n));

    return 0;
}