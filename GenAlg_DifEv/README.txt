=============================README====================================
	PROJECT 3: Genetic Algorithm and Differential Evolution

Author: Holly Strauch
CS 471 
Project 3
May 3, 2019

This program uses Genetic Algorithm and Differential Evolution to optimize
18 different functions. Genetic Algorithm is run with either tournament 
select or roulette select, and Differential Evolution is run with one of 
10 DE strategies
==============================RUN PROJECT==============================
Input files are set to run GA with roulette selection, 5 experiements
per function.  File can be changed to run other versions as specifiec
below in 'Input.'

Run program on any machine with gcc:

	> gcc -o main.exe main.c algInput.c deAlg.c ftns.c gAlg.c input.c pop.c
util.c MT/mt19937ar.c

If program will not compile try replacing gcc with cc

IF INPUT FILE IS NOT FOUND:
	replace the file string in main.c, deAlg.c, or gAlg.c
	with the path to file


===============================INPUT===================================

ftnInput.txt File:
    int <generations>		//Number of generations to run
    int <popsize>		//Size of the population
    double <crRate>		//Crossover rate, .8-.95
    double <mRate>		//Mutation rate, .005-.001
    double <mRange>		//Mutation range, .1
    double <mPrecision>		//Mutation precision, 1-5
    double <er>			//Elitism Rate
    double <F>			//DE scaling factor 0<F<=2
    double <L>			//Second DE scaling factor 0<L<=2
    int <dim>			//Dimension of vectors
    int <numFtns>		//Number of functions 
    double <function number> <function lower bound> <function upper bound>
    .
    .	
 //The functions and their bounds can be set using the followin lines:
	1.0 -512.0 512.0
	2.0 -100.0 100.0
	3.0 -100.0 100.0
	4.0 -30.0 30.0
	5.0 -500.0 500.0
	6.0 -30.0 30.0
	7.0 -30.0 30.0
	8.0 -32.0 32.0
	9.0 -32.0 32.0
	10.0 -500.0 500.0
	11.0 -500.0 500.0
	12.0 -100.0 100.0
	13.0 0.0 3.1415926
	14.0 -30.0 30.0
	15.0 -100.0 100.0
	16.0 -10.0 100.0
	17.0 -100.0 100.0
	18.0 -100.0 100.0
    
    
The number of sets of ftn input must correspond with the number of functions.




-----------------------------------------------------------------------------
algInput File:
	int <alg>		//1 for GA, 2 for DE
    	int <strategy>		//1-10, specifies a DE strategy
    	int <select>		//1 for tournament, 2 for roulette. Selection method for GA
    	int <experiments>	//The number of times to run each algorithm 
					on all functions
================================OUTPUT==================================

Each algorithm will produce a CSV file with its name.  The CSV file will
show all the best results from each generation, as well as runtime and 
the number of times the original function was called.

=====================================================================
This program uses Mersenne Twister:    
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          
   Copyright (C) 2005, Mutsuo Saito,
   All rights reserved.                          

