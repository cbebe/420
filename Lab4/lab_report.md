---
title: ECE 420 Lab 4 Report
subtitle: Winter 2022
fontsize: 12pt
geometry: margin=0.75in
author: Charles Ancheta, Patricia Zafra
---

# Background

In this lab, we were tasked with implementing a distributed version of the PageRank algorithm using MPI. An iterative approach was used to calculate the probabilities and stop once the algorithm reaches the following condition provided in the lab manual:
$$\frac{||\vec{r}(t+1) - \vec{r}(t)||}{||\vec{r}(t)||} < 1 \times 10^{-5}\enspace(4)$$
Using the iterative approach, we were able to parallelize the PageRank algorithm to distribute the workload amongst several machines and nodes to achieve optimal performance.

# Description of Implementation

In order to distribute the tasks, we first initialized variables that are local to each process. These variables include a buffer to hold the probabilities at the end of the calculations, two vectors that calculate the contribution of each process as per Equation (3), and start and end indices for each process. The division of work is done by calculating a chunk size using:
$$chunk size = \frac{N_{nodes} + N_{padding zeros}}{N_{processes}}$$

Note that we added padding zeros to the vector in the case where the number of nodes is not perfectly divisible by the number of processes.

Each process will do a $chunksize$ amount of work and its start and end indices are calculated using their rank as follows:
$$start = chunksize \times rank_{process}$$
$$end = chunksize \times ({rank_{process} + 1})$$

After dividing the work between processes, each process does its contribution of the calculation as described by Equations (1) and (3) provided in the lab manual, and the calculation stops once we reach the condition provided by Equation (4). We then used `MPI_Allgather` to gather the calculations done by each process on its local vector. We used `MPI_Allgather` because it allows each process to gather the data from all processes. The buffer that contains the contributions of each process is then copied to the global vector which stores the final result.

# Performance Discussion

### Questions

1.  For small problem sizes, the single machine setup will perform better than a multiple machine setup where there would be additional communication overhead. However as the problem size increases, the program will begin to benefit from having the work be distributed amongst machines, and the communication overhead will be less of an issue. Also, as the number of processes on a single machine increases, the efficiency of the program significantly decreases due to overhead from coordination between processes. We didn't really see this issue in our program, but given that we only ran up to 4 processes, this wasn't really much of an issue. This is also less of an issue with multiple machines, where the performance varies depending on the problem size along with the number of machines running. Therefore, a large problem (>1112 nodes) running on many processes would perform better on a multiple machine setup.

2.  The best number of processes to be used with our program is 4 on all problem sizes. This might not be the case for problem sizes smaller than 1112 nodes where the communication overhead overtakes the computational load. This makes our program have coarse granularity, where each process does a relatively large chunk of work. Increasing the number of processes beyond 4 could slow down our problem where we could have greater communication overhead or excess idle time of processes.

3.  Since our graph is represented by a vector whose elements may or may not refer to other elements in the vector, we did not have to do any matrix partitioning. We simply divided the data linearly into $p$ parts and distributed them among the $p$ processes.

4.  We used `MPI_Allgather` to collect the entire vector after every iteration since it's required to compute the relative error. We could have used something like `MPI_Reduce` in the special case the graph is partitioned into "islands" that do not connect to other partitions in the graph to remove the communication overhead of sharing the whole array between the processes. However, that might not work for a graph that is a single island. The advantage of the communication mechanism that we used is that it handles all cases and shapes of the graph.

# Appendix

## Experiment Results Tables

### Single Machine

No. of processes: 1

| Nodes | Serial | Parallel | Speedup |
| ----- | ------ | -------- | ------- |
| 1112  | 0.0222 | 0.0171   | 1.2996  |
| 5424  | 0.3234 | 0.1862   | 1.7371  |
| 10000 | 0.9719 | 0.4972   | 1.9546  |

No. of processes: 2

| Nodes | Serial | Parallel | Speedup |
| ----- | ------ | -------- | ------- |
| 1112  | 0.0223 | 0.0171   | 1.3041  |
| 5424  | 0.3234 | 0.1866   | 1.7332  |
| 10000 | 0.9721 | 0.4977   | 1.9534  |

No. of processes: 3

| Nodes | Serial | Parallel | Speedup |
| ----- | ------ | -------- | ------- |
| 1112  | 0.0223 | 0.0171   | 1.3062  |
| 5424  | 0.3234 | 0.1847   | 1.7513  |
| 10000 | 0.9719 | 0.4896   | 1.9850  |

No. of processes: 4

| Nodes | Serial | Parallel | Speedup |
| ----- | ------ | -------- | ------- |
| 1112  | 0.0223 | 0.0169   | 1.3205  |
| 5424  | 0.3237 | 0.1805   | 1.7936  |
| 10000 | 0.9722 | 0.4777   | 2.0354  |

### Multiple Machines

No. of processes: 2

| Nodes | Serial | Parallel | Speedup |
| ----- | ------ | -------- | ------- |
| 1112  | 0.0224 | 0.0169   | 1.3213  |
| 5424  | 0.3237 | 0.1809   | 1.7891  |
| 10000 | 0.9726 | 0.4791   | 2.0300  |

No. of processes: 3

| Nodes | Serial | Parallel | Speedup |
| ----- | ------ | -------- | ------- |
| 1112  | 0.0224 | 0.0169   | 1.3225  |
| 5424  | 0.3237 | 0.1792   | 1.8059  |
| 10000 | 0.9725 | 0.4726   | 2.0576  |

No. of processes: 4

| Nodes | Serial | Parallel | Speedup |
| ----- | ------ | -------- | ------- |
| 1112  | 0.0224 | 0.0168   | 1.3305  |
| 5424  | 0.3236 | 0.1768   | 1.8308  |
| 10000 | 0.9726 | 0.4635   | 2.0986  |
