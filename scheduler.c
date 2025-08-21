#include <stdio.h>
#include <limits.h>


struct Process {
    int id, at, bt;
    int ct, tat, wt;
    int done;
};


void printResults(struct Process p[], int n, float totalWT, float totalTAT){
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT /n);
}


void sjfNonPreemptive(struct Process p[], int n){
    int completed = 0, currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    //reset done flags
    for(int i = 0; i < n; i++){
        p[i].done = 0;
    }

    printf("\n--- SJF (Non-Preemptive) --\n");
    printf("Gantt Chart:\n");

    while(completed < n) {
        int idx = -1; //index of the best candidate to run now
        int minBT = INT_MAX;

        //find process with smallest BT among arrived & not done
        for(int i = 0; i < n; i++){
            if(!p[i].done && p[i].at <= currentTime){
                if (p[i].bt < minBT){
                    minBT = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx == -1){
            // no process is ready, CPU idle
            printf("| IDLE (%d) ", currentTime + 1);
            currentTime++;
            continue;
        }

        currentTime += p[idx].bt;
        p[idx].ct = currentTime;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = 1;
        completed++;

        totalWT += p[idx].wt;
        totalTAT += p[idx].tat;

        printf("| P%d (%d) ", p[idx].id, p[idx].ct);

        }

        printf("|\n");

        printResults(p, n, totalWT, totalTAT);
}

void fcfs(struct Process p[], int n) {
    // Sort by Arrival Time (bubble sort)
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            if(p[j].at > p[j+1].at){
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    printf("\n--- FCFS ---\n");
    printf("Gantt Chart:\n");
    for(int i = 0; i < n; i++){
        if(currentTime < p[i].at){
            printf("| IDLE (%d) ", p[i].at);
            currentTime = p[i].at; // CPU Idle
        }

        currentTime += p[i].bt;
        p[i].ct = currentTime;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;

        printf("| P%d (%d) ", p[i].id, p[i].ct);
    }
    printf("|\n");

    printResults(p, n, totalWT, totalTAT);
}

int main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++){
        processes[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
    }

    sjfNonPreemptive(processes, n);
    fcfs(processes, n);
    return 0;
}
