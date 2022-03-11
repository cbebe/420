#!/bin/sh

[ "$1" = "" ] && printf "USAGE: $0 <BEST_SCHEME_SOURCE>\n" && exit 1

file=$(realpath $1)

# It's okay to keep the symlink 
# because zip will grab the referenced file before archiving
rm -f src/scheme.c && cd src && ln -sr $file scheme.c && cd ..
