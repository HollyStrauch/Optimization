#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "ftnInput.h"
#include "ftns.h"
#include "util.h"
#include "searchAlgs.h"

/*!/brief getBest() creates a matrix of random values and calculates which vector has the best solution
 *      for the given function. Updates vector parameter to be the best of the solution inputs
 *
 * @param dim -the dimension of the vectors/number of matrix columns
 * @param input -ftnInput struct with read-in data
 * @param index - the current location to fetch data from in input->ftnBounds
 * @param bestSolution - the vector which currently yeilds the best result
 * @return bestFit - the lowest result found from running the vectors
 */
double getBest(int dim, ftnInput * input, int index, double *bestSolution){
    double **matrix, current, bestFit;
    int i, j;

    matrix = fillmatrix(input->trials, dim, matrix, input->ftnBounds[4*index + 1], input->ftnBounds[4*index + 2]);

    //set initial values
    bestFit = runftns(input->ftnBounds[4*index], dim, matrix[0]);
    for(j = 0; j < dim; j++) {
        bestSolution[j] = matrix[0][j];
    }
    //find best
    for(i = 1; i < input->trials; i++){
            current = runftns(input->ftnBounds[4*index], dim, matrix[i]);
            if(current < bestFit){
                bestFit = current;
                for(j = 0; j < dim; j++) {
                    bestSolution[j] = matrix[i][j];
                }
            }
    }

    freematrix(dim, matrix);
    return bestFit;
}

/*!/brief randWalk() finds the best overall solution for a function from a number of solutions,
 *  each of which were the best result generated from a matrix.  Process is timed and results
 *  printed to an external file.
 *
 * @param input - initialized ftnInput struct with function and run data
 * @return bestFit - the best overall solution found
 */
double randWalk(ftnInput * input){
    double *bestSolution, current=0, bestFit=0;
    int i, j, k;
    FILE *op;
    clock_t start, stop;

    op = fopen("randwalk.csv", "w");
    //for each dimension
    for (i = 0; i < input->numDim; i++){
        start = clock();
        fprintf(op, "%d\n", input->dimensions[i]);

        //For each function
        for(j = 0; j < input->numFtns; j++){
            fprintf(op, "FUNCTION #%lf\n", input->ftnBounds[4*j]);
            bestSolution = vectgen(input->dimensions[i]);

            //set initial result as best
            fprintf(op, "%lf,", current = getBest(input->dimensions[i], input, j, bestSolution));

            bestFit = current;

            //run itr times
            for(k = 1; k < input->itr; k++){
                //print the best solution from itr # of matrices
                fprintf(op, "%lf,", current = getBest(input->dimensions[i], input, j, bestSolution));

                if(current < bestFit){
                    bestFit = current;
                }
            }

            fprintf(op, "bestFit: %lf\n", bestFit);
            free(bestSolution);
        }
        stop = clock();
        fprintf(op, "time: %lf,\n", ((double)stop - (double)start)/CLOCKS_PER_SEC);
    }
    fclose(op);
    printf("Output file created");
    return bestFit;
}

/*! /brief localSearch() takes the best solution vector from a random matrix and finds its neighbor.  Process is
 *  repeated until the neighbor no longer yields a better result. Each dimension is timed and the best solution
 *  is printed out. General local search is run with param itr set to 1, 1>makes the function an Iterative Local
 *  Search
 *
 * @param input - ftnInput struct with function and run data
 * @param itr  - the number of different times the local search process will run for each function
 */
void localSearch(ftnInput *input, int itr){
    double *xVect, xResult, bestResult;
    int i=0, j=0, k=0;
    FILE * op;
    clock_t start, stop;

    if(itr == 1) {
        op = fopen("localSearch.csv", "w");
    }else{
        op = fopen("itrLocSearch.csv", "w");
    }
    //for each dimension
    for(i = 0; i < input->numDim; i++){
        start = clock();
        fprintf(op, "dim: %d\n", input->dimensions[i]);

        //for each ftn input->numFtns
        for(j = 0; j < input->numFtns; j++){
            printf("running ftn %d dimension %d\n", (int)input->ftnBounds[j*4], input->dimensions[i]);
            fprintf(op, "ftn %d,", (int)input->ftnBounds[j*4]);

            xVect = vectgen(input->dimensions[i]);

            //set initial overall best
            xResult = getBest(input->dimensions[i], input, j, xVect);
            xResult = bestNeighbor(input, input->dimensions[i], j, xVect, xResult);
            bestResult = xResult;
            fprintf(op, "%lf,", xResult);
            free(xVect);
            //itr = 1 for localSearch
            for(k = 1; k < itr; k++) {
                xVect = vectgen(input->dimensions[i]);

                //start with best solution from a random matrix
                xResult = getBest(input->dimensions[i], input, j, xVect);
                xResult = bestNeighbor(input, input->dimensions[i], j, xVect, xResult);
                fprintf(op, "%lf,", xResult);

                if(xResult < bestResult){
                    bestResult = xResult;
                }

                ///

                free(xVect);
            }
            if (itr > 1) {
                fprintf(op, "best: %lf,", bestResult);
            }
            fprintf(op, "\n");
        }
        stop = clock();
        //put 'time' back in
        fprintf(op, ",%lf,\n\n", ((double)stop - (double)start)/CLOCKS_PER_SEC);
    }

    fclose(op);
    printf("Output file created");
}

/*!/brief bestNeighbor() generates the neighbors of the given vector with the mapping relation
 *  Xnew[i] = X[i] - alpha * (f(y) - f(x)). Alpha is specified in the input file.  A new neighbor
 *  is calculated until there is not better result found.
 *
 * @param input - input struct with function and run data
 * @param dim  - dimension of the vector
 * @param index - current index to fetch data from input->ftnBounds
 * @param xVect  - original vector from which the neighbor is generated
 * @param xResult - the fitness of xVect
 * @return xResult - the best neighbor found
 */
double bestNeighbor(ftnInput *input, int dim, int index, double *xVect, double xResult){
    double *yVect, *newVect, yResult, newResult;
    int t, i, improved=1;
    double alpha = input->ftnBounds[index*4 + 3];

    while (improved) {
        improved = 0;
        yVect = vectgen(dim);
        newVect = vectgen(dim);

        for (t = 0; t < dim; t++) {
            newVect[t] = xVect[t];
            yVect[t] = xVect[t];
        }

        //compare each dimensions
        for (i = 0; i < dim; i++) {

            yVect[i] = xVect[i] + alpha;

            if (yVect[i] > input->ftnBounds[index * 4 + 2]) {
                yVect[i] = input->ftnBounds[index * 4 + 2];
            }

            yResult = runftns(input->ftnBounds[index * 4], dim, yVect);

            //mapping relation
            newVect[i] = xVect[i] - alpha * (yResult - xResult);
            //check bounds
            if (newVect[i] > input->ftnBounds[index * 4 + 2]) {
                newVect[i] = input->ftnBounds[index * 4 + 2];
            } else if (newVect[i] < input->ftnBounds[index * 4 + 1]) {
                newVect[i] = input->ftnBounds[index * 4 + 1];
            }
            //reset y
            yVect[i] = xVect[i];
        }

        newResult = runftns(input->ftnBounds[index * 4], dim, newVect);
        //stop at precision of
        if (xResult - newResult > .0001) {
            improved = 1;
            for (t = 0; t < dim; t++) {
                xVect[t] = newVect[t];
            }
            xResult = newResult;
        }
        free(yVect);
        free(newVect);
    }
    return xResult;
}

/*! /brief itrLocSearch() runs local search a specified number of times for each function
 *
 * @param input - an initialized ftnInput struct with function and run data
 */
void itrLocSearch(ftnInput *input){
    localSearch(input, input->itr);
}

