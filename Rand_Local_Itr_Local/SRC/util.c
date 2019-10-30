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
    int m, n;
    matrix = matrixgen(trials, dim);

    for(m = 0; m < trials; m++){
        for(n = 0; n < dim; n++){
            matrix[m][n] = genrand_real1() * (highb - lowb) + lowb;
        }
    }
    return matrix;
}



/*! \brief Create vector with calloc()

 \param dim - dimension of the vector
 \return vect - the vector of size dim
*/
double *vectgen(int dim){
    double *vect;

    vect = (double *)calloc(dim, sizeof(double));
    if (vect == NULL){
        fprintf(stderr, "Out of memory: vectgen\n");
	}

    return vect;
}

/*! \brief Create 2d matrix with calloc()

 \param trials - number of vectors
 \param dim - dimension of each vector
 \return double pointer to a trials*dim matrix
*/

double **matrixgen(int trials, int dim) {
	int i;
	double **matrix;

	matrix = (double **)calloc(trials, sizeof(double));
	if (matrix == NULL){
        fprintf(stderr, "Out of memory: matrixgen\n");

	}
	for (i = 0; i < trials; i++){
        matrix[i] = vectgen(dim);
	}
    return matrix;
}

/*! \brief Free the memory from a matrix

	\param dim - dimension of the vectors in the matrix
*/
void freematrix(int trials, double **matrix){
    int i;

    for (i = 0; i < trials; i++)
        free(matrix[i]);

    free(matrix);

}

