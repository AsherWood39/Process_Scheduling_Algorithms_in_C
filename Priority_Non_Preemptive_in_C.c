#include <stdio.h>

#define MAX_PROCESS 10  // Maximum number of processes

// Structure to represent a process
struct Process
{
    int process_id;         // Unique ID for the process
    int arrival_time;       // Arrival time of the process
    int burst_time;         // Burst time (time required for execution)
    int completion_time;    // Time at which the process finishes execution
    int turn_around_time;   // Turnaround time = Completion time - Arrival time
    int waiting_time;       // Waiting time = Turnaround time - Burst time
    int priority;           // Priority of the process
    int remaining_time;     // Remaining time for the process during execution
} processes[MAX_PROCESS];   // Declare an array of processes with a maximum size of 10


int gantt_chart[MAX_PROCESS], I = 0;   // Array to store the order of processes in the Gantt chart and a counter variable

int n;  // Global variable to store the number of processes

// Function to perform Non Pre-emptive Priority Scheduling and calculate completion time, turnaround time and waiting time for each process
void non_preemptive_priority_scheduling()
{
    int current_time = 0, completed_processes = 0, min_priority, shortest_process;

    // Initialize remaining time for each process to its burst time
    for (int i = 0; i < n; i++) 
    {
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Execute the processes using a scheduling algorithm (Non Pre-emptive Priority Scheduling)
    while (completed_processes < n) 
    {
        min_priority = __INT_MAX__;     // Initialize with maximum integer value
        shortest_process = -1;          // Initialize to an invalid index

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) 
        {
            if (processes[i].arrival_time <= current_time && processes[i].priority < min_priority && processes[i].remaining_time > 0) 
            {
                min_priority = processes[i].priority;
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
        current_time += processes[shortest_process].burst_time;
        processes[shortest_process].completion_time = current_time;
        processes[shortest_process].remaining_time = 0;

        // Calculate turnaround time and waiting time
        processes[shortest_process].turn_around_time = processes[shortest_process].completion_time - processes[shortest_process].arrival_time;
        processes[shortest_process].waiting_time = processes[shortest_process].turn_around_time - processes[shortest_process].burst_time;

        completed_processes++;  // Increment the count of completed processes

        // Store the process ID in the Gantt chart order array
        gantt_chart[I] = shortest_process;
        I++;
    }
}

// Function to calculate average turnaround time
float calculate_average_turnaround_time()
{
    int total_turnaround_time = 0;  // Variable to store total turnaround time

    // Calculate the sum of all turnaround times
    for (int i = 0; i < n; i++)
        total_turnaround_time += processes[i].turn_around_time;

    return (float)total_turnaround_time / n;    // Return the average turnaround time
}

// Function to calculate average waiting time
float calculate_average_waiting_time()
{
    int total_waiting_time = 0; // Variable to store total waiting time

    // Calculate the sum of all waiting times
    for (int i = 0; i < n; i++)
        total_waiting_time += processes[i].waiting_time;

    return (float)total_waiting_time / n;   // Return the average waiting time
}

// Function to print the resultant table (showing process details)
void print_resultant_table()
{
    printf("\nResultant Table:\n");

    // Print the table header with column names
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("|  Process ID   |     A . T     |     B . T     |     C . T     |   T . A . T   |     W . T     |    Priority   |\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    // Print process information for each process
    for (int i = 0; i < n; i++)
        printf("|\tP%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n", 
            processes[i].process_id, 
            processes[i].arrival_time, 
            processes[i].burst_time, 
            processes[i].completion_time, 
            processes[i].turn_around_time, 
            processes[i].waiting_time,
            processes[i].priority
        );

    printf("-----------------------------------------------------------------------------------------------------------------\n");    
}

// Function to print the Gantt Chart (graphical representation of process execution)
void print_gantt_chart() 
{
    printf("\nGantt Chart:\n ");

    // Print the top row (dashes) for Gantt chart
    for (int i = 0; i < n; i++) 
    {
        if (i > 0 && processes[gantt_chart[i - 1]].completion_time < processes[gantt_chart[i]].arrival_time)
        {
            printf("--");
        }

        printf("----------------");
    }

    printf("\n|");

    // Print the process IDs in the Gantt chart
    for (int i = 0; i < n; i++)
    {
        if (i > 0 && processes[gantt_chart[i - 1]].completion_time < processes[gantt_chart[i]].arrival_time) 
        {
            printf("    |");
        }

        printf("\tP%d\t|", processes[gantt_chart[i]].process_id);
    }

    printf("\n ");

    // Print the middle row (dashes) for Gantt chart
    for (int i = 0; i < n; i++) 
    {
        if (i > 0 && processes[gantt_chart[i - 1]].completion_time < processes[gantt_chart[i]].arrival_time) 
        {
            printf("--");
        }

        printf("----------------");
    }

    // Print the completion times in the Gantt chart
    printf("\n0");
    for (int i = 0; i < n; i++) 
    {
        if (i > 0 && processes[gantt_chart[i - 1]].completion_time < processes[gantt_chart[i]].arrival_time) 
        {
            printf("    %d", processes[gantt_chart[i]].arrival_time);
        }

        printf("\t\t%d", processes[gantt_chart[i]].completion_time);
    }
    printf("\n");
}


// Main function: Entry point of the program
int main()
{
    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input the arrival and burst times for each process
    for (int i = 0; i < n; i++)
    {
        processes[i].process_id = i + 1;
        printf("Enter the arrival time of P%d : ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the burst time of P%d : ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter the priorities of P%d (0 being the highest) : ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    non_preemptive_priority_scheduling();   // Perform the Non Pre-emptive Priority Scheduling algorithm and calculate completion time, turnaround time, and waiting time for each process

    print_gantt_chart();        // Print the Gantt chart
    
    print_resultant_table();    // Print the resultant table with process details

    // Print the average turnaround time and waiting time
    printf("\nAverage Turnaround Time: %f\n", calculate_average_turnaround_time());
    printf("Average Waiting Time: %f\n", calculate_average_waiting_time());

    return 0;   // Return 0 to indicate successful execution
}
