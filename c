#!/bin/bash

v=$1
f=${v::-2}

clang -std=c11 -Wall -Wextra -Wpedantic -fsanitize=address -c $f.c -o ./obj/$f.o
clang ./obj/$f.o -fsanitize=address -o ./bin/c_$f
