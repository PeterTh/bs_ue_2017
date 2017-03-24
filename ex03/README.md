# Exercise Sheet 3

In this exercise sheet you will schedule the execution of different processes on paper. Different scheduling techniques will be analized. 

## Task 1

| Process | Arrival Time | Service Time | Priority |
|---------|--------------|--------------|----------|
| A       | 0            | 3            | 1        |
| B       | 2            | 6            | 1        |
| C       | 4            | 4            | 2        |
| D       | 6            | 5            | 2        |
| E       | 8            | 2            | 3        |

The previous table describes the arrival time, service time and priority of 5 different processes. This task consists in:
* creating a GANTT chart describing how these processes are assigned to the CPU according to different scheduling algorithms, and 
* computing the *turnaround time*, *response time* and *throughput* in each of these cases. 

The considered scheduling algorithms are:
1. FCFS (First Come First Served)
2. SPN (Shortest Process Next)
3. SRT (Shortest Remaining Time Next)
4. Round Robin (quantum = 1)
5. Round Robin (quantum = 4)
6. Highest Priority First with preemption
7. Highest Priority First without preemption

Include the GANTT charts and the requested data into the file you submit via OLAT. 
