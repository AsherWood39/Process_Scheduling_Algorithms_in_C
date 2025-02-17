#include <stdio.h>

#define MAX_PROCESS 10  // Maximum number of processes that can be handled

// Structure to represent Process
typedef struct
{
    int process_id;        // Process ID (identifier)
    int arrival_time;      // Time at which the process arrives in the ready queue
    int burst_time;        // CPU burst time required by the process
    int completion_time;   // Time at which the process finishes execution
    int turn_around_time;  // Turnaround time (completion_time - arrival_time)
    int waiting_time;      // Waiting time (turn_around_time - burst_time)
    int priority;          // Priority
    int remaining_time;    // Remaining time for the process to execute
} Process;

// Structure to represent Gantt chart
typedef struct
{
    int process_id;
    int time;
}G;

G gantt_chart[MAX_PROCESS]; // Array of Gantt chart
Process processes[MAX_PROCESS]; // Array of processes
int I = 0;  // Gantt chart tracker index
int n;  // Number of processes

// Function to perform Pre-emptive Priority Scheduling and calculate the completion time, turnaround time and waiting time
void priority_preemptive_scheduling()
{
    int current_time = 0, completed_processes = 0;  // Track the current time and completed processes

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++)
    {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = -1;
    }

    // Sort the processes based on their arrival time using bubble sort
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) 
            {
                // Swap the processes if their arrival time is in the wrong order
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    
    // Perform the scheduling
    while (completed_processes < n)
    {
        int next_process = -1, max_priority = __INT_MAX__; // Initialize the minimum remaining time and next process

        // Find the process with minimum remaining time
        for (int i=0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && processes[i].priority < max_priority)
            {
                next_process = i;
                max_priority = processes[i].priority;
            }
        }

        // If no process is found, increment the current time
        if (next_process == -1)
        {
            // Represent idle time in the Gantt chart
            gantt_chart[I].process_id = -1;  // Placeholder for idle time
            gantt_chart[I].time = current_time;
            I++;
            current_time++;
            continue;
        }

        // Update the remaining time for the process
        processes[next_process].remaining_time--;

        // Update the current time
        current_time++;

        // Update the completion time and turnaround time for the process
        if (processes[next_process].remaining_time == 0) 
        {
            processes[next_process].completion_time = current_time;
            processes[next_process].turn_around_time = processes[next_process].completion_time - processes[next_process].arrival_time;
            processes[next_process].waiting_time = processes[next_process].turn_around_time - processes[next_process].burst_time;

            completed_processes++;   // Increment the number of completed processes
        }

        // Update the Gantt chart  
        if (I == 0 || gantt_chart[I-1].process_id != processes[next_process].process_id)
        {
            gantt_chart[I].process_id = processes[next_process].process_id;
            gantt_chart[I].time = current_time;
            I++;
        }
        else
        {
            gantt_chart[I-1].time = current_time;
        }
    }
}

// Function to calculate the average turnaround time
float calculate_average_turnaround_time()
{
    int total_turnaround_time = 0;  // Variable to store total turnaround time

    // Calculate the sum of all turnaround times
    for (int i = 0; i < n; i++)
        total_turnaround_time += processes[i].turn_around_time;

    return (float)total_turnaround_time / n;    // Return the average turnaround time
}

// Function to calculate the average waiting time
float calculate_average_waiting_time() 
{
    int total_waiting_time = 0; // Variable to store total waiting time

    // Calculate the sum of all waiting times
    for (int i = 0; i < n; i++)
        total_waiting_time += processes[i].waiting_time;

    return (float)total_waiting_time / n;   // Return the average waiting time
}

// Function to print the Gantt Chart (graphical representation of process execution)
void print_gantt_chart()
{
    printf("\nGantt Chart:\n ");

    // Print the top row (dashes) for Gantt chart
    for (int i = 0; i < I; i++) 
    {
        printf("--------");
    }

    printf("\n|");

    // Print the process IDs in the Gantt chart
    for (int i = 0; i < I; i++)
    {
        if (gantt_chart[i].process_id == -1) 
        {
            printf("\t|");
        } 
        else 
        {
            printf("  P%d   |", gantt_chart[i].process_id);
        }
    }

    printf("\n ");

    // Print the middle row (dashes) for Gantt chart
    for (int i = 0; i < I; i++) 
    {
        printf("--------");
    }

    // Print the completion times in the Gantt chart
    printf("\n0");
    for (int i = 0; i < I; i++) 
    {
        printf("\t%d", gantt_chart[i].time);
    }
    printf("\n");
}

// Function to print the resultant table (showing process details)
void print_resultant_table()
{
    printf("\nResultant Table:\n");

    // Print the table header with column names
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("|  Process ID   |     A . T     |     B . T     |     C . T     |   T . A . T   |     W . T     |   Priority    |\n");
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

// Main function: Entry point of the program
int main()
{
    // Input the number of processes and the quantum number from the user
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input the arrival and burst times for each process
    for (int i = 0; i < n; i++)
    {
        processes[i].process_id = i + 1;
        printf("Enter the Arrival time of P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the Burst time of P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter the Priority of P%d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    priority_preemptive_scheduling();   // Perform the Pre-emptive Priority Scheduling algorithm and calculate completion time, turnaround time, and waiting time for each process

    print_gantt_chart();        // Print the Gantt chart
    
    print_resultant_table();    // Print the resultant table with process details

    // Print the average turnaround time and waiting time
    printf("\nAverage Turnaround Time: %.2f\n", calculate_average_turnaround_time());
    printf("Average Waiting Time: %.2f\n", calculate_average_waiting_time());

    return 0;   // Return 0 to indicate successful execution
}

