=============================README====================================
	PROJECT 5: NEH Algorithm on Flow Shop Functions

Author: Holly Strauch
CS 471 
Project 5
May 31, 2019

This program runs the NEH algorithm on three functions: Flow Shop Scheduling (FSS),
Flow Shop with Blocking (FSB), and Flow Shop with No Wait (FSNW).  It is a 
combinatorial algorithm which attempts to find the ordering n jobs being 
processed in m machines that will results in the minimum amount of total time. 

All program files are found in the SRC folder. The main.c file and general program
files are directly within SRC, while the NEH algorithm code and Taillard data files
are in their own respective folders. The Results folder contains the general results 
for each of the three functions, along with individual PDFs of Gantt Charts made 
from the first file of every category of data file. The remaining files in the primary 
folder are the doxygen reference manual and report on the findings.
==============================RUN PROJECT==============================
The input.txt file must be set to specify whether a single permutation is being tested
or if the entire algorithm is being run, along with which function the algorithm should
be run on. When the algorithm is run, all Data Files will be read from.

The input file is initially set to run NEH on all Data Files using FSS

Functions:
1: Flow Shop Scheduling
2: Flow Shop with Blocking
3: Flow Shop with No Wait


Run program on any machine with gcc:

	gcc -o main.exe main.c Util.c Schedule.c Output.c Input.c FSFtns.c NEH/NEH.c MT/mt19937ar.c

If program will not compile try replacing gcc with cc

IN CASE OF FILE INPUT ERROR:
	"No such file: initInput Algorithm": replace the input.txt file path in main.c
	 with the full file path

	"No Such file: initInput Data" replace the name in Input.c of the fileDataLoc with 
		the full file path ending with "DataFiles\%d.txt"


===============================INPUT===================================
The input.txt file controls if the algorithm is run and which function is being used.
If a permutation is being given to run, the corresponding Data File 


input.txt File:
    int <run Permutation>	//Set to 0 for running the algorithm, 1 for running a permuation
    int <function>		//1 for FSS, 2 for FSB, 3 for FSNW
    int <fileNumber>		//Specifies a file to read from, ONLY used when a permutation is read
    int <permutation>		//A permutation of numbers 1 to n, n = jobs in specified file
 
DataFiles (DO NOT CHANGE):
    int <machines>		//The number of machines
    int <jobs>			//The number of jobs
    int <Processing Time Matrix>//Matrix of size machines X jobs representing the processing time
					for each job on each machine


================================OUTPUT==================================

The algorithm will produce a CSV file with the output results for a single
function on all Data Files with the name "FS<x>Resultsfile.csv" where <x> is 
a number corresponding to a function, as specified about.

A file with data for a Gantt Chart will be printed out every 10th file with
the name "gcFS<x>file<y>.csv" where <x> corresponds to a function and <y> is
the number of the Data File.

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

