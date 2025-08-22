#include <stdio.h>
#include <limits.h>

/* Process Structure
 * Represents a process with all necessary attributes for scheduling
 * id: Process identifier
 * at: Arrival Time - when process enters the ready queue
 * bt: Burst Time - total CPU time needed
 * ct: Completion Time - when process finishes execution
 * tat: Turnaround Time - total time from arrival to completion
 * wt: Waiting Time - time spent waiting in ready queue
 * done: Flag to track if process has completed execution
 */
struct Process {
    int id, at, bt;
    int ct, tat, wt;
    int done;
};

/* Print scheduling results in tabular format
 * Parameters:
 * p[] - array of processes
 * n - total number of processes
 * totalWT - sum of all waiting times
 * totalTAT - sum of all turnaround times
 */
void printResults(struct Process p[], int n, float totalWT, float totalTAT){
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT /n);
}

/* Shortest Job First (Non-Preemptive) Scheduling Algorithm
 * Selects the process with smallest burst time among arrived processes
 * Parameters:
 * p[] - array of processes
 * n - total number of processes
 */
void sjfNonPreemptive(struct Process p[], int n){
    int completed = 0;         // Count of completed processes
    int currentTime = 0;       // Current time in simulation
    float totalWT = 0;         // Sum of waiting times
    float totalTAT = 0;        // Sum of turnaround times

    // Initialize all processes as not completed
    for(int i = 0; i < n; i++){
        p[i].done = 0;
    }

    printf("\n--- SJF (Non-Preemptive) --\n");
    printf("Gantt Chart:\n");

    // Continue until all processes are completed
    while(completed < n) {
        int idx = -1;          // Index of process to be executed next
        int minBT = INT_MAX;   // Minimum burst time found so far

        // Find process with minimum burst time among arrived processes
        for(int i = 0; i < n; i++){
            if(!p[i].done && p[i].at <= currentTime){
                if (p[i].bt < minBT){
                    minBT = p[i].bt;
                    idx = i;
                }
            }
        }

        // If no process is available, CPU remains idle
        if (idx == -1){
            printf("| IDLE (%d) ", currentTime + 1);
            currentTime++;
            continue;
        }

        // Execute the selected process
        currentTime += p[idx].bt;
        // Calculate completion, turnaround and waiting times
        p[idx].ct = currentTime;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = 1;
        completed++;

        // Update total statistics
        totalWT += p[idx].wt;
        totalTAT += p[idx].tat;

        // Print Gantt chart entry
        printf("| P%d (%d) ", p[idx].id, p[idx].ct);
    }

    printf("|\n");
    printResults(p, n, totalWT, totalTAT);
}

/* First Come First Serve (FCFS) Scheduling Algorithm
 * Executes processes in order of arrival
 * Parameters:
 * p[] - array of processes
 * n - total number of processes
 */
void fcfs(struct Process p[], int n) {
    // Sort processes by arrival time using bubble sort
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            if(p[j].at > p[j+1].at){
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int currentTime = 0;       // Current time in simulation
    float totalWT = 0;         // Sum of waiting times
    float totalTAT = 0;        // Sum of turnaround times

    printf("\n--- FCFS ---\n");
    printf("Gantt Chart:\n");

    // Process each job in arrival order
    for(int i = 0; i < n; i++){
        // If CPU is idle, update current time
        if(currentTime < p[i].at){
            printf("| IDLE (%d) ", p[i].at);
            currentTime = p[i].at;
        }

        // Execute current process and calculate times
        currentTime += p[i].bt;
        p[i].ct = currentTime;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        // Update total statistics
        totalWT += p[i].wt;
        totalTAT += p[i].tat;

        // Print Gantt chart entry
        printf("| P%d (%d) ", p[i].id, p[i].ct);
    }
    printf("|\n");

    printResults(p, n, totalWT, totalTAT);
}

/* Shortest Job First (Preemptive) Scheduling Algorithm (SRTF)
 * Selects the process with the smallest remaining burst time among arrived
 * Parameters:
 * p[] - array of processes
 * n - total number of processes
 */

void sjfPreemptive(struct Process p[], int n){
    int completed = 0;
    int currentTime = 0;
    float totalWT = 0;
    float totalTAT = 0;

    int remainingBT[n]; //Array to track remaining burst times
    for(int i = 0; i < n; i++){
        remainingBT[i] = p[i].bt;
        p[i].done = 0;
    }

    printf("\n--- SJF (preemptive / SRTF) ---\n");
    printf("Gantt Chart:\n");

    int lastProcess = -1; //Track last executed process ( for Gantt chart)

    // Continue until all processes are completed
    while(completed < n){
        int idx = -1;
        int minBT= INT_MAX;

        for(int i = 0; i < n; i++){
            if(!p[i].done && p[i].at <= currentTime && remainingBT[i] > 0){
                if(remainingBT[i] < minBT){
                    minBT = remainingBT[i];
                    idx = i;
                }
            }
        }

        // If not process has arrived yet, CPU idle
        if(idx == -1){
            if(lastProcess != -2){
                printf(" | IDLE (%d) ", currentTime + 1);
                lastProcess = -2;
            }

            currentTime++;
            continue;
        }

        // If process changes, print Gantt chart entry
        if(lastProcess != idx){
            printf("| P%d (%d) ",p[idx].id, currentTime + 1);
            lastProcess = idx;
        }

        // Execute process for 1 unit
        remainingBT[idx]--;
        currentTime++;

        //If Process completes
        if(remainingBT[idx] == 0){
            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].done = 1;
            completed++;

            totalWT += p[idx].wt;
            totalTAT += p[idx].tat;
        }
    }

    printf("|\n");
    printResults(p, n, totalWT, totalTAT);
}

/* Main function
 * Handles user input and calls scheduling algorithms
 */
int main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input process details
    struct Process processes[n];
    for (int i = 0; i < n; i++){
        processes[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
    }

    // Execute both scheduling algorithms
    sjfNonPreemptive(processes, n);
    fcfs(processes, n);
    return 0;
}
