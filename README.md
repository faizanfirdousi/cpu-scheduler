# CPU Scheduler Implementation

This is a C program that implements various CPU scheduling algorithms commonly studied in Operating Systems. The program provides a menu-driven interface to demonstrate the working of different scheduling algorithms with visualization through Gantt charts.

## Features

- Implementation of 4 CPU scheduling algorithms:
  1. First Come First Serve (FCFS)
  2. Shortest Job First (Non-Preemptive)
  3. Shortest Job First (Preemptive) / Shortest Remaining Time First (SRTF)
  4. Round Robin (with configurable time quantum)

- For each algorithm, the program displays:
  - Gantt Chart visualization
  - Process completion details in tabular format
  - Average Waiting Time
  - Average Turnaround Time

## Compilation and Usage

To compile the program:
```bash
gcc scheduler.c -o scheduler
```

To run the program:
```bash
./scheduler
```

## Input Format

1. First, enter the number of processes
2. For each process, enter:
   - Arrival Time (AT)
   - Burst Time (BT)
3. Choose the scheduling algorithm from the menu
4. For Round Robin, additionally enter the time quantum

## Output Format

For each scheduling algorithm, the program shows:

1. Gantt Chart showing the execution sequence
2. Table with the following details for each process:
   - Process ID
   - Arrival Time (AT)
   - Burst Time (BT)
   - Completion Time (CT)
   - Turnaround Time (TAT)
   - Waiting Time (WT)
3. Average Waiting Time
4. Average Turnaround Time

## Terms Used

- **Arrival Time (AT)**: Time at which the process enters the ready queue
- **Burst Time (BT)**: Total CPU time required by the process
- **Completion Time (CT)**: Time at which process completes execution
- **Turnaround Time (TAT)**: Total time taken from arrival to completion (CT - AT)
- **Waiting Time (WT)**: Total time spent waiting in ready queue (TAT - BT)

## Algorithms Implemented

1. **First Come First Serve (FCFS)**
   - Non-preemptive algorithm
   - Processes are executed in order of arrival

2. **Shortest Job First (Non-Preemptive)**
   - Non-preemptive algorithm
   - Process with shortest burst time is selected for execution
   - Process runs to completion once selected

3. **Shortest Job First (Preemptive) / SRTF**
   - Preemptive version of SJF
   - Current process can be preempted by a new process with shorter remaining time
   - Also known as Shortest Remaining Time First (SRTF)

4. **Round Robin**
   - Preemptive algorithm
   - Each process gets CPU for a fixed time quantum
   - After time quantum expires, process is moved to end of ready queue
   - Provides fair CPU sharing and good response time
