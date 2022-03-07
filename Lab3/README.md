# Lab 3

In this experiment, we only change the `scheme*.c` file, using different scheduling policies to find the optimal solution.

## Scheduling Policy naming convention

```
scheme<GAUSSIAN SCHEDULING><JORDAN SCHEDULING>.c
```

| Policy             | Prefix |
| ------------------ | ------ |
| Static scheduling  | `s`    |
| Dynamic scheduling | `d`    |
| Guided scheduling  | `g`    |

Example: Dynamic Gaussian with Guided Jordan - `schemedg.c` will be linked to `maindg` executable
