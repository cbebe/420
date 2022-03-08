#!/bin/sh

# Remove symlink
rm src/scheme.c
cp $1 src/scheme.c
