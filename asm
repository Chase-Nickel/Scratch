#!/bin/bash

v=$1
f=${v::-2}

# https://courses.cs.washington.edu/courses/cse469/18wi/Materials/arm64.pdf
as -g --warn --fatal-warnings ./$f.s -o ./obj/$f.o
ld -g ./obj/$f.o -o ./bin/asm_$f

