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

#ifndef STRAUCH4_PSOPOPULATION_H
#define STRAUCH4_PSOPOPULATION_H

#include "../Input.h"
#include "../Output.h"

/** \brief struct to hold all the population information for a PSO algorithm
 *
 * double **particles: Matrix to hold current population
 * double **velocities: Matrix to hold the current corresponding velocities
 * double **pbSolutions: Matrix to hold the vectors of the personal best solutions
 * double *fitness: Array to hold the current fitness values
 * double *pbest: Array to hold the personal best fitness values
 * double *bestSolution: The global best solution vector
 * double gbest: The global best fitness value
 * double worst: The worst fitness values
 *
 */
typedef struct _PSOpopulation {
    double **particles;
    double **velocities;
    double **pbSolutions;
    double *fitness;
    double *pbest;
    double *bestSolution;
    double gbest;
    double worst;
} PSOpopulation;

//Initializes a struct to contain all the population info for a PSOpopulation
PSOpopulation *initPop(int popSize, int dim);

//Frees the memory of a PSOpopulation struct and its data fields
void freePSOpop(int popsize, PSOpopulation *pop);

//Calculates the fitness values for the current population and updates how many times the objective function
//     was called in the Output struct
void calculateFit(PSOpopulation *pop, int index, Input *in, Output *out);

//Calculates the initial global best and sets initial pbSolutions to the starting vectors
void initBest(PSOpopulation *pop, int popSize, int dim);

//Creates initial velocites as random positive values, half the size of the domain of the function
void initVelocities(Input *in, int index, PSOpopulation *pop);

//Sets the global best, personal best, and worst fitness values
void setValues(PSOpopulation *pop, int popSize, int dim);

//Finds and updates the overall minimum value for global best
void setGBest(PSOpopulation *pop, int p, int dim);

//Updates the personal best fitnesses and corresponding vectors
void setPBest(PSOpopulation *pop, int p, int dim);

//Finds and sets the overall worst fitness values
void setWorst(PSOpopulation *pop, int popSize);

//Checks values in a vector against the given bounds.  If the value is outside the bounds, it is set to the
//      appropriate bound
void fixSolutions(PSOpopulation *pop, Input *in, int index);

#endif //STRAUCH4_PSOPOPULATION_H
