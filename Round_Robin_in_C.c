#include <stdio.h>

#define MAX_PROCESS 10

struct Process
{
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int remaining_time;
}processes[MAX_PROCESS];

int gantt_chart[2 * MAX_PROCESS][2 * MAX_PROCESS], I = 0;

int n, q;

void round_robin_scheduling()
{
    int current_time = 0, completed_processes = 0;
    int queue[MAX_PROCESS], front = 0, rear = 0;

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
                struct Process temp = processes[j];
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
        int process_index = queue[front++];

        // Gantt chart entry for the current process
        gantt_chart[I][0] = processes[process_index].process_id;

        if (processes[process_index].remaining_time <= q)
        {
            current_time += processes[process_index].remaining_time;
            processes[process_index].remaining_time = 0;
            processes[process_index].completion_time = current_time;

            processes[process_index].turn_around_time = processes[process_index].completion_time - processes[process_index].arrival_time;
            processes[process_index].waiting_time = processes[process_index].turn_around_time - processes[process_index].burst_time;

            completed_processes++;
        }
        else
        {
            processes[process_index].remaining_time -= q;
            current_time += q;
        }

        gantt_chart[I][1] = current_time;
        I++;

        // Add new processes that have arrived up to the current time
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
            queue[rear++] = process_index;
        }

        for (int i = front; i < rear; i++)
        {
            queue[i - 1] = queue[i];
        }
        front--; rear--;
    }
}

float calculate_average_turnaround_time()
{
    int total_turnaround_time = 0;

    // Calculate the sum of all turnaround times
    for (int i = 0; i < n; i++)
        total_turnaround_time += processes[i].turn_around_time;

    return (float)total_turnaround_time / n;    // Return the average turnaround time
}

float calculate_average_waiting_time() 
{
    int total_waiting_time = 0;

    // Calculate the sum of all waiting times
    for (int i = 0; i < n; i++)
        total_waiting_time += processes[i].waiting_time;

    return (float)total_waiting_time / n;   // Return the average waiting time
}

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
}       // Print the Gantt chart

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

int main()
{
    // Input the number of processes
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

    round_robin_scheduling();           // Perform the Round Robin Scheduling algorithm and calculate completion time, turnaround time, and waiting time for each process

    print_gantt_chart();        // Print the Gantt chart
    
    print_resultant_table();    // Print the resultant table with process details

    // Print the average turnaround time and waiting time
    printf("\nAverage Turnaround Time: %f\n", calculate_average_turnaround_time());
    printf("Average Waiting Time: %f\n", calculate_average_waiting_time());


    return 0;
}
