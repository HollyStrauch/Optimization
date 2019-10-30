=============================README====================================
	PROJECT 2: Random Walk, Local Search, Iterative Local Search

Author: Holly Strauch
CS 471 
Project 2
4/21/2019

This program will ask user if they would like to run a Random Walk, Local 
Search, or Iterative local search. The algorithm will be run on all
functions and dimensions specified in the input file. Each algorithm
tries to find the best result for each function.
================================NOTES==================================
Alpha values are set to obtain more optimal results than if they were all
set to .11, but still achieve reasonable runtimes. For faster runtime, 
set all alpha values to .11 in the input file.
==============================RUN PROJECT==============================

Run program on any machine with gcc:

	> gcc -o main.exe main.c ftns.c util.c ftnInput.c MT/mt19937ar.c searchAlgs.c
	> .\main.exe

If program will not compile try replacing gcc with cc

IF INPUT FILE IS NOT FOUND:
	replace the file string in main() with the path to input.txt


===============================INPUT===================================

Program reads from a file with the following format:

int <iterations>
int <trials>
int <number of dimensions>
int <dimension.1>...<dimension.n>
int <number of functions>
 //ftn input:
double <function number> <function lower bound> <function upper bound> <alpha>
.
.
.

The number of sets of ftn input must correspond with the number of functions.

================================OUTPUT==================================

Each algorithm will produce a CSV file with its name.  The CSV file will
contain all the best results obtained while running the algorithm.  Random
Walk and Iterative Local Search will have 30 values per function per 
dimension, while Local Search as a single output.
Local Search will 

