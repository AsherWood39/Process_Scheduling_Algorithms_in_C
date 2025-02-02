#include <stdio.h>

#define MAX_PROCESS 10  // Maximum number of processes that can be handled

// Structure to represent a process
typedef struct  
{
    int process_id;        // Process ID (identifier)
    int arrival_time;      // Time at which the process arrives in the ready queue
    int burst_time;        // CPU burst time required by the process
    int completion_time;   // Time at which the process finishes execution
    int turn_around_time;  // Turnaround time (completion_time - arrival_time)
    int waiting_time;      // Waiting time (turn_around_time - burst_time)
    int remaining_time;    // Remaining time for the process to execute
} Process;

Process processes[MAX_PROCESS];  // Array of processes

int gantt_chart[2 * MAX_PROCESS][2], I = 0;  // Gantt chart to track the execution sequence

int n, q;  // Number of processes and time quantum (slice of time for Round Robin)

// Function to perform Round Robin Scheduling and calculate the completion time, turnaround time and waiting time
void round_robin_scheduling()
{
    int current_time = 0, completed_processes = 0;  // Track the current time and completed processes
    int queue[MAX_PROCESS], front = 0, rear = 0;  // Queue to store process indices, front and rear pointers

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

    // Enqueue processes that have arrived at the start
    for (int i = 0; i < n; i++)
    {
        if (processes[i].arrival_time <= current_time)
        {
            queue[rear++] = i;
        }
    }

    // Process execution with round robin scheduling
    while (completed_processes < n)
    {
        // Dequeue a process to execute
        int process_index = queue[front++]; // Get the process at the front of the queue

        // Gantt chart entry for the current process
        gantt_chart[I][0] = processes[process_index].process_id;

        // Execute the process for up to the time quantum (q)
        if (processes[process_index].remaining_time <= q)
        {
            current_time += processes[process_index].remaining_time;  // Update time with remaining burst
            processes[process_index].remaining_time = 0;  // Process is finished
            processes[process_index].completion_time = current_time;

            // Calculate turnaround time and waiting time
            processes[process_index].turn_around_time = processes[process_index].completion_time - processes[process_index].arrival_time;
            processes[process_index].waiting_time = processes[process_index].turn_around_time - processes[process_index].burst_time;

            completed_processes++;  // Increment the count of completed processes
        }
        else
        {
            processes[process_index].remaining_time -= q;  // Deduct the quantum from remaining time
            current_time += q;  // Increment current time by the quantum
        }

        gantt_chart[I][1] = current_time;
        I++;

        // Add newly arrived processes to the queue that have arrived during execution
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && processes[i].completion_time == -1) {
                // Check if the process is already in the queue
                int already_in_queue = 0;
                for (int j = front-1; j < rear; j++) {
                    if (queue[j] == i) {
                        already_in_queue = 1;
                        break;
                    }
                }
                if (!already_in_queue) {
                    queue[rear++] = i;
                }
            }
        }

        // If the process still has remaining time, add it back to the queue
        if (processes[process_index].remaining_time > 0) {
            queue[rear++] = process_index;  // Re-queue the process for next execution
        }

        // Shift the contents of the queue to the left by 1 index
        for (int i = front; i < rear; i++)
        {
            queue[i - 1] = queue[i];
        }
        front--; rear--;
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
        if (i+1 != I && gantt_chart[i][0] == gantt_chart[i + 1][0])
        {
            continue;
        }
        printf("--------");
    }

    printf("\n|");

    // Print the process IDs in the Gantt chart
    for (int i = 0; i < I; i++)
    {
        if (i+1 != I && gantt_chart[i][0] == gantt_chart[i + 1][0])
        {
            continue;
        }
        printf("  P%d   |", gantt_chart[i][0]);
    }

    printf("\n ");

    // Print the middle row (dashes) for Gantt chart
    for (int i = 0; i < I; i++) 
    {
        if (i+1 != I && gantt_chart[i][0] == gantt_chart[i + 1][0])
        {
            continue;
        }
        printf("--------");
    }

    // Print the completion times in the Gantt chart
    printf("\n0");
    for (int i = 0; i < I; i++) 
    {
        if (i+1 != I && gantt_chart[i][0] == gantt_chart[i + 1][0])
        {
            continue;
        }
        printf("\t%d", gantt_chart[i][1]);
    }
    printf("\n");
}

// Function to print the resultant table (showing process details)
void print_resultant_table()
{
    printf("\nResultant Table:\n");

    // Print the table header with column names
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("|  Process ID   |     A . T     |     B . T     |     C . T     |   T . A . T   |     W . T     |\n");
    printf("-------------------------------------------------------------------------------------------------\n");

    // Print process information for each process
    for (int i = 0; i < n; i++)
        printf("|\tP%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n", 
            processes[i].process_id, 
            processes[i].arrival_time, 
            processes[i].burst_time, 
            processes[i].completion_time, 
            processes[i].turn_around_time, 
            processes[i].waiting_time
        );

    printf("-------------------------------------------------------------------------------------------------\n");    
}

// Main function: Entry point of the program
int main()
{
    // Input the number of processes and the quantum number from the user
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the quantum number: ");
    scanf("%d", &q);

    // Input the arrival and burst times for each process
    for (int i = 0; i < n; i++)
    {
        processes[i].process_id = i + 1;
        printf("Enter the arrival time of P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the burst time of P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    round_robin_scheduling();   // Perform the Round Robin Scheduling algorithm and calculate completion time, turnaround time, and waiting time for each process

    print_gantt_chart();        // Print the Gantt chart
    
    print_resultant_table();    // Print the resultant table with process details

    // Print the average turnaround time and waiting time
    printf("\nAverage Turnaround Time: %f\n", calculate_average_turnaround_time());
    printf("Average Waiting Time: %f\n", calculate_average_waiting_time());

    return 0;   // Return 0 to indicate successful execution
}
