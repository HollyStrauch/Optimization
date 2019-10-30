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
#include "FA.h"
#include "../Util.h"
#include "../Input.h"
#include "FApop.h"
#include "../MT/mt19937ar.h"

/** \brief firefly function runs the Firefly Algorithm.  An output struct is initialized to print out data to a file,
 *      then for each experiment a random population is generated and sorted before the rest of the algorithm is
 *      completed int the FAmove() function. Each individual generation can be printed to another file by uncommenting
 *      the FILE *opGen open and close lines, and the printGen() function.
 *
 * @param in Input struct with data for the algorithm and equations
 */
void firefly(Input *in){
    int i=0, j=0, e=0;
    FILE *op = fopen("FAResult.csv", "a");
	//FILE *opGen = fopen("FAGen.csv", "a");

    for(i = 0; i < in->numFtns; i++) {
        Output *out = initOutput(in, (int) in->ftnBounds[i * 3]);

        for (e = 0; e < in->experiments; e++) {
            printf("\nF %d \n", (int) in->ftnBounds[3 * i]);
            clock_t start = clock();

            FApop *pop = initFAPop(in->popsize, in->dim);

            pop->fireflies = fillmatrix(in->popsize, in->dim, pop->fireflies, in->ftnBounds[i * 3 + 1],
                                        in->ftnBounds[i * 3 + 2]);
            calculateFitFA(pop, i, in, out);
            quickSort(0, in->popsize - 1, pop->fitness, pop->fireflies, in->dim);

            for (j = 0; j < in->itrs; j++) {
                FAmove(pop, in, i, out);
                calculateFitFA(pop, i, in, out);
                addBestWorstOutput(out, pop->fitness[in->popsize - 1], pop->fitness[0]);
                outputIncItr(out, in);
				printf("%lf ", pop->fitness[in->popsize - 1]);
				//printGen(pop->fireflies, in->popsize, in->dim, opGen);

            }
            printf("%lf ", pop->fitness[in->popsize - 1]);
            clock_t stop = clock();
            setTimeOutput(out, ((double) stop - (double) start) / CLOCKS_PER_SEC);

            freeFApop(in->popsize, pop);
            outputIncExp(out, in);
        }
        printOutput(out, in, op);
        freeOutput(out, in);
    }

    fclose(op);
    //fclose(opGen);
}

/** \brief After a copy of the current population and fitness are created, pairwise comparisons are performed between
 *      each firefly.  Their relative light intensities are compared, and if the initial firefly has a higher fitness
 *      it will be moved towards the other.  Then the worst firefly in the population will be replaced if the new
 *      firefly position is improved.  Comparisons are continued to be made with the original vectors in the temporary
 *      copy while the current population is updated.
 *
 * @param pop The current population
 * @param in The input struct with data for the algorithm and equation
 * @param index
 */
void FAmove(FApop *pop, Input *in, int index, Output *out){
    int i=0, j=0;
    double dist=0.0, beta=0.0;
    double range = in->ftnBounds[index * 3 + 2] - in->ftnBounds[index * 3 + 1];
	double **tempPop = matrixgen(in->popsize, in->dim);
	double *tempFit = vectgenDoub(in->popsize);
	copyMatrix(pop->fireflies, tempPop, in->popsize, in->dim);
	copyVect(pop->fitness, tempFit, in->popsize);

    for(i = in->popsize-1; i >= 0; i--){
        for(j = in->popsize-1; j >= 0; j--){
            dist = FAdistance(in, tempPop[i], tempPop[j]);
            double Ii = FAintensity(in, tempFit[i], dist);
            double Ij = FAintensity(in, tempFit[j], dist);
			if(Ij < Ii) {

                beta = betaftn(in, dist);
                double *firefly = FAattract(in, tempPop[i], tempPop[j], beta, range);
                fixSol(firefly, in->ftnBounds[index * 3 + 2], in->ftnBounds[index * 3 + 1], in->dim);
                updateWorst(pop, firefly, in->ftnBounds[index * 3], in, out);

                free(firefly);
            }
        }
    }
    freematrix(in->dim, tempPop);
    free(tempFit);
}

/** \brief Calculates the attractiveness of a firefly. C2 refers to the beta parameter while C3 refers gamma
 *
 * @param in The input struct with data for the algorithm and equation
 * @param dist The distance between two fireflies
 * @return The resulting attractiveness beta
 */
double betaftn(Input *in, double dist){
    double beta = in->C2 * exp(-1.0*in->C3*pow(dist, 2.0));
    return beta;
}

/** \brief A new firefly vector is created based off of the movement of one firefly towards another
 *
 * @param in The input struct with data for the algorithm and equation
 * @param Vi The first firefly vector
 * @param Vj The second firefly vector
 * @param beta The result from the betaftn
 * @param range The range of permitted values for the current equation
 * @return The new firefly vector
 */
double * FAattract(Input *in, double *Vi, double *Vj, double beta, double range){
    double * firefly = vectgenDoub(in->dim);
    int i = 0;
    for(i = 0; i < in->dim; i++) {
        firefly[i] = Vi[i] + beta * (Vj[i] - Vi[i]) + in->C1 *
                (genrand_real1() - .5) * range;
    }

    return firefly;
}

/** \brief Calculates the distance between two firefly vectors
 *
 * @param in The input struct with data for the algorithm and equation
 * @param V1 The first firefly
 * @param V2 The second firefly
 * @return the distance between the two fireflies
 */
double FAdistance(Input *in, double *V1, double *V2){
    int i=0;
    double dist=0.0;

    for(i = 0; i < in->dim; i++){
        dist += pow((double)(V1[i] - V2[i]), 2.0);
    }

    return sqrt(dist);
}

/** \brief calculates the relative intensity of a firefly
 *
 * @param in The input struct with data for the algorithm and equation
 * @param fitness The current fitness of the firefly
 * @param dist The distance between the firefly and the one it will be compared to
 * @return the relative light intesity
 */
double FAintensity(Input *in, double fitness, double dist){
    return fitness * exp(-1.0 * in->C3 * pow(dist, 2.0));
}