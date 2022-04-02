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

3.  How did you partition your data? How did you partition the graph among the processes?

4.  What communication mechanisms are used in your program? What is the advantage of your specific choices in terms of communication overhead and running time?

# Appendix

## Experiment Results Tables

Nodes ( Single / Multiple )

|              | Number of processes | 1      | 2               | 3               | 4               |
| ------------ | ------------------- | ------ | --------------- | --------------- | --------------- |
| Problem size |                     |        |                 |                 |                 |
| 1112         |                     | 1.1559 | 1.3589 / 1.2574 | 1.3507 / 1.3360 | 1.4081 / 1.4186 |
| 5424         |                     | 0.9970 | 1.4044 / 1.2705 | 1.5828 / 1.6546 | 1.7763 / 1.8670 |
| 10000        |                     | 0.9984 | 1.4604 / 1.3078 | 1.6461 / 1.7766 | 1.9197 / 2.0606 |
