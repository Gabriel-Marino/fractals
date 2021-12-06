#!/bin/bash

    gcc -O3 $1 -static -lgsl -lgslcblas -lm -o fractal.out #2> warns.txt
    time ./fractal.out

    # rm dat/*
    rm *.out

# kill -9 $PPID
