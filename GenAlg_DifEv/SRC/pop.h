/*
PROJECT 3: Genetic Algorithm and Differential Evolution

Author: Holly Strauch
CS 471
Project 3
May 3, 2019

This program uses Genetic Algorithm and Differential Evolution to optimize
18 different functions. Genetic Algorithm is run with either tournament
select or roulette select, and Differential Evolution is run with one of
10 DE strategies
*/

#ifndef STRAUCH_PROJECT3_POP_H
#define STRAUCH_PROJECT3_POP_H
#include "input.h"

//Population struct for with data types for a population, the associated fitness, an ordering of the fitness,
// and the best of the fitness values
typedef struct _population {
    double **popMatrix;
    double *fitness;
    int *order;
    double bestFit;
} population;

//Initializes the memory for a population struct
population *initPop(int solutions, int dim);

//Calculates the fitness values for each vector in a population popMatrix.
void calculateFit(population *pop, int index, input *in);

//Sets the order data type in a population struct to contain indices in sorted order based on the firness
//data type.  Sorted high to low.
void setOrder(population *pop, input *in);

//Copies one population into another
void copyPop(population *pop, population *temp, input *in);

//Finds the lowest fitness value and sets it in the population struct.  Returns the index of the
//best value
int calculateBestFit(population *pop, input *in);

//freePop() frees all the allocated memory of a population struct
void freePop(int popsize, population *pop);

#endif //STRAUCH_PROJECT3_POP_H
