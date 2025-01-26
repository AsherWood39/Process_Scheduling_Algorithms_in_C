#include <stdio.h>

#define MAX_PROCESS 10     // Define the maximum number of processes

// Structure to represent a process
struct Process
{
    int process_id;          // Unique ID for the process
    int arrival_time;        // Arrival time of the process (when the process arrives)
    int burst_time;          // Burst time (the total time the process needs to execute)
    int completion_time;     // Completion time (when the process finishes execution)
    int turn_around_time;    // Turnaround time (time spent from arrival to completion)
    int waiting_time;        // Waiting time (time spent waiting before execution starts)
};

// Function to calculate average turnaround time
float calculate_average_turnaround_time(struct Process processes[], int n)
{
    int total_turnaround_time = 0;    // Variable to accumulate the total turnaround time

    // Iterate through all processes and sum their turnaround times
    for (int i = 0; i < n; i++)
        total_turnaround_time += processes[i].turn_around_time;

    return (float)total_turnaround_time / n;    // Return the average turnaround time
}

// Function to calculate average waiting time
float calculate_average_waiting_time(struct Process processes[], int n)
{
    int total_waiting_time = 0;    // Variable to accumulate the total waiting time

    // Iterate through all processes and sum their waiting times
    for (int i = 0; i < n; i++)
        total_waiting_time += processes[i].waiting_time;

    return (float)total_waiting_time / n;    // Return the average waiting time
}

// Function to perform the FCFS scheduling algorithm and calculate completion time, turnaround time and waiting time for each process
void fcfs_scheduling(struct Process processes[], int n)
{
    int current_time = 0;    // Keep track of the current time during execution

    // Iterate through all processes and calculate their completion, turnaround, and waiting times
    for (int i = 0; i < n; i++)
    {
        // If the current time is less than the arrival time of the process, update current time to arrival time
        if (current_time < processes[i].arrival_time)
        if (current_time < processes[i].arrival_time)
            current_time = processes[i].arrival_time;

        // Calculate completion time for the process
        processes[i].completion_time = current_time + processes[i].burst_time;
        
        // Calculate turnaround time (completion time - arrival time)
        processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;

        // Calculate waiting time (turnaround time - burst time)
        processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;

        // Update current time to the completion time of the current process
        current_time = processes[i].completion_time;
    }
}

// Function to print the resultant table showing process details
void print_resultant_table(struct Process processes[], int n)
{
    printf("\nResultant Table:\n");

    // Print the table header with column names
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("|  Process ID   |     A . T     |     B . T     |     C . T     |   T . A . T   |     W . T     |\n");
    printf("-------------------------------------------------------------------------------------------------\n");

    // Print process details (ID, arrival time, burst time, completion time, turnaround time, waiting time)
    for (int i = 0; i < n; i++)
        printf("|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turn_around_time, processes[i].waiting_time);

    printf("-------------------------------------------------------------------------------------------------\n");    
}

// Function to print the Gantt Chart representing process execution
void print_gantt_chart(struct Process processes[], int n)
{
    printf("\nGantt Chart:\n ");

    // Print the top row with dashes representing each process slot
    for (int i = 0; i < n; i++)
    {
        printf("----------------");
    }
    
    printf("\n|");

    // Print the process IDs (P1, P2, etc.) in the Gantt chart
    for (int i=0; i<n; i++)
    {
        printf("\tP%d\t|", processes[i].process_id);
    }

    printf("\n ");

    // Print the bottom row with dashes representing each process slot
    for (int i = 0; i < n; i++)
    {
        printf("----------------");
    }

    printf("\n0\t");

    // Print the completion times for each process
    for (int i=0; i<n; i++)
    {
        printf("\t%d\t", processes[i].completion_time);
    }
    printf("\n");
}

// Main function: Entry point of the program
int main()
{
    int n;    // Variable to store the number of processes
    struct Process processes[MAX_PROCESS];    // Array to store process information

    // Input the number of processes from the user
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input the arrival and burst times for each process from the user
    for (int i = 0; i < n; i++)
    {
        processes[i].process_id = i + 1;    // Set the process ID to a unique number starting from 1
        printf("Enter the arrival time of process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    // Perform the FCFS scheduling algorithm and calculate the completion time, turnaround time, and waiting time for each process
    fcfs_scheduling(processes, n);

    // Print the Gantt chart showing process execution order and times
    print_gantt_chart(processes, n);

    // Print the resultant table showing all the process details
    print_resultant_table(processes, n);

    // Print the average turnaround time and average waiting time
    printf("\nAverage Turnaround Time: %f\n", calculate_average_turnaround_time(processes, n));
    printf("Average Waiting Time: %f\n", calculate_average_waiting_time(processes, n));

    return 0;
}
