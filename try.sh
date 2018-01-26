#!/bin/sh -eu

options=$(cut -s -d= -f1 uncrustify.base)
srcdir=$1

# Initialize with a base set of options.
best=1000000
cp -f uncrustify.base uncrustify.best

for pass in $(seq 1 10); do
  for opt in $options; do
    echo "Changing option $opt"

    # Copy the best from the last option test.
    cp -f uncrustify.best .uncrustify.prev

    # Pick the best of four tries for each option.
    tries=$(./count "$opt")
    if [ "$tries" -lt 2 ]; then
      continue
    fi
    for try in $(seq 1 "$tries"); do
      # Generate a new config.
      ./permute "$opt" < .uncrustify.prev > .uncrustify
      cp -f .uncrustify .uncrustify.prev

      # Test the config. If uncrustify crashes, try the next option.
      git -C "$srcdir" reset -q --hard
      find "$srcdir" '(' -name '*.c' -or -name '*.h' ')' -exec \
        uncrustify -c .uncrustify -l C -q --no-backup {} + || continue
      stat=$(git -C "$srcdir" diff --minimal --shortstat)
      diff=$(echo "$stat" | cut -d' ' -f5,7 --output-delimiter=+ | bc)

      # Choose the best.
      echo "  try $try diff is $diff (best is $best)"
      if [[ $diff -le $best ]]; then
        cp .uncrustify uncrustify.best
        best=$diff
      fi
    done
  done
done
