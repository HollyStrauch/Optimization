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

#ifndef STRAUCH4_HSPOP_H
#define STRAUCH4_HSPOP_H

#include "../Input.h"
#include "../Output.h"

/** \brief Struct to hold a population population matrix and corresponding fitness vector for the Harmony Search
 *      algorithm
 *
 *  double **solutions is a matrix of size population X vector dimension
 *  double *fitness is an array of size population
 */
typedef struct _HSpop {
    double **solutions;
    double *fitness;
} HSpop;

//Initializes the population for Harmony Search
HSpop *initHSPop(int popSize, int dim);

//Calculates the fitness values for the current population and updates how many times the objective function
//       was called in the Output struct
void calculateFitHS(HSpop *pop, int index, Input *in, Output *out);

//Checks to see if the fitness of a vector is lower than the worst vector in a descending sorted array.  If so,
//      the new vector replaces the worst and is moved into sorted position in the matrix.
void updateWorstHS(HSpop *pop, double *vect, int ftn, Input *in, Output *out);

//Frees the memory of the HSpop struct and its contents
void freeHSpop(int popsize, HSpop *pop);

#endif //STRAUCH4_HSPOP_H
