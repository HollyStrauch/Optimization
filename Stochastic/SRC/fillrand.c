#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "MT/mt19937ar.h"

/*! \brief Use the Mersenne Twister random number generator to fill a matrix
	with random values within set bounds.

	\param trials the number of vectors in the matrix
	\param dim length of the vectors
	\param **matrix the two dimensional matrix
	\param highb the upper bound for the random generator
	\param lowb the lower bound for the random generator
	\return matrix the two dimensional matrix that has been filled
*/

double **fillmatrix(int trials, int dim, double **matrix, double highb, double lowb){
    int seed, m, n;
    double value; //for testing only

    seed = getpid();
    init_genrand(seed);


    for(m = 0; m < trials; m++){
        for(n = 0; n < dim; n++){
            value = genrand_real1() * (highb - lowb) + lowb;
            matrix[m][n] = value;
        }
    }
    return matrix;
}
