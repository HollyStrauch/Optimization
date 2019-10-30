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
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include "MT/mt19937ar.h"
#include "util.h"

/*! \brief Use the Mersenne Twister random number generator to fill a matrix
	with random values within set bounds.

	\param trials the number of vectors in the matrix
	\param dim length of the vectors
	\param **matrix the two dimensional matrix
	\param highb the upper bound for the random generator
	\param lowb the lower bound for the random generator
	\return matrix the two dimensional matrix that has been filled
*/

double **fillmatrix(int trials, int dim, double **matrix, double lowb, double highb){
    int m=0, n=0;

    for(m = 0; m < trials; m++){
        for(n = 0; n < dim; n++){
            matrix[m][n] = genrand_real1() * (highb - lowb) + lowb;
        }
    }
    return matrix;
}



/*! \brief Create double vector with calloc()

 \param dim - dimension of the vector
 \return vect - the vector of size dim
*/
double *vectgenDoub(int dim){
    double *vect;

    vect = (double *)calloc(dim, sizeof(double));
    if (vect == NULL){
        fprintf(stderr, "Out of memory: vectgenDoub\n");
	}

    return vect;
}

/*! \brief Create int vector with calloc()

 \param dim The dimension of the vector
 \return vect Integer vector of size dim
*/
int *vectgenInt(int dim){
    int *vect;

    vect = (int *)calloc(dim, sizeof(int));
    if (vect == NULL){
        fprintf(stderr, "Out of memory: vectgenInt\n");
    }

    return vect;
}

/*! \brief Create 2d matrix with calloc()

 \param trials - number of vectors
 \param dim - dimension of each vector
 \return double pointer to a trials*dim matrix
*/
double **matrixgen(int trials, int dim) {
	int i=0;
	double **matrix;

	matrix = (double **)calloc(trials, sizeof(double));
	if (matrix == NULL){
        fprintf(stderr, "Out of memory: matrixgen\n");

	}
	for (i = 0; i < trials; i++){
        matrix[i] = vectgenDoub(dim);
	}
    return matrix;
}



/*! \brief Free the memory from a matrix

	\param dim - dimension of the vectors in the matrix
*/
void freematrix(int trials, double **matrix){
    int i=0;

    for (i = 0; i < trials; i++)
        free(matrix[i]);

    free(matrix);

}

/*! \brief Generate uniquely random indices using Knuth's algorithm.  Numbers 0 - N-1 will be generated.
 *      Method can accept an integer to be excluded from the generated numbers.

 \param *ind Array to hold the number of indices being generated
 \param sourceSize The size of the source vector
 \param unums The number of unique numbers being generated
 \param exclude An integer to be excluded from the generated numbers
 \return *ind Array filled with uniquely random indices in ascending order
*/
int * uniqueRandI(int * ind, int sourceSize, int unums, int exclude1, int exclude2){
    int unrem = unums;
    int srem = sourceSize;
    int i=0, j = 0;

    for(i = 0; i < sourceSize && j < unums; i++){
        srem = sourceSize - i;
        unrem = unums - j;

        if ((int)(genrand_real1() * sourceSize) % srem < unrem && (i != exclude1 || i != exclude2)){
            ind[j++] = i;
        }
    }

    return ind;
}

/** /brief Copies one vector into another
 *
 * @param source The vector being copied
 * @param dest The vector being copied to
 * @param length The lenght of the vectors
 */
void copyVect(double *source, double *dest, int length){
    int i=0;

    for(i = 0; i < length; i++){
        dest[i] =  source[i];
    }
}

/** /brief Modified Quick Sort Algorithm based on DepthLmitedQuickSort() from Microsoft Reference Source.  An array
 *      of indices is sorted based on the values in a fitness array in descending order
 *
 * @param left The left most index of the area being sorted. Starting value is 0;
 * @param right The left most index of the area being sorted. Starting value is length - 1;
 * @param fitCopy An array of values which the sortin is based off of.
 * @param indices An array of indices 0 through N-1
 */
void quickSort(int left, int right, double *fitCopy, int *indices)
{
    do
    {
        int i = left;
        int j = right;
        int middle = (j + i) / 2;

        // pre-sort the low, middle (pivot), and high values in place.
        if( fitCopy[i] > fitCopy[middle]){
            swap(i, middle, fitCopy, indices);
        }
        if( fitCopy[i] > fitCopy[j]){
            swap(i, j, fitCopy, indices);
        }
        if( fitCopy[middle] > fitCopy[j]){
            swap(middle, j, fitCopy, indices);
        }

        do
        {

                while(fitCopy[i] > fitCopy[middle]) i++;
                while(fitCopy[j] < fitCopy[middle]) j--;

            //assert(i >= left && j <= right, "(i>=left && j<=right)  Sort failed - Is your IComparer bogus?");
            if (i > j) break;
            if (i < j)
            {
                swap(i, j, fitCopy, indices);
            }
            i++;
            j--;
        } while (i <= j);

        // The next iteration of the while loop is to "recursively" sort the larger half of the array and the
        // following calls recrusively sort the smaller half.

        if (j - left <= right - i)
        {
            if (left < j) quickSort(left, j, fitCopy, indices);
            left = i;
        }
        else
        {
            if (i < right) quickSort(i, right, fitCopy, indices);
            right = j;
        }
    } while (left < right);
}

/** /brief Swaps two values inside an array of values and an array of indices respectivly.  Used in quickSort().
 *
 * @param index1 First index to be swapped
 * @param index2 Second index to be swapped
 * @param fitness Array of values
 * @param ind Array of indices
 */
void swap(int index1, int index2, double * fitness, int * ind){
    double temp=0.0;
    int tempi=0;

    temp = fitness[index1];
    fitness[index1] = fitness[index2];
    fitness[index2] = temp;

    tempi = ind[index1];
    ind[index1]= ind[index2];
    ind[index2] = tempi;
}
