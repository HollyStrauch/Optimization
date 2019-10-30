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

#ifndef STRAUCH4_FA_H
#define STRAUCH4_FA_H

#include "FApop.h"

// firefly function runs the Firefly Algorithm.  An output struct is initialized to print out data to a file,
//     then for each experiment a random population is generated and sorted before the rest of the algorithm is
//     completed int the FAmove() function. Each individual generation can be printed to another file by uncommenting
//     the FILE *opGen open and close lines, and the printGen() function.
void firefly(Input *in);

//After a copy of the current population and fitness are created, pairwise comparisons are performed between
//      each firefly.  Their relative light intensities are compared, and if the initial firefly has a higher fitness
//      it will be moved towards the other.  Then the worst firefly in the population will be replaced if the new
//      firefly position is improved.  Comparisons are continued to be made with the original vectors in the temporary
//      copy while the current population is updated.
void FAmove(FApop *pop, Input *in, int index, Output *out);

//Calculates the distance between two firefly vectors
double FAdistance(Input *in, double *V1, double *V2);

//Calculates the attractiveness of a firefly. C2 refers to the beta parameter while C3 refers gamma
double betaftn(Input *in, double dist);

//A new firefly vector is created based off of the movement of one firefly towards another
double * FAattract(Input *in, double *Vi, double *Vj, double beta, double range);

//calculates the relative intensity of a firefly
double FAintensity(Input *in, double fitness, double dist);

#endif //STRAUCH4_FA_H
