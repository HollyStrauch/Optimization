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

#include <stdio.h>
#include <stdlib.h>
#include "pop.h"
#include "util.h"
#include "input.h"
#include "ftns.h"

/** /brief Initializes the memory for a population struct
 *
 * @param popu Size of the population
 * @param dim Dimension of the vectors in popMatrix
 * @return pointer to the initialized population struct
 */
population *initPop(int popu, int dim){
    population *pop = (population *)calloc(1, sizeof(population));

    pop->popMatrix = matrixgen(popu, dim);
    pop->fitness = vectgenDoub(popu);
    pop->order = vectgenInt(popu);
    pop->bestFit=0.0;

    return pop;
}

/** /brief Calculates the fitness values for each vector in a population popMatrix.
 *
 * @param pop The population where the fitness is being caluclated
 * @param index The index of the current function's input in ftnBounds
 * @param in The input struct containing function input values
 */
void calculateFit(population *pop, int index, input *in){
    int i=0;

    for (i = 0; i < in->popsize; i++){
        pop->fitness[i] = runftns(in->ftnBounds[index * 3], in->dim, pop->popMatrix[i]);
    }

}

/** /brief Sets the order data type in a population struct to contain indices in sorted order based on the firness
 *      data type.  Sorted high to low.
 *
 * @param pop The population to create the ordered indices
 * @param in input struct with input info.
 */
void setOrder(population *pop, input *in){
    double *copy = (double *)calloc(in->popsize, sizeof(double));
    int i=0, k=0;

    if (copy == NULL){
        fprintf(stderr, "Out of memory: vectgenDoub\n");
        exit(-1);
    }

    for(i = 0; i < in->popsize; i++){
        copy[i] = pop->fitness[i];
    }

    for (k = 0; k < in->popsize; k++){
        pop->order[k] = k;
    }

    quickSort(0, in->popsize - 1, copy, pop->order);

    free(copy);
}

/** /brief Copies one population into another
 *
 * @param pop Destination population struct
 * @param temp Source population struct
 * @param in input struct with input information
 */
void copyPop(population *pop, population *temp, input *in) {
    int i=0, j=0;

    for (i = 0; i < in->popsize; i++) {
        for (j = 0; j < in->dim; j++) {
            pop->popMatrix[i][j] = temp->popMatrix[i][j];
        }
        pop->fitness[i] = temp->fitness[i];
        pop->order[i] = temp->order[i];
    }
    pop->bestFit = temp->bestFit;
}

/*! \brief Finds the lowest fitness value and sets it in the population struct.  Returns the index of the
 *  best value

 \param *pop The population struct that is being analyzed
 \param *in The input struct
 \param exclude An index to be ignored
 \return bestI The index of the lowest fitness value
*/
int calculateBestFit(population *pop, input *in){
    int bestI=0, i=0;
    double best=0.0;
    double total = 0;

    best = pop->fitness[0];
    total += best;

    for(i = 1; i < in->popsize; i++){
        if(pop->fitness[i] < best){
            best = pop->fitness[i];
            bestI = i;
        }
        total += pop->fitness[i];
    }

    pop->bestFit = best;
    return bestI;
}

/** /brief freePop() frees all the allocated memory of a population struct
 *
 * @param popsize Length of popMatrix, fitness, and order
 * @param pop population struct being freed
 */
void freePop(int popsize, population *pop){
    freematrix(popsize, pop->popMatrix);
    free(pop->fitness);
    free(pop->order);
    free(pop);
}
