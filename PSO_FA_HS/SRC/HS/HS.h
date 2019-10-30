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
#ifndef STRAUCH4_HS_H
#define STRAUCH4_HS_H

#include "../Output.h"
#include "HSpop.h"

// harmonySearch initializes The harmony Search algorithm. An output struct is initialized to print out data to
//      a file, then for each experiment a random population is generated and sorted before the rest of the algorithm is
//      completed int the HStuning() function.Each individual generation can be printed to another file by uncommenting
//      the FILE *opGen open and close lines, and the printGen() function.
void harmonySearch(Input *in);

//A new vector is created and, if it is an improvement on the worst vector in the population, the new vector
//      replaces the worst and is put into sorted order. The new vector is created 1 dimension at a time. With a
//      probability of HMCR (C1), the current dimension will be selected randomly from the corresponding dimension
//      from another vector in the population.  Then, with a probability of PAR(C2), it will be modified by the
//      bandwidth (C3) times a random value [0,1).  Otherwise, a completely random value is generated for the dimension
void HStuning(HSpop *pop, Input *in, Output *out, double *newVect, int index);

#endif //STRAUCH4_HS_H
