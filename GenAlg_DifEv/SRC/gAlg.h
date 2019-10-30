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


#ifndef STRAUCH_PROJECT3_GALG_H
#define STRAUCH_PROJECT3_GALG_H

#include "pop.h"
#include "input.h"
#include "algInput.h"

//Opens a csv file to print to and runs genAlg() with roulette wheel or tournement selection
void selectGA(algInput *algIn);

//Runs the Genetic Algorithm and prints to the specified file
void genAlg(input * in, int select, FILE *op, int index);

//pickBest compares the children to the parents.  If a child is worse than both parents, that offspring
//    pointer will be set to one of the parents.
void pickBest(double *off1, double *off2, int p1I, int p2I, int index, input *in, population * pop);

//reduce finalizes the next generation in a population struct pop by taking the top elite vectors from the
// previous generation, then filling in the remaining population with the best results from the newly created
// offspring.  The populations must have their order set for the function to work properly.
void reduce(population *pop, population *newpop, input *in, int elite);

//crossOver creates two offspring vectors by taking two parents, picking an index, placing the values
// preceding that point into one offspring and those after into the other offspring, "crossing" the vectors.
// A random number is generated and crossover will only occur if it is lower than an inputted crossover rate
void crossOver(double * o1, double *o2, double *p1, double *p2, input *in);

//A vector is mutated if a randomly generated number is lower than an inputed mutation rate.  New values
// are checked to stay in function bounds.
void mutate(double *offspring, input *in, int index);

//Two vectors are chosen by selecting a group of vectors randomly, then choosing the best fit from that
//  selection.  The number 'exclude' will be skipped over in this process.
int tournSelect(population * pop, input * in, int exclude);

//brief Finds the minimum value in a vectors
double findMin(double * vect, int length);

//Chooses two vectors by created a normalized array with weighted values, and randomly selected a vector
// from the normalized array.
int *rouletteSelect(population * pop, input *in, int *indices);

#endif //STRAUCH_PROJECT3_GALG_H
