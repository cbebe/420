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

Each process will do a _chunksize_ amount of work and its start and end indices are calculated using their rank as follows:
$$start = chunksize \times rank_{process}$$
$$end = chunksize \times ({rank_{process} + 1})$$

After dividing the work between processes, each process does its contribution of the calculation as described by Equations (1) and (3) provided in the lab manual, and the calculation stops once we reach the condition provided by Equation (4). We then used `MPI_Allgather` to gather the calculations done by each process on its local vector. We used `MPI_Allgather` because it allows each process to gather the data from all processes. The buffer that contains the contributions of each process is then copied to the global vector which stores the final result.

# Performance Discussion

### Questions

1.  Is the performance of your program better on a single machine setup or on a multiple machines setup? What is the reason?

    The program runs better on multiple machines. This is likely due to a better distributed workload amongst the machines. On a single machine, the performance of the program will decrease as the number of processes is increased, due to the context switching between processes. When running a relatively large program on multiple machines, the workload is much more balanced and is thus more performant.

2.  What is the best number of processes that should be used in your program, respective to the different problem sizes? How does the granularity affect the running time of your program and why?

    The best number of processes to be used with our program is 4 on all problem sizes. This might not be the case for problem sizes smaller than 1112 nodes where the communication overhead overtakes the computational load.

3.  How did you partition your data? How did you partition the graph among the processes?

    Since our graph is represented by a vector whose elements may or may not refer to other elements in the vector, we did not have to do any matrix partitioning. We simply divided the data linearly into $p$ parts and distributed them among the $p$ processes.

4.  What communication mechanisms are used in your program? What is the advantage of your specific choices in terms of communication overhead and running time?

    We used `MPI_Allgather` to collect the entire vector after every iteration since it's required to compute the relative error. We could have used something like `MPI_Reduce` in the special case the graph is partitioned into "islands" that do not connect to other partitions in the graph to remove the communication overhead of sharing the whole array between the processes. However, that might not work for a graph that is a single island. The advantage of the communication mechanism that we used is that it handles all cases and shapes of the graph.

# Appendix

## Experiment Results Tables

### Single Machine

No. of processes: 1

| Nodes | Serial | Parallel | Speedup |
| ----- | ------ | -------- | ------- |
| 1112  | 0.0169 | 0.0171   | 0.9855  |
| 5424  | 0.3240 | 0.3271   | 0.9904  |
| 10000 | 0.9752 | 0.9708   | 1.0045  |

No. of processes: 2

| Nodes | Serial | Parallel | Speedup |
| ----- | ------ | -------- | ------- |
| 1112  | 0.0190 | 0.0139   | 1.3628  |
| 5424  | 0.3232 | 0.1772   | 1.8240  |
| 10000 | 0.9762 | 0.5224   | 1.8688  |

No. of processes: 3

| Nodes | Serial | Parallel | Speedup |
| ----- | ------ | -------- | ------- |
| 1112  | 0.0175 | 0.0084   | 2.0917  |
| 5424  | 0.3259 | 0.1539   | 2.1178  |
| 10000 | 0.9847 | 0.3823   | 2.5759  |

No. of processes: 4

| Nodes | Serial | Parallel | Speedup |
| ----- | ------ | -------- | ------- |
| 1112  | 0.0182 | 0.0079   | 2.2873  |
| 5424  | 0.3237 | 0.1182   | 2.7398  |
| 10000 | 0.9776 | 0.2744   | 3.5629  |

### Multiple Machines

No. of processes: 2

| Nodes | Serial | Parallel | Speedup |
| ----- | ------ | -------- | ------- |
| 1112  | 0.0229 | 0.0166   | 1.3760  |
| 5424  | 0.3230 | 0.1883   | 1.7159  |
| 10000 | 0.9685 | 0.5061   | 1.9137  |

No. of processes: 3

| Nodes | Serial | Parallel | Speedup |
| ----- | ------ | -------- | ------- |
| 1112  | 0.0229 | 0.0169   | 1.3553  |
| 5424  | 0.3235 | 0.1567   | 2.0645  |
| 10000 | 0.9737 | 0.3626   | 2.6855  |

No. of processes: 4

| Nodes | Serial | Parallel | Speedup |
| ----- | ------ | -------- | ------- |
| 1112  | 0.0228 | 0.0142   | 1.6078  |
| 5424  | 0.3233 | 0.1124   | 2.8762  |
| 10000 | 0.9703 | 0.2688   | 3.6098  |
