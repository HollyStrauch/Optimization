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
#include "FApop.h"
#include "../Util.h"
#include "../Ftns.h"
#include "../Output.h"

/** \brief Initializes a population struct for the Firefly algorithm
 *
 * @param popSize Size of the population
 * @param dim The dimension of each 'firefly' vector
 * @return initialized population
 */

FApop *initFAPop(int popSize, int dim){
    FApop *pop = (FApop *)calloc(1, sizeof(FApop));

    pop->fireflies = matrixgen(popSize, dim);
    pop->fitness = vectgenDoub(popSize);

    return pop;
}

/** \brief Calculates the fitness values for the entire population and updates how many times the objective function
 *      was called
 *
 * @param pop The FApop struct with the population matrix and fitness vector
 * @param index The index that should be referenced from the ftnBounds array
 * @param in The Input struct with the information for the algorithm and equations
 * @param out The Output struct which will record values for output
 */
void calculateFitFA(FApop *pop, int index, Input *in, Output *out){
    int i=0;
    for (i = 0; i < in->popsize; i++){
        pop->fitness[i] = runftns(in->ftnBounds[index * 3], in->dim, pop->fireflies[i]);
    }
    addCallsOutput(out, in->popsize);
}

/** \brief Checks to see if the fitness of a vector is lower than the worst vector in a descending sorted array.  If so,
 *      the new vector replaces the worst and is moved into sorted position in the matrix.
 *
 * @param pop The current Firefly population
 * @param firefly The new vector being compared
 * @param ftn The current equation being run
 * @param in The Input struct with information for the algorithm and equations.
 */
void updateWorst(FApop *pop, double *firefly, int ftn, Input *in, Output *out){
    double fFit = runftns(ftn, in->dim, firefly);
    addCallsOutput(out, 1);

    if(fFit < pop->fitness[0]){
        copyVect(firefly, pop->fireflies[0], in->dim);
        pop->fitness[0] = fFit;

        //ind is 1 ahead of the new firefly
        int ind = 1;
        while(fFit < pop->fitness[ind] && ind < in->popsize){
            swap(ind, ind - 1, pop->fitness, pop->fireflies, in->dim);
            ind++;
        }
    }
}

/** \brief Frees the FApop and its contents
 *
 * @param popsize The size of the population
 * @param pop The FApop to be freed
 */
void freeFApop(int popsize, FApop *pop){
    freematrix(popsize,pop->fireflies);
    free(pop->fitness);
    free(pop);
}
