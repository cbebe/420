#!/bin/sh

[ "$1" = "" ] && printf "USAGE: $0 <BEST_SCHEME_SOURCE>\n" && exit 1

# Remove symlink and replace with an actual file
rm -f src/scheme.c && cp $1 src/scheme.c
