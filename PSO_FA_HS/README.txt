=============================README====================================
	PROJECT 4: Particle Swarm Optimization, Firefly Algorithm,
			and Harmony Search

Author: Holly Strauch
CS 471 
Project 4
May 19, 2019

This program uses Particle Swarm Optimization (PSO), Firefly Algorithm (FA), and 
Harmony Search (HS) to attempt to optimize the fitness values of 18 different
functions. The equations that the algorithms are run on take vectors as inputs
and the populations are scalable in dimension and size. 

All program files are found in the SRC folder. The main.c file and general use
files are directly within SRC, while the code for the algorithms are 
split into their respective folders. The Results folder holds the result summary
form. The remaining files in the primary folder hold 
the doxygen reference manual and report on the findings.

Due to the size of the files of raw output data, the files for the generations 
and the output fitness values are being submitted separately. The results are from runs
 of the algorithms of population size 500, 500 iterations, and dimensions of 30 
==============================RUN PROJECT==============================
ftnInput file is set to a population size of 500, 500 iterations, and dimension 
of 30.  The constants are set to .8, .8, .8 and are meant to be run with PSO.
The file can be changed to run for other algorithms as specified below in 'Input.'
The flag -O3 has been used due to the slow speeds of some of the algorithms.

Run program on any machine with gcc:

	gcc -O3 -o main.exe main.c Util.c Output.c Input.c Ftns.c FA/FA.c FA/FApop.c MT/mt19937ar.c HS/HS.c HS/HSpop.c PSO/PSO.c PSO/PSOpopulation.c

If program will not compile try replacing gcc with cc

IF INPUT FILE IS NOT FOUND or code is being run in an IDE:

	replace the file string in main.c with the full path to file


===============================INPUT===================================
The input file is generalized to be used for each algorithm. The constant value
inputs correspond to each algorithm as follows:

PSO
C1 : Personal best factor, (0 , 2]
C2 : Global best factor, (0 , 2]
C3 : K dampening factor [.8 , 1.2]

FA
C1 : alpha .5
C2 : beta  .2
C3 : gamma .00001

HS
C1 : HMCR [.7 , .95]
C2 : PAR [.1 , .5]
C3 : bw .2

ftnInput.txt File:
    int <experiments>		//Number of times the algorithm will be run on each function
    int <popsize>		//Size of the population
    int <itrs>			//The number of iterations the algorithm will run on the population
    int <dim>			//Dimension of vectors
    double <C1>			//The first constant value
    double <C2>			//The second constant value
    double <C3>			//The third constant value
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

================================OUTPUT==================================

Each algorithm will produce a CSV file with its name.  The CSV file will
show the best fitness from each iteration, runtime, the number of times
 the objective function was called, and the worst fitness each iteration.

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

