#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ftnslst.h"



/*! \brief Create vector with calloc()

 \param dim - dimension of the vector
 \return vect - the vector of size dim
*/
double *vectgen(int dim){
    int i;
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
 \return double pointer to a trials x dim matrix
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

