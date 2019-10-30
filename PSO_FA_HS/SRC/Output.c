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
#include "Input.h"
#include "Output.h"
#include "Util.h"

/** \brief Initializes the output struct that will hold data to be printed
 *
 * @param in Input struct with data for the algorithm and equations
 * @param f The current function that the algorithm is being run on
 * @return A pointer to the output struct
 */
Output *initOutput(Input *in, int f){
    Output *out = (Output *)calloc(1, sizeof(Output));
    out->ftn = f;
    out->best_per_itr = matrixgen(in->experiments, in->itrs);
    out->worst_per_itr = matrixgen(in->experiments, in->itrs);
    out->itrI = 0;
    out->expI = 0;
    out->ftnCalls = vectgenInt(in->experiments);
    out->time = vectgenDoub(in->experiments);

    return out;
}

/** \brief Adds the best and worst values to their respective arrays at the current iteration
 *
 * @param out The current Output struct
 * @param best Best fitness values
 * @param worst Worst Fitness value
 */
void addBestWorstOutput(Output * out, double best, double worst){
    out->best_per_itr[out->expI][out->itrI] = best;
    out->worst_per_itr[out->expI][out->itrI] = worst;

}

/** \brief Adds to the number of recorded calls of the objective function
 *
 * @param out The current Output struct
 * @param calls The number of calls being added
 */
void addCallsOutput(Output *out, int calls){
    out->ftnCalls[out->expI] += calls;
}

/** \brief Sets the algorithm runtime for the current experiement
 *
 * @param out The current Output struct
 * @param t The runtime
 */
void setTimeOutput(Output *out, double t){
    out->time[out->expI] = t;
}

/** \brief Increments the index marking the current iteration
 *
 * @param out The current Output struct
 * @param in Input struct with data for the algorithm and equations
 */
void outputIncItr(Output *out, Input *in){
    out->itrI += 1;
}

/** \brief Increments the index marking the current experiment
 *
 * @param out
 * @param in Input struct with data for the algorithm and equations
 */
void outputIncExp(Output *out, Input *in){
    out->expI += 1;
    out->itrI = 0;
}

/** \brief Prints all the values in the Output struct to a file
 *
 * @param out The current Output struct
 * @param in Input struct with data for the algorithm and equations
 * @param op The FILE pointer
 */
void printOutput(Output *out, Input * in, FILE *op){
    int i = 0, j=0;

    fprintf(op, "%d Best\n", out->ftn);
    for(i = 0; i < in->experiments; i++){
        for(j = 0; j < in->itrs; j++) {
            fprintf(op, "%lf,", out->best_per_itr[i][j]);
        }
        fprintf(op, ",%d,", out->ftnCalls[i]);
        fprintf(op, "%lf,,", out->time[i]);
        for(j = 0; j < in->itrs; j++) {
            fprintf(op, "%lf,", out->worst_per_itr[i][j]);
        }

        fprintf(op, "\n");
    }

}

/** \brief Frees the memory of the Output struct and its contents
 *
 * @param out The Output struct to be freed
 * @param in Input struct with data for the algorithm and equations
 */
void freeOutput(Output *out, Input *in) {
    freematrix(in->experiments, out->best_per_itr);
    freematrix(in->experiments, out->worst_per_itr);
    free(out->ftnCalls);
    free(out->time);
    free(out);
}

