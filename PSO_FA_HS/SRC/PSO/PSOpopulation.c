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
#include "PSOpopulation.h"
#include "../Util.h"
#include "../Input.h"
#include "../Ftns.h"
#include "../MT/mt19937ar.h"
#include "../Output.h"

/** \brief Initializes a struct to contain all the population info for a PSOpopulation
 *
 * @param popSize The size of the population matrix
 * @param dim The dimension of the vectors in the population matrix
 * @return A pointer to the initialized PSOpopulation struct
 */
PSOpopulation *initPop(int popSize, int dim){
    PSOpopulation *pop = (PSOpopulation *)calloc(1, sizeof(PSOpopulation));

    pop->particles = matrixgen(popSize, dim);
    pop->velocities = matrixgen(popSize, dim);
    pop->pbSolutions = matrixgen(popSize, dim);
    pop->fitness = vectgenDoub(popSize);
    pop->pbest = vectgenDoub(popSize);
    pop->bestSolution = vectgenDoub(dim);
    pop->gbest=0.0;
    pop->worst=0.0;

    return pop;
}

/** \brief Frees the memory of a PSOpopulation struct and its data fields
 *
 * @param popsize The size of the population matrix
 * @param pop The population being freed
 */
void freePSOpop(int popsize, PSOpopulation *pop){
    freematrix(popsize,pop->particles);
    freematrix(popsize, pop->velocities);
    freematrix(popsize, pop->pbSolutions);
    free(pop->fitness);
    free(pop->pbest);
    free(pop->bestSolution);
    free(pop);
}

/**\brief Calculates the fitness values for the current population and updates how many times the objective function
 *      was called in the Output struct
 *
 * @param pop The population where the fitness is being calculated
 * @param index References the current location in the ftnBounds array in the input struct
 * @param in Input struct with data for the algorithm and equations
 * @param out Output struct that stores data to be printed
 */
void calculateFit(PSOpopulation *pop, int index, Input *in, Output *out){
    int i=0;
    for (i = 0; i < in->popsize; i++){
        pop->fitness[i] = runftns(in->ftnBounds[index * 3], in->dim, pop->particles[i]);
    }
    addCallsOutput(out, in->popsize);
}

/** \brief Calculates the initial global best and sets initial pbSolutions to the starting vectors
 *
 * @param pop The current population
 * @param popSize The size of the population matrix
 * @param dim The dimension of each vector
 */
void initBest(PSOpopulation *pop, int popSize, int dim){
    int i=0;
    int best = 0;

    for(i = 0; i < popSize; i++){
        if(pop->fitness[i] < pop->fitness[best]){
            best = i;
        }
        copyVect(pop->particles[i], pop->pbSolutions[i], dim);
    }

    pop->gbest = pop->fitness[best];
    copyVect(pop->particles[best], pop->bestSolution, dim);
}

/** \brief Creates initial velocites as random positive values, half the size of the domain of the function
 *
 * @param in Input struct with data for the algorithm and equations
 * @param index References the current position in the ftnBounds array
 * @param pop The current population struct
 */
void initVelocities(Input *in, int index, PSOpopulation *pop){
    int i=0, j=0;

    for(i = 0; i < in->popsize; i++){
        for(j = 0; j < in->dim; j++){
            pop->velocities[i][j] = genrand_real1() * (.5 * (in->ftnBounds[index * 3 + 2] - in->ftnBounds[index * 3 + 1]));
        }
    }
}

/** \brief Sets the global best, personal best, and worst fitness values
 *
 * @param pop Current population
 * @param popSize The size of the population matrix
 * @param dim The dimension of each vector in the matrix
 */
void setValues(PSOpopulation *pop, int popSize, int dim){
    setPBest(pop, popSize, dim);
    setGBest(pop, popSize, dim);
    setWorst(pop, popSize);
}

/** \brief Updates the personal best fitnesses and corresponding vectors
 *
 * @param pop The current population
 * @param popSize The size of the population matrix
 * @param dim The dimension of the vectors
 */
void setPBest(PSOpopulation *pop, int popSize, int dim){
    int i = 0;
    for(i = 0; i < popSize; i++) {
        if (pop->fitness[i] < pop->pbest[i]) {
            pop->pbest[i] = pop->fitness[i];
            copyVect(pop->particles[i], pop->pbSolutions[i], dim);
        }
    }
}

/** \brief Finds and updates the overall minimum value for global best
 *
 * @param pop Current population
 * @param popSize Size of the population matrix
 * @param dim The dimension of the vectors
 */
void setGBest(PSOpopulation *pop, int popSize, int dim){
    int i = 0, best=0;

    for(i = 0; i < popSize; i++) {
        if (pop->pbest[i] < pop->gbest) {
            pop->gbest = pop->pbest[i];
            best = i;
        }
    }
    copyVect(pop->pbSolutions[best], pop->bestSolution, dim);
}

/** \brief Finds and sets the overall worst fitness values
 *
 * @param pop The current population
 * @param popSize The size of the population matrix
 */
void setWorst(PSOpopulation *pop, int popSize) {
    double worst = pop->fitness[0];
    int i = 0;

    for(i = 1; i < popSize; i++){
        if (pop->fitness[i] > worst){
            worst = pop->fitness[i];
        }
    }

    pop->worst = worst;
}

/** \brief Checks values in a vector against the given bounds.  If the value is outside the bounds, it is set to the
 *      appropriate bound
 *
 * @param pop The current population
 * @param in Input struct with data for the algorithm and equations
 * @param index Reference the current position in the ftnBounds array
 */
void fixSolutions(PSOpopulation *pop, Input *in, int index) {
    int i = 0, j = 0;
    for (i = 0; i < in->popsize; i++) {
        for (j = 0; j < in->dim; j++) {
            if (pop->particles[i][j] < in->ftnBounds[index * 3 + 1]) {
                pop->particles[i][j] = in->ftnBounds[index * 3 + 1];
            } else if (pop->particles[i][j] > in->ftnBounds[index * 3 + 2]) {
                pop->particles[i][j] = in->ftnBounds[index * 3 + 2];
            }
        }
    }
}
