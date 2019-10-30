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
#include <time.h>
#include "../Input.h"
#include "PSO.h"
#include "PSOpopulation.h"
#include "../Util.h"
#include "../MT/mt19937ar.h"
#include "../Output.h"

/** \brief Runs the PSO algorithm.  The population is initialized then for each iteration the function for moving
 *      particles is called.  This function also prints output to a file.
 *
 * @param in Input struct with data for the algorithm and equations
 */
void PSORun(Input * in){
    int i=0, j=0;
    FILE *op = fopen("PSOResults.csv", "a");
    //FILE *opGen = fopen("PSOGen.csv", "a");

    for(i = 0; i <in->numFtns; i++) {
        Output *out = initOutput(in, (int) in->ftnBounds[i * 3]);
		int e=0;
		for(e = 0; e < in->experiments; e++) {

            printf("F %d\n", (int) in->ftnBounds[i * 3]);
            clock_t start = clock();

            PSOpopulation *pop = initPop(in->popsize, in->dim);
            pop->particles = fillmatrix(in->popsize, in->dim, pop->particles, in->ftnBounds[i * 3 + 1],
                                        in->ftnBounds[i * 3 + 2]);
            initVelocities(in, i, pop);

            calculateFit(pop, i, in, out);

            copyVect(pop->fitness, pop->pbest, in->popsize);
            initBest(pop, in->popsize, in->dim);
            printf("Itr Best: %lf,", pop->gbest);

            //PSO next level
            for (j = 0; j < in->itrs; j++) {

                PSOparticles(pop, in);
                fixSolutions(pop, in, i);
                calculateFit(pop, i, in, out);
                setValues(pop, in->popsize, in->dim);
                addBestWorstOutput(out, pop->gbest, pop->worst);
                //printGen(pop->particles, in->popsize, in->dim, opGen);
                outputIncItr(out, in);
            }
            printf("Best: %lf \n\n", pop->gbest);
            clock_t stop = clock();
            setTimeOutput(out, 1000.0 * ((double) stop - (double) start) / CLOCKS_PER_SEC);
            outputIncExp(out, in);

            freePSOpop(in->popsize, pop);

        }
        printOutput(out, in, op);
        freeOutput(out, in);
    }
    //fclose(opGen);
    fclose(op);
}


/** \brief For each individual in the popultion, a new velocity is calculated, the particle is updated,
 *      then the new fitness, personal best, and global best values are calculated.
 *
 * @param pop The current population of particles
 * @param in Input struct with function and algorithm values
 */
void PSOparticles(PSOpopulation *pop, Input * in){
    int i=0;
    for(i = 0; i < in->popsize; i++) {
        PSONewVelocity(in, i, pop);
        PSOUpdateParticle(in, i, pop);
    }

}

/** \brief Calculates the new velocities for each dimension for a vector C3 is a dampening factor, while C1 and C2
 *      effect whether the personal best or global best has a greater effect on the overall movement
 *
 * @param in Input struct with data for the algorithm and equations
 * @param index References the current vector that the velocity is being calculated for
 * @param pop The population where the velocities are being calculated
 */
void PSONewVelocity(Input *in, int index, PSOpopulation *pop){
    int j=0;
    for(j = 0; j < in->dim; j++) {
        pop->velocities[index][j] =
                in->C3 * (pop->velocities[index][j] + in->C1 * genrand_real1() * (pop->pbSolutions[index][j] - pop->particles[index][j])
                + in->C2 * genrand_real1() * (pop->bestSolution[j] - pop->particles[index][j]));
    }
}

/** \brief Updates the values in the vector by adding the new velocity per each dimension
 *
 * @param in Input struct with data for the algorithm and equations
 * @param index References the current vector in the population that is being updated
 * @param pop The current population
 */
void PSOUpdateParticle(Input *in, int index, PSOpopulation *pop){
    int j=0;

    for(j = 0; j < in->dim; j++){
        pop->particles[index][j] = pop->particles[index][j] + pop->velocities[index][j];
    }
}
