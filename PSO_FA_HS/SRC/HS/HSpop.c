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

#include <stdlib.h>
#include <stdio.h>
#include "HSpop.h"
#include "../Util.h"
#include "../Ftns.h"
#include "../Output.h"

/** \brief Initializes the population for Harmony Search
 *
 * @param popSize The size of the population
 * @param dim  The dimension of the vectors in the population
 * @return A pointer to the initialized population
 */
HSpop *initHSPop(int popSize, int dim){
    HSpop *pop = (HSpop *)calloc(1, sizeof(HSpop));

    pop->solutions = matrixgen(popSize, dim);
    pop->fitness = vectgenDoub(popSize);

    return pop;
}

/** \brief Calculates the fitness values for the current population and updates how many times the objective function
 *      was called in the Output struct
 *
 * @param pop The current population
 * @param index The current position being referenced in in->ftnBounds
 * @param in Input struct with data for the algorithm and equations
 * @param out The Output struct that records values for printing
 */
void calculateFitHS(HSpop *pop, int index, Input *in, Output *out){
    int i=0;
    for (i = 0; i < in->popsize; i++){
        pop->fitness[i] = runftns(in->ftnBounds[index * 3], in->dim, pop->solutions[i]);
    }
    addCallsOutput(out, in->popsize);
}

/** \brief Checks to see if the fitness of a vector is lower than the worst vector in a descending sorted array.  If so,
 *      the new vector replaces the worst and is moved into sorted position in the matrix.
 *
 * @param pop The current population
 * @param vect The new vector being compared
 * @param ftn The current objective function
 * @param in Input struct with data for the algorithm and equations
 * @param out The Output struct that records values for printing
 */
void updateWorstHS(HSpop *pop, double *vect, int ftn, Input *in, Output *out){
    double fFit = runftns(ftn, in->dim, vect);
    addCallsOutput(out, 1);

    if(fFit < pop->fitness[0]){
        copyVect(vect, pop->solutions[0], in->dim);
        pop->fitness[0] = fFit;

        //ind is 1 ahead of the new firefly
        int ind = 1;
        while(fFit < pop->fitness[ind] && ind < in->popsize){
            swap(ind, ind - 1, pop->fitness, pop->solutions, in->dim);
            ind++;
        }
    }
}

/** \brief Frees the memory of the HSpop struct and its contents
 *
 * @param popsize The size of the population
 * @param pop The HSpop struct being freed
 */
void freeHSpop(int popsize, HSpop *pop){
    freematrix(popsize,pop->solutions);
    free(pop->fitness);
    free(pop);
}
