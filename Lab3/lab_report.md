---
title: ECE 420 Lab 3 Report
subtitle: Winter 2022
fontsize: 12pt
geometry: margin=0.75in
author: Charles Ancheta, Patricia Zafra
---

# Description of Implementation

Our implementation does not differ much from the given serial example, which is the goal of using OpenMP.
For the Gaussian elimination, we were able to parallelize the pivoting and elimination steps.
However, each row still had to be done serially.
For the Jordan elimination step, we parallelized the variable elimination for each row.
We tried making a local copy for each row before modifying it to prevent false sharing between threads but we realized that the overhead of copying is not worth it for false sharing prevention. <!-- Not sure about this, we haven't actually tried -->

### Methods of Parallelization

We experimented with several methods of parallelization in order to improve the performance of both elimination algorithms. First, we used the parallel directive only once in the main function, which then inside performs both elimination algorithms using work-sharing constructs. We did this so that the teams of threads launched by the directive will be reused to decrease the overhead from forks and implicit joins.

### Testing Different Scheduling Schemes

In order to determine which scheduling policies allowed for the most optimized results, we created nine different schemes for every possible combination of scheduling policies for the Gaussian and Jordan elimination algorithms.
For example, `schemeds.c` executes the Gaussian elimination algorithm using dynamic scheduling and the Jordan elimination algorithm using static scheduling.

# Performance Discussion

Using data of size 1000, by testing different combinations of scheduling policies on different numbers of threads, we were able to find that using a scheduling policy of `static` for Gaussian elimination and `static` for Jordan elimination running on 4 threads gave us the fastest run time.

Below is a table showing the runtimes of various schemes running with different numbers of threads. Some schemes are omitted from the table as the results were similar to other schemes:

| # of Threads | Baseline (Serial) | Dynamic Gaussian/Guided Jordan | Static Gaussian/Dynamic Jordan | Static Gaussian/Static Jordan |
| ------------ | ----------------- | ------------------------------ | ------------------------------ | ----------------------------- |
| 1            | 0.229619          | 0.237278                       | 0.245057                       | 0.231731                      |
| 4            | --                | 0.155944                       | 0.126496                       | 0.083097                      |
| 10           | --                | 0.229466                       | 0.198058                       | 0.182534                      |

The most optimized runtime we achieved by running these different schemes was 0.083097 s, resulting in a speedup of:
$$S = 0.229619/0.083097 = 2.763$$

We found that running on a number of threads greater than 4 began to slow down our schemes, which is likely due to the overhead from spawning threads when parallelizing.
