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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../Util.h"
#include "../Input.h"
#include "../MT/mt19937ar.h"
#include "HS.h"
#include "HSpop.h"
#include "../Output.h"
#include "../Ftns.h"

/** \brief harmonySearch initializes The harmony Search algorithm. An output struct is initialized to print out data to
 *      a file, then for each experiment a random population is generated and sorted before the rest of the algorithm is
 *      completed int the HStuning() function.Each individual generation can be printed to another file by uncommenting
 *      the FILE *opGen open and close lines, and the printGen() function.
 *
 * @param in Input struct with data for the algorithm and equations
 */

void harmonySearch(Input *in){
    int i=0, j=0, e=0;
    FILE *op = fopen("HSResults.csv", "a");
   // FILE *opGen = fopen("HSGen.csv", "a");

    for(i = 0; i < in->numFtns; i++) {
        Output *out = initOutput(in, (int) in->ftnBounds[i * 3]);

        for (e = 0; e < in->experiments; e++) {
            printf("F %d\n", (int) in->ftnBounds[i * 3]);
            clock_t start = clock();

            HSpop *pop = initHSPop(in->popsize, in->dim);
            pop->solutions = fillmatrix(in->popsize, in->dim, pop->solutions, in->ftnBounds[i * 3 + 1],
                                        in->ftnBounds[i * 3 + 2]);
            calculateFitHS(pop, i, in, out);
            quickSort(0, in->popsize - 1, pop->fitness, pop->solutions, in->dim);

            for (j = 0; j < in->itrs; j++) {
                double *newVect = vectgenDoub(in->dim);
                HStuning(pop, in, out, newVect, i);
                addBestWorstOutput(out, pop->fitness[in->popsize - 1], pop->fitness[0]);

                //printGen(pop->solutions, in->popsize, in->dim, opGen);
                outputIncItr(out, in);
                free(newVect);
            }
            printf("%lf, %lf, \n", pop->fitness[in->popsize - 1], pop->fitness[0]);
            clock_t stop = clock();
            setTimeOutput(out, (1000.0 * (double) stop - (double) start) / CLOCKS_PER_SEC);

            outputIncExp(out, in);
            freeHSpop(in->popsize, pop);
        }
        printOutput(out, in, op);
        freeOutput(out, in);
    }
    //fclose(opGen);
    fclose(op);
}

/** \brief A new vector is created and, if it is an improvement on the worst vector in the population, the new vector
 *      replaces the worst and is put into sorted order. The new vector is created 1 dimension at a time. With a
 *      probability of HMCR (C1), the current dimension will be selected randomly from the corresponding dimension
 *      from another vector in the population.  Then, with a probability of PAR(C2), it will be modified by the
 *      bandwidth (C3) times a random value [0,1).  Otherwise, a completely random value is generated for the dimension
 *
 * @param pop The current population
 * @param in Input struct with data for the algorithm and equations
 * @param out The Output struct that records values for printing
 * @param newVect The new vector being created
 * @param index The current position being referenced in in->ftnBounds
 */
void HStuning(HSpop *pop, Input *in, Output *out, double *newVect, int index){
    int i=0;

    for(i = 0; i < in->dim; i++){

        //C1 is HMCR
        if (genrand_real1() <= in->C1){
            newVect[i] = pop->solutions[(int)(genrand_real1()*in->popsize)][i];
            //C2 is PAR
            if(genrand_real1() <= in->C2){
                //C3 is bw
                newVect[i] = newVect[i] + genrand_real1() * in->C3;
            }
        }else{
            newVect[i] = genrand_real1() * (in->ftnBounds[index * 3 + 2] - in->ftnBounds[index * 3 + 1]) +
                    in->ftnBounds[index * 3 + 1];
        }
    }
    fixSol(newVect, in->ftnBounds[index * 3 + 2], in->ftnBounds[index * 3 + 1], in->dim);
    updateWorstHS(pop, newVect, in->ftnBounds[index * 3], in, out);
}