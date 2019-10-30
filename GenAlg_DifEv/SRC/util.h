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

#ifndef STRAUCH_PROJECT3_UTIL_H
#define STRAUCH_PROJECT3_UTIL_H

//Use the Mersenne Twister random number generator to fill a matrix
//	with random values within set bounds.
double **fillmatrix(int trials, int dim, double **matrix, double lowb, double highb);

//Create double vector with calloc()
double *vectgenDoub(int dim);

//Create int vector with calloc()
int *vectgenInt(int dim);

//Create 2d matrix with calloc()
double **matrixgen(int trials, int dim);

//Free the memory from a matrix
void freematrix(int dim, double **matrix);

//Generate uniquely random indices using Knuth's algorithm.  Numbers 0 - N-1 will be generated.
//  Method can accept an integer to be excluded from the generated numbers.
int * uniqueRandI(int * ind, int sourceSize, int unums, int exclude1, int exclude2);

//Copies one vector into another
void copyVect(double *source, double *dest, int length);

//Modified Quick Sort Algorithm based on DepthLmitedQuickSort() from Microsoft Reference Source.  An array
//   of indices is sorted based on the values in a fitness array in descending order
void quickSort(int left, int right, double *fitCopy, int *indices);

//Swaps two values inside an array of values and an array of indices respectivly.  Used in quickSort().
void swap(int index1, int index2, double * fitness, int * ind);

#endif //STRAUCH_PROJECT3_UTIL_H