#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "ftnslst.h"
#include "matrixgen.h"
#include "ftnInput.h"
#include "fillrand.h"


/*! \brief Gets input from ftnInput struct and runs through the equations
            specified.  Solutions are printed to CSV file

	\param *filename is the name of the file being read in from
	\param *op the file pointer open in main() that will be written out to.
	\return 0 if executed.
*/
int run(const char *filename, FILE *op){
    int i, j, k;
    clock_t start, stop;
    ftnInput *input;
    double **matrix, *solutions, time;

    input = getInput(filename);

    //loop for each dimension
    for(i = 0; i < input->numDim; i++){

        fprintf(op, "%d\n", input->dimensions[i]);

        //run through each function
        for(j = 0; j < input->numFtns; j++){
            matrix = matrixgen(input->trials, input->dimensions[i]);
            solutions = (double *)calloc(input->trials, sizeof(double));

            matrix = fillmatrix(input->trials, input->dimensions[i], matrix, input->ftnBounds[3*j+2], input->ftnBounds[3*j+1]);

            start = clock();
            //fill array with solutions
            for(k = 0; k < input->trials; k++){
                solutions[k] = runftns(input->ftnBounds[3*j], input->dimensions[i], matrix[k]);
            }

            stop = clock();
            //print solutions
            for(k = 0; k < input->trials; k++){
                fprintf(op, "%lf,", solutions[k]);
            }

            time = ((double)stop - (double)start)/CLOCKS_PER_SEC;

            fprintf(op, "\n");
            fprintf(op, "time:,%lf\n", time);

            free(solutions);
            freematrix(input->trials, matrix);
        }
    }

    return 0;
}
