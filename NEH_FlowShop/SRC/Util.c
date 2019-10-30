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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include "Util.h"
#include "Input.h"
#include "MT/mt19937ar.h"
#include <string.h>



/*! \brief Create int vector with calloc()

 \param dim The dimension of the vector
 \return vect Integer vector of size dim
*/
int *vectgenInt(int dim){
    int *vect;

    vect = (int *) calloc(dim, sizeof(int));
    if (vect == NULL) {
        fprintf(stderr, "Out of memory: vectgenInt\n");
    }

    return vect;
}


/*! \brief Create 2d integer matrix with calloc()

 \param trials - number of vectors
 \param dim - dimension of each vector
 \return double pointer to a trials*dim matrix
*/
int **matrixGenInt(int trials, int dim){
    int i;
    int **matrix = (int **) calloc(trials, sizeof(int*));

    if (matrix == NULL) {
        fprintf(stderr, "Out of memory: matrixgen\n");

    }
    for (i = 0; i < trials; i++) {
        matrix[i] = vectgenInt(dim);
    }
    return matrix;
}


/*! \brief Free the memory from a matrix

	\param dim - dimension of the vectors in the matrix
*/
void freematrix(int trials, int **matrix) {
    int i;

    for (i = 0; i < trials; i++) {
        if(matrix[i]){
            free(matrix[i]);
        }
    }

    if(matrix) {
        free(matrix);
    }

}

/** \brief Copies one vector into another
*
* @param source The vector being copied
* @param dest The vector being copied to
* @param length The lenght of the vectors
*/
void copyVect(int *source, int *dest, int length) {
    int i=0;
    for (i = 0; i < length; i++) {
        dest[i] = source[i];
    }
}


/** \brief Modified Quick Sort Algorithm based on DepthLmitedQuickSort() from Microsoft Reference Source.  An array
 *      of indices is sorted based on the values in a fitness array in descending order
 *
 * @param left The left most index of the area being sorted. Starting value is 0;
 * @param right The left most index of the area being sorted. Starting value is length - 1;
 * @param fitCopy An array of values which the sortin is based off of.
 * @param indices An array of indices 0 through N-1
 */
void quickSortFS(int left, int right, int *fit, int *order, int dim)
{
    do
    {
        int i = left;
        int j = right;
        int middle = (j + i) / 2;

        // pre-sort the low, middle (pivot), and high values in place.
        if( fit[i] > fit[middle]){
            swapFS(i, middle, fit, order);
        }
        if( fit[i] > fit[j]){
            swapFS(i, j, fit, order);
        }
        if( fit[middle] > fit[j]){
            swapFS(middle, j, fit, order);
        }

        do
        {

            while(fit[i] > fit[middle]) i++;
            while(fit[j] < fit[middle]) j--;

            //assert(i >= left && j <= right, "(i>=left && j<=right)  Sort failed - Is your IComparer bogus?");
            if (i > j) break;
            if (i < j)
            {
                swapFS(i, j, fit, order);
            }
            i++;
            j--;
        } while (i <= j);

        // The next iteration of the while loop is to "recursively" sort the larger half of the array and the
        // following calls recrusively sort the smaller half.

        if (j - left <= right - i)
        {
            if (left < j) quickSortFS(left, j, fit, order, dim);
            left = i;
        }
        else
        {
            if (i < right) quickSortFS(i, right, fit, order, dim);
            right = j;
        }
    } while (left < right);
}

/** \brief Swaps two values inside an array of values and an array of indices respectivly.  Used in quickSort().
 *
 * @param index1 First index to be swapped
 * @param index2 Second index to be swapped
 * @param fitness Array of values
 * @param ind Array of indices
 */
void swapFS(int index1, int index2, int * fitness, int * order){
    int temp=0;

    temp = fitness[index1];
    fitness[index1] = fitness[index2];
    fitness[index2] = temp;

    temp = order[index1];
    order[index1] = order[index2];
    order[index2] = temp;

}



/** \brief returns the max values of two integers
 *
 * @param a First integer
 * @param b Second Integer
 * @return The larger integer
 */
int iMAX(int a, int b){
    return a > b ? a:b;
}

/** \brief Finds the minimum value of an array and returns the index of it's location.  If there is a tie for the
 *      minimum value, one is selected randomly using Mersenne Twister number generator
 *
 * @param array Int array holding the values to be searched
 * @param length The length of the array holding values
 * @return Index of the minimum value
 */
int findMin(int *array, int length){
    int i=0;
    int min = array[0];

    for(i = 1; i < length; i++){
        if(array[i] < min){
            min = array[i];
        }
    }

    //holds indicies
    int *smallest = vectgenInt(length);
    int count = 0;

    for(i = 0; i < length; i++){
        if(array[i] == min){
            smallest[count] = i;
            count++;
        }
    }

    int index=0;
    if(count > 1) {
        index = smallest[(int) (genrand_real1() * count)];
    }else{
        index = smallest[0];
    }
    //return a random value job from the least values
    return index;
}

/** \brief Inserts a value at a specified index in the array. More space in the array is assumed, and existing values
 *      are shifted to the right to make room for the new value.
 *
 * @param array Int array where a value is being inserted
 * @param length The length of the filled part of the array (or number of elements in array, must be less than total
 *      array length)
 * @param index The index that the new value is being inserted at
 * @param value The value being inserted into the array
 */
void insertAt(int *array, int length, int index, int value){
    int i = 0;

    for(i = length - 1; i >= 0; i--){
        if(i > index){
            array[i] = array[i - 1];
        }else if(i == index){
            array[i] = value;
        }
    }
}
