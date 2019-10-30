/*
 * 	PROJECT 4: Particle Swarm Optimization, Firefly Algorithm,
			and Harmony Search

Author: Holly Strauch
CS 471
Project 4
May 19, 2019

This program uses Particle Swarm Optimization (PSO), Firefly Algorithm (FA), and
Harmony Search (HS) to attempt to optimize the fitness values of 18 different
functions. The equations that the algorithms are run on take vectors as inputs
and the populations are scalable in dimension and size.
 */

#ifndef STRAUCH4_INPUT_H
#define STRAUCH4_INPUT_H

/** \brief Struct to hold data for functions and algorithms
 *
 * int experiments: The number of times to run each function
 * int popsize: The size to make the population matrix
 * int itrs: The number of iterations to run the algorithms for
 * int dim: the dimension of the vectors in the population
 * double C1: The first constant value for an algorithm
 * double C2: The second constant value for an algorithm
 * double C3: The third constant value for an algorithm
 * int numFtns: the number of functions that will be run
 * double *ftnBounds: An array with the functions that will be run and their bounds
 */

typedef struct _Input {
    int experiments;
    int popsize;
    int itrs;
    int dim;
    double C1;
    double C2;
    double C3;
    int numFtns;
    double *ftnBounds;
} Input;

//Initializes an Input struct from data read in from a file
Input *getInput(char *filename);
#endif //STRAUCH4_INPUT_H
