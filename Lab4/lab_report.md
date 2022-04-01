---
title: ECE 420 Lab 4 Report
subtitle: Winter 2022
fontsize: 12pt
geometry: margin=0.75in
author: Charles Ancheta, Patricia Zafra
---

# Description of Implementation

# Performance Discussion

### Questions

1.  Is the performance of your program better on a single machine setup or on a multiple machines setup? What is the reason?

    The program runs better on multiple machines. This is likely due to a better distributed workload amongst the machines. On a single machine, the performance of the program will decrease as the number of processes is increased, due to the context switching between processes. When running a relatively large program on multiple machines, the workload is much more balanced and is thus more performant.

2.  What is the best number of processes that should be used in your program, respective to the different problem sizes? How does the granularity affect the running time of your program and why?

3.  How did you partition your data? How did you partition the graph among the processes?

4.  What communication mechanisms are used in your program? What is the advantage of your specific choices in terms of communication overhead and running time?

Nodes ( Single / Multiple )

|              | Number of processes | 1      | 2               | 3               | 4               |
| ------------ | ------------------- | ------ | --------------- | --------------- | --------------- |
| Problem size |                     |        |                 |                 |                 |
| 1112         |                     | 1.1559 | 1.3589 / 1.2574 | 1.3507 / 1.3360 | 1.4081 / 1.4186 |
| 5424         |                     | 0.9970 | 1.4044 / 1.2705 | 1.5828 / 1.6546 | 1.7763 / 1.8670 |
| 10000        |                     | 0.9984 | 1.4604 / 1.3078 | 1.6461 / 1.7766 | 1.9197 / 2.0606 |

I do not know what to make of these numbers

##
