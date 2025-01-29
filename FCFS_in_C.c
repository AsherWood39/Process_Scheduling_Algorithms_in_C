#include <stdio.h>

#define MAX_PROCESS 10 // Define the maximum number of processes

// Structure to represent a process with necessary attributes
struct Process 
{
    int process_id;         // Process ID
    int arrival_time;       // Arrival time of the process
    int burst_time;         // Burst time (CPU time required) of the process
    int completion_time;    // Completion time after process execution
    int turn_around_time;   // Turnaround time = Completion time - Arrival time
    int waiting_time;       // Waiting time = Turnaround time - Burst time
} processes[MAX_PROCESS];   // Declare an array of processes with a maximum size of 10

int n;  // Global variable to store the number of processes

// Function to perform First-Come, First-Served (FCFS) scheduling and calculate the completion time, turnaround time and waiting time
void fcfs_scheduling() 
{
    // Sort the processes based on their arrival time using bubble sort
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) 
            {
                // Swap the processes if their arrival time is in the wrong order
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int current_time = 0;

    // Loop through all processes and calculate their completion time, turnaround time, and waiting time
    for (int i = 0; i < n; i++) 
    {
        // If the current time is less than the arrival time of the process, move current time to arrival time
        if (current_time < processes[i].arrival_time)
            current_time = processes[i].arrival_time;

        // Calculate the completion time by adding burst time to the current time
        processes[i].completion_time = current_time + processes[i].burst_time;

        processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;   // Calculate the turnaround time
        processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;        // Calculate the waiting time

        current_time = processes[i].completion_time;    // Update the current time after the process completes
    }
}

// Function to calculate the average turnaround time of all processes
float calculate_average_turnaround_time() 
{
    int total_turnaround_time = 0;

    // Loop through all processes and accumulate the total turnaround time
    for (int i = 0; i < n; i++)
        total_turnaround_time += processes[i].turn_around_time;

    return (float)total_turnaround_time / n;    // Return the average turnaround time
}

// Function to calculate the average waiting time of all processes
float calculate_average_waiting_time() 
{
    int total_waiting_time = 0;

    // Loop through all processes and accumulate the total waiting time
    for (int i = 0; i < n; i++)
        total_waiting_time += processes[i].waiting_time;

    return (float)total_waiting_time / n;   // Return the average waiting time
}

// Function to print the resultant table (showing process details)
void print_resultant_table() 
{
    printf("\nResultant Table:\n");
    
    // Print the table header with column names
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("|  Process ID   |     A . T     |     B . T     |     C . T     |   T . A . T   |     W . T     |\n");
    printf("-------------------------------------------------------------------------------------------------\n");

    // Print process details (ID, arrival time, burst time, completion time, turnaround time, waiting time)
    for (int i = 0; i < n; i++) 
    {
        printf("|\tP%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n", 
            processes[i].process_id, 
            processes[i].arrival_time, 
            processes[i].burst_time, 
            processes[i].completion_time, 
            processes[i].turn_around_time, 
            processes[i].waiting_time
        );
    }

    printf("-------------------------------------------------------------------------------------------------\n");
}

// Function to print the Gantt Chart (graphical representation of process execution)
void print_gantt_chart() 
{
    printf("\nGantt Chart:\n ");
    
    // Print the top row with dashes representing each process slot
    for (int i = 0; i < n; i++) 
    {
        if (i > 0 && processes[i - 1].completion_time < processes[i].arrival_time)
        {
            printf("--");
        }

        printf("----------------");
    }

    printf("\n|");

    // Print the process IDs (P1, P2, etc.) in the Gantt chart
    for (int i = 0; i < n; i++)
    {
        if (i > 0 && processes[i - 1].completion_time < processes[i].arrival_time) 
        {
            printf("    |");
        }

        printf("\tP%d\t|", processes[i].process_id);
    }

    printf("\n ");

    // Print the bottom row with dashes representing each process slot
    for (int i = 0; i < n; i++) 
    {
        if (i > 0 && processes[i - 1].completion_time < processes[i].arrival_time) 
        {
            printf("--");
        }

        printf("----------------");
    }

    // Print the completion times for each process
    printf("\n0");
    for (int i = 0; i < n; i++) 
    {
        if (i > 0 && processes[i - 1].completion_time < processes[i].arrival_time) 
        {
            printf("    %d", processes[i].arrival_time);
        }

        printf("\t\t%d", processes[i].completion_time);
    }
    printf("\n");
}

// Main function: Entry point of the program
int main() 
{
    // Input the number of processes from the user
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Ensure that the number of processes is within the allowed limit
    if (n > MAX_PROCESS) 
    {
        printf("Number of processes cannot exceed %d.\n", MAX_PROCESS);
        return 1; // Exit if the number exceeds the maximum allowed
    }

    // Input the arrival and burst times for each process from the user
    for (int i = 0; i < n; i++) 
    {
        processes[i].process_id = i + 1;    // Set the process ID to a unique number starting from 1
        printf("Enter the arrival time of P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the burst time of P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    fcfs_scheduling();          // Perform the FCFS scheduling algorithm and calculate the completion time, turnaround time, and waiting time for each process

    print_gantt_chart();        // Print the Gantt chart showing process execution order and times
    
    print_resultant_table();    // Print the resultant table showing all the process details

    // Print the average turnaround time and average waiting time
    printf("\nAverage Turnaround Time: %f\n", calculate_average_turnaround_time());
    printf("Average Waiting Time: %f\n", calculate_average_waiting_time());

    return 0; // Return 0 to indicate successful execution
}
