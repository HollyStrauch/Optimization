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
#include <math.h>
#include <time.h>
#include "gAlg.h"
#include "pop.h"
#include "util.h"
#include "input.h"
#include "MT/mt19937ar.h"
#include "ftns.h"
#include "algInput.h"

/** /brief Opens a csv file to print to and runs genAlg() with roulette wheel or tournement selection
 *
 * @param algIn algInput struct with data to run experiments
 */
void selectGA(algInput *algIn){
    input * in = getInput("ftnInput.txt");
    FILE * op;
    int i=0, j=0;

    op = fopen("gaResult.csv", "w");

    for(i = 0; i < in->numFtns; i++) {
        fprintf(op, "\n F %d\n", i+1);
        printf("Function %d running\n", i+1);
        for(j = 0; j < algIn->experiments; j++) {
            genAlg(in, algIn->select, op, i);
        }
    }

    fclose(op);

}

/** /brief Runs the Genetic Algorithm and prints to the specified file
 *
 * @param in Input struct with function and algorithm values
 * @param select An integer dictating which selection method to run
 * @param op The File pointer to print out to
 * @param i The current index in the ftnBounds array
 */
void genAlg(input * in, int select, FILE *op, int i) {
    int j=0, c=0, g=0;
    int elite = (int) (in->er * in->popsize);
    population *newpop;

    int callCount = 0;
    clock_t start = clock();

    //inital population
    population *pop = initPop(in->popsize, in->dim);
    pop->popMatrix = fillmatrix(in->popsize, in->dim, pop->popMatrix, in->ftnBounds[3 * i + 1],
                                in->ftnBounds[3 * i + 2]);

    calculateFit(pop, i, in);
    for (c = 0; c < in->popsize; c++) {
        callCount++;
    }

    setOrder(pop, in);


    for (g = 0; g < in->generations; g++) {
        newpop = initPop(in->popsize, in->dim);

        for (j = 0; j < in->popsize; j += 2) {
            double *p1 = vectgenDoub(in->dim);
            double *p2 = vectgenDoub(in->dim);
            double *o1 = vectgenDoub(in->dim);
            double *o2 = vectgenDoub(in->dim);
            int p1I;
            int p2I;
            //select parents

            if (select == 1) {
                //tournament
                p1I = tournSelect(pop, in, -1);
                p2I = tournSelect(pop, in, p1I);
                copyVect(pop->popMatrix[pop->order[p1I]], p1, in->dim);
                copyVect(pop->popMatrix[pop->order[p2I]], p2, in->dim);
            } else if (select == 2) {
                //roulette

                int *indices = vectgenInt(2);
                indices = rouletteSelect(pop, in, indices);
                p1I = indices[0];
                p2I = indices[1];
                copyVect(pop->popMatrix[p1I], p1, in->dim);
                copyVect(pop->popMatrix[p2I], p2, in->dim);
                free(indices);
            } else {
                fprintf(stderr, "Invalid input value");
                exit(1);
            }

            crossOver(o1, o2, p1, p2, in);

            callCount += 2;
            pickBest(o1, o2, p1I, p2I, i, in, pop);
            free(p1);
            free(p2);

            mutate(o1, in, i);
            mutate(o2, in, i);
            copyVect(o1, newpop->popMatrix[j], in->dim);
            copyVect(o1, newpop->popMatrix[j +1], in->dim);

            free(o1);
            free(o2);
            //end for
        }

        calculateFit(newpop, i, in);
        for (c = 0; c < in->popsize; c++) {
            callCount++;
        }

        setOrder(newpop, in);

        reduce(pop, newpop, in, elite);
        setOrder(pop, in);
        calculateBestFit(pop, in);

        fprintf(op, "%lf,", pop->bestFit);
        freePop(in->popsize, newpop);

    }
    clock_t stop = clock();
    fprintf(op, "call/time:, %d, %lf", callCount, ((double) stop - (double) start) / CLOCKS_PER_SEC);
    fprintf(op, "\n");

}


/** /brief pickBest compares the children to the parents.  If a child is worse than both parents, that offspring
 *      pointer will be set to one of the parents.
 *
 * @param off1
 * @param off2
 * @param p1I
 * @param p2I
 * @param index
 * @param in
 * @param pop
 */
void pickBest(double *off1, double *off2, int p1I, int p2I, int index, input *in, population * pop){
    double oFit1 = runftns(in->ftnBounds[3*index], in->dim, off1);
    double oFit2 = runftns(in->ftnBounds[3*index], in->dim, off2);

    if(oFit1 > pop->fitness[p1I] && oFit1 > pop->fitness[p2I]) {
            copyVect(pop->popMatrix[pop->order[p1I]], off1, in->dim);
    }

    if(oFit2 > pop->fitness[p2I] && oFit2 > pop->fitness[p1I]){
            copyVect(pop->popMatrix[pop->order[p2I]], off2, in->dim);
    }

}

/** /brief reduce finalizes the next generation in a population struct pop by taking the top elite vectors from the
 *      previous generation, then filling in the remaining population with the best results from the newly created
 *      offspring.  The populations must have their order set for the function to work properly.
 *
 * @param pop Previous generation
 * @param newpop Offspring from previous generation
 * @param in input struct with function data
 * @param elite The number of vectors to transfer from the previous generation
 */
void reduce(population *pop, population *newpop, input *in, int elite){
    double ** tempPop = matrixgen(in->popsize, in->dim);
    double * tempFit = vectgenDoub(in->popsize);
    int i=0;

    int count = 0;
    int index = 0;
    //move elite into temp
    for(i = in->popsize - 1; i >= in->popsize - elite; i--){
        copyVect(pop->popMatrix[pop->order[i]], tempPop[index], in->dim);
        tempFit[index] = pop->fitness[pop->order[i]];
        count++;
        index++;
    }

    //move over best children
    for(i = in->popsize - 1; i >= elite; i--){
        copyVect(newpop->popMatrix[newpop->order[i]], tempPop[index], in->dim);
        tempFit[index] = newpop->fitness[newpop->order[i]];
        count++;
        index++;
    }

    for(i = 0; i < in->popsize; i++){
        copyVect(tempPop[i], pop->popMatrix[i], in->dim);
        pop->fitness[i] = tempFit[i];
    }

    freematrix(in->popsize, tempPop);
    free(tempFit);
}

/** /brief  crossOver creates two offspring vectors by taking two parents, picking an index, placing the values
 *  preceding that point into one offspring and those after into the other offspring, "crossing" the vectors.
 *  A random number is generated and crossover will only occur if it is lower than an inputted crossover rate
 *
 * @param o1 Empty offspring vector
 * @param o2 Empty offspring vector
 * @param p1 parent vector from current population
 * @param p2 parent vector from current population
 * @param in input struct with function and algorithm values
 */
void crossOver(double * o1, double *o2, double *p1, double *p2, input *in){
    int i = 0;
    int randDim;

    if ((genrand_real1()) < in->crRate){
        randDim = (int) (genrand_real1() * in->dim);

        for(i = 0; i < randDim; i++) {
            o1[i] = p1[i];
            o2[i] = p2[i];
        }

        for(i = randDim; i < in->dim; i++){
            o1[i] = p2[i];
            o2[i] = p1[i];
        }
    }else{
        for(i = 0; i < in->dim; i++) {
            o1[i] = p1[i];
            o2[i] = p2[i];
        }
    }
}

/** /brief a vector is mutated if a randomly generated number is lower than an inputed mutation rate.  New values
 *  are checked to stay in function bounds.
 *
 * @param offspring Vector to be mutated
 * @param in input struct with function and algorithm values
 * @param index The current location in the ftnBounds array
 */
void mutate(double *offspring, input *in, int index){
    int i=0;
    for( i = 0; i < in->dim; i++){
        if(genrand_real1() < in->mRate){
            offspring[i] += (genrand_real1()*2.0 - 1.0) * (in->ftnBounds[3*index +2] - in->ftnBounds[3*index+1]) *
                    in->mRange * pow(2, (-1.0* genrand_real1()*in->mPrecision));

            if(offspring[i] < in->ftnBounds[3*index+1]){
                offspring[i] = in->ftnBounds[3*index+1];
            }else if(offspring[i] > in->ftnBounds[3*index+2]){
                offspring[i] = in->ftnBounds[3*index+2];
            }
        }

    }
}


/** /brief two vectors are chosen by selecting a group of vectors randomly, then choosing the best fit from that
 *      selection.  The number 'exclude' will be skipped over in this process.
 *
 * @param pop The population where the vectors are being chosen from
 * @param in input struct with function and algorithm values
 * @param exclude An index to be excluded from the selection
 * @return the index of the chosen vector
 */
int tournSelect(population * pop, input * in, int exclude){
    int i=0, best = 0;
    int tsize = (int)(in->popsize*.25);
    int *ind = vectgenInt(tsize);

    uniqueRandI(ind, in->popsize, tsize, exclude, -1);

    for(i = 1; i < tsize; i++){
        if(pop->fitness[ind[i]] < pop->fitness[ind[best]]){
            best = i;
        }
    }
    free(ind);
    return best;
}

/** /brief Finds the minimum value in a vectors
 *
 * @param vect The vector being searched
 * @param length The length of the vector
 * @return The minimum value found
 */
double findMin(double * vect, int length){
    double min = vect[0];
    int i=0;

    for(i = 1; i < length; i++){
        if (vect[i] < min){
            min = vect[i];
        }
    }
    return min;
}

/** /brief Chooses two vectors by created a normalized array with weighted values, and randomly selected a vector
 *      from the normalized array.
 *
 * @param pop The population the vectors are being chosen from
 * @param in input struct with function and algorithm values
 * @param indices An array of the two indices choses
 * @return a pointer to an array indeces[] with the two chosen indices.
 */
int *rouletteSelect(population * pop, input *in, int *indices) {
    double *norm = vectgenDoub(in->popsize);
    double min = findMin(pop->fitness, in->popsize);
    double sumAdj = 0;
    int i;

    for(i = 0; i < in->popsize; i++){
        norm[i] = pop->fitness[i] - min;
        sumAdj += norm[i];
    }

    double sumPb;
    for(i = 0; i < in->popsize; i++){
        norm[i] = 1 - norm[i]/sumAdj;
        sumPb += norm[i];
    }

    double normTot = 0;
    for(i = 0; i < in->popsize; i++){
        norm[i] = norm[i] / sumPb;
        normTot += norm[i];
    }

    double rand = (genrand_real1() * normTot);

    int select = 0;
    while (select < in->popsize - 1 && rand > 0) {
        rand -= norm[select];
        select++;
    }
    indices[0] = select;

    do{
        rand = (genrand_real1() * normTot);
        select = 0;

        while (select < in->popsize - 1 && rand > 0) {
            rand -= norm[select];
            select++;

        }
        indices[1] = select;

    }while(indices[0] == indices[1]);

    free(norm);
    return indices;
}

