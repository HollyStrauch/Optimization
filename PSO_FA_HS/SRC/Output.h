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

#ifndef STRAUCH4_OUTPUT_H
#define STRAUCH4_OUTPUT_H

typedef struct _Output {
    int ftn;
    double **best_per_itr;
    double **worst_per_itr;
    int itrI;
    int expI;
    int *ftnCalls;
    double *time;

} Output;

//Initializes the output struct that will hold data to be printed
Output *initOutput(Input *in, int f);

//Adds the best and worst values to their respective arrays at the current iteration
void addBestWorstOutput(Output * out, double best, double worst);

//Adds to the number of recorded calls of the objective function
void addCallsOutput(Output *out, int calls);

//Increments the index marking the current iteration
void outputIncItr(Output *out, Input *in);

//Increments the index marking the current experiment
void outputIncExp(Output *out, Input *in);

//Sets the algorithm runtime for the current experiement
void setTimeOutput(Output *out, double t);

//Prints all the values in the Output struct to a file
void printOutput(Output *out, Input * in, FILE *op);

//Frees the memory of the Output struct and its contents
void freeOutput(Output *out, Input *in);


#endif //STRAUCH4_OUTPUT_H
