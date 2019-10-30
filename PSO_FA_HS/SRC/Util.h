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

#ifndef STRAUCH4_UTIL_H
#define STRAUCH4_UTIL_H

#include "Input.h"

//Use the Mersenne Twister random number generator to fill a matrix
//	with random values within set bounds.
double **fillmatrix(int trials, int dim, double **matrix, double lowb, double highb);

//Create 2d matrix with calloc()
double **matrixgen(int trials, int dim);

//Create double vector with calloc()
double *vectgenDoub(int dim);

//Create int vector with calloc()
int *vectgenInt(int dim);

//Copies one vector into another
void copyVect(double *source, double *dest, int length);

//Copies one matrix into another
void copyMatrix(double **source, double **dest, int trials, int dim);

//Free the memory from a matrix
void freematrix(int trials, double **matrix);

//Checks values in a vector against the given bounds.  If the value is outside the bounds, it is set to the
//     appropriate bound
void fixSol(double *vect, double upper, double lower, int dim);

//Generate uniquely random indices using Knuth's algorithm.  Numbers 0 - N-1 will be generated.
//  Method can accept an integer to be excluded from the generated numbers.
int * uniqueRandI(int * ind, int sourceSize, int unums, int exclude1, int exclude2);

void printGen(double **matrix, int popsize, int dim, FILE *op);

//Modified Quick Sort Algorithm based on DepthLmitedQuickSort() from Microsoft Reference Source.  An array
//   of indices is sorted based on the values in a fitness array in descending order
void quickSort(int left, int right, double *fit, double **solutions, int dim);

//Swaps two values inside an array of values and an array of indices respectivly.
void swap(int index1, int index2, double * fitness, double **solutions, int dim);


#endif //STRAUCH4_UTIL_H
