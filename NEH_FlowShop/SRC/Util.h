/*
 * 	PROJECT 5: NEH Algorithm on Flow Shop Functions

Author: Holly Strauch
CS 471
Project 5
May 31, 2019

This program runs the NEH algorithm on three functions: Flow Shop Scheduling (FSS),
Flow Shop with Blocking (FSB), and Flow Shop with No Wait (FSNW).  It is a
combinatorial algorithm which attempts to find the ordering n jobs being
processed in m machines that will results in the minimum amount of total time.
 */

#ifndef STRAUCH4_UTIL_H
#define STRAUCH4_UTIL_H

#include <stdio.h>
#include "Input.h"


//Create 2d integer matrix with calloc()
int **matrixGenInt(int trials, int dim);

//Create int vector with calloc()
int *vectgenInt(int dim);

//Free the memory from a matrix
void freematrix(int trials, int **matrix);

//Finds the minimum value of an array and returns the index of it's location.  If there is a tie for the
//       minimum value, one is selected randomly using Mersenne Twister number generator
int findMin(int *array, int length);

//Inserts a value at a specified index in the array. More space in the array is assumed, and existing values
// *      are shifted to the right to make room for the new value.
void insertAt(int *array, int length, int index, int value);

//Modified Quick Sort Algorithm based on DepthLmitedQuickSort() from Microsoft Reference Source.  An array
//   of indices is sorted based on the values in a fitness array in descending order
void quickSortFS(int left, int right, int *fit, int *order, int dim);

//Swaps two values inside an array of values and an array of indices respectivly.
void swapFS(int index1, int index2, int * fitness, int *order);

//return the max values of two integers
int iMAX(int a, int b);

#endif //STRAUCH4_UTIL_H
