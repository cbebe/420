---
title: ECE 420 Lab 3 Report
subtitle: Winter 2022
fontsize: 12pt
geometry: margin=0.75in
author: Charles Ancheta, Patricia Zafra
---

# Description of Implementation

Our implementation does not differ much from the given serial example, which is the goal of using OpenMP. For the Gaussian elimination, we were able to parallelize the pivoting and elimination steps. For the Jordan elimination step, we parallelized the elimination for each row.

### Methods of Parallelization

### Testing Different Scheduling Schemes

In order to determine which scheduling schemes allowed for the most optimized results, we created nine different schemes for every possible combination of scheduling policies for the Gaussian and Jordan elimination algorithms.
For example, `schemeds.c` executes the Gaussian elimination algorithm using dynamic scheduling and the Jordan elimination algorithm using static scheduling.
By testing different combinations of scheduling policies, we were able to find that using a scheduling scheme of `guided` for Gaussian elimination and `static` for Jordan elimination gave us the fastest run time.

# Performance Discussion
