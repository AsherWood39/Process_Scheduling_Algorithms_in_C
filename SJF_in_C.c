#include <stdio.h>

#define MAX_PROCESS 10 // Maximum number of processes

// Structure to represent a process
struct Process
{
    int process_id;          // Unique ID for the process
    int arrival_time;        // Arrival time of the process
    int burst_time;          // Burst time (time required for execution)
    int completion_time;     // Time at which the process finishes execution
    int turn_around_time;    // Turnaround time = Completion time - Arrival time
    int waiting_time;        // Waiting time = Turnaround time - Burst time
    int remaining_time;      // Remaining time for the process during execution
};

// Array to store the order of processes in the Gantt chart and a counter variable
int gantt_chart[MAX_PROCESS], I = 0;

// Function to calculate average turnaround time
float calculate_average_turnaround_time(struct Process processes[], int n)
{
    int total_turnaround_time = 0;

    // Calculate the sum of all turnaround times
    for (int i = 0; i < n; i++)
        total_turnaround_time += processes[i].turn_around_time;

    return (float)total_turnaround_time / n;    // Return the average turnaround time
}

// Function to calculate average waiting time
float calculate_average_waiting_time(struct Process processes[], int n)
{
    int total_waiting_time = 0;

    // Calculate the sum of all waiting times
    for (int i = 0; i < n; i++)
        total_waiting_time += processes[i].waiting_time;

    return (float)total_waiting_time / n;    // Return the average waiting time
}

// Function to calculate completion time, turnaround time and waiting time for each process
void sjf_scheduling(struct Process processes[], int n)
{
    int current_time = 0, completed_processes = 0, min_burst_time, shortest_process;

    // Initialize remaining time for each process to its burst time
    for (int i = 0; i < n; i++)
    {
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Execute the processes using a scheduling algorithm (Shortest Job First)
    while (completed_processes < n)
    {
        min_burst_time =__INT_MAX__;    // Initialize with maximum integer value
        shortest_process = -1;          // Initialize to an invalid index

        // Find the process with the shortest remaining time and which has arrived
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time < min_burst_time && processes[i].remaining_time > 0)
            {
                min_burst_time = processes[i].remaining_time;
                shortest_process = i;
            }
        }

        // If no process is ready to execute, increment the current time
        if (shortest_process == -1)
        {
            current_time++;
            continue;
        }

        // Update the process details after executing the selected process
        processes[shortest_process].remaining_time = 0;
        processes[shortest_process].completion_time = current_time + processes[shortest_process].burst_time;
        current_time = processes[shortest_process].completion_time;

        // Calculate turnaround time and waiting time
        processes[shortest_process].turn_around_time = processes[shortest_process].completion_time - processes[shortest_process].arrival_time;
        processes[shortest_process].waiting_time = processes[shortest_process].turn_around_time - processes[shortest_process].burst_time;

        // Store the process ID in the Gantt chart order array
        gantt_chart[I] = shortest_process;
        I++;
        
        completed_processes++;    // Increment the count of completed processes
    }
}

// Function to print the resultant table (showing process details)
void print_resultant_table(struct Process processes[], int n)
{
    printf("\nResultant Table:\n");

    // Print the table header with column names
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("|  Process ID   |     A . T     |     B . T     |     C . T     |   T . A . T   |     W . T     |\n");
    printf("-------------------------------------------------------------------------------------------------\n");

    // Print process information for each process
    for (int i = 0; i < n; i++)
        printf("|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turn_around_time, processes[i].waiting_time);

    printf("-------------------------------------------------------------------------------------------------\n");    
}

// Function to print the Gantt Chart (graphical representation of process execution)
void print_gantt_chart(struct Process processes[], int n)
{
    printf("\nGantt Chart:\n ");

    // Print the top row (dashes) for Gantt chart
    for (int i = 0; i < n; i++)
    {
        printf("----------------");
    }
    
    printf("\n|");

    // Print the process IDs in the Gantt chart
    for (int i=0; i<n; i++)
    {
        printf("\tP%d\t|", processes[gantt_chart[i]].process_id);
    }

    printf("\n ");

    // Print the middle row (dashes) for Gantt chart
    for (int i = 0; i < n; i++)
    {
        printf("----------------");
    }

    // Print the completion times in the Gantt chart
    printf("\n0\t");
    for (int i=0; i<n; i++)
    {
        printf("\t%d\t", processes[gantt_chart[i]].completion_time);
    }
    printf("\n");
}

// Main function to input data and execute the scheduling algorithm
int main()
{
    int n;
    struct Process processes[MAX_PROCESS];

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input the arrival and burst times for each process
    for (int i = 0; i < n; i++)
    {
        processes[i].process_id = i + 1;
        printf("Enter the arrival time of process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    // Perform the SJF scheduling algorithm and calculate completion time, turnaround time, and waiting time for each process
    sjf_scheduling(processes, n);

    // Print the Gantt chart
    print_gantt_chart(processes, n);    
    
    // Print the resultant table with process details
    print_resultant_table(processes, n);    
    
    // Print the average turnaround time and waiting time
    printf("\nAverage Turnaround Time: %f\n", calculate_average_turnaround_time(processes, n));
    printf("Average Waiting Time: %f\n", calculate_average_waiting_time(processes, n));

    return 0;
}
