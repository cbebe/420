#!/bin/sh

# Use no-color because it will be in a file
gcc -O3 -DNO_COLOR devkit/speedup.c -o speedup -lm