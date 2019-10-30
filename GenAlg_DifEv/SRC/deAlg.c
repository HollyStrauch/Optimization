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
#include <time.h>
#include "deAlg.h"
#include "input.h"
#include "pop.h"
#include "util.h"
#include "MT/mt19937ar.h"
#include "ftns.h"
#include "algInput.h"

/** /brief deAlg sets up the Differential Evolution Algorithm, calls a strategy, and prints results to
 *      a csv file 'deResults.csv'
 *
 * @param algIn algInput struct pointer with data for running the algorithm
 */
void deAlg(algInput *algIn) {
    int i=0, e=0, j=0, c=0;
    input * in = getInput("ftnInput.txt");
    FILE * op;

    op = fopen("deResult.csv", "w");

    //for every function
    for (i = 0; i < in->numFtns; i++) {

            for (e = 0; e < algIn->experiments; e++) {
                fprintf(op, "F 1,");
                //initialize
                population *pop = initPop(in->popsize, in->dim);
                pop->popMatrix = fillmatrix(in->popsize, in->dim, pop->popMatrix, in->ftnBounds[3 * i + 1],
                                            in->ftnBounds[3 * i + 2]);

                calculateFit(pop, i, in);
                calculateBestFit(pop, in);
                fprintf(op, "%lf,", pop->bestFit);

                int callCount = 0;
                clock_t start = clock();
                for (j = 0; j < in->generations; j++) {
                    population *temp = initPop(in->popsize, in->dim);

                    //pick strategy

                    stSelect(algIn->strategy, in, callCount, pop, temp, i);

                    copyPop(pop, temp, in);

                    calculateFit(pop, i, in);
                    for (c = 0; c < in->popsize; c++) {
                        callCount++;
                    }
                    calculateBestFit(pop, in);
                    fprintf(op, "%lf,", pop->bestFit);

                    freePop(in->popsize, temp);
                }
                clock_t stop = clock();
                fprintf(op, "call/time:, %d, %lf", callCount, ((double) stop - (double) start) / CLOCKS_PER_SEC);
                fprintf(op, "\n");
                freePop(in->popsize, pop);
            }

    }
    printf("Output File Created");
}

/** /brief stSelect is a switch statement that chooses which of the 10 DE strategies to run
 *
 * @param algIn algInput struct with data for running the algorithms
 * @param in input struct with data for running functions
 * @param callCount A count of how many times one of the original 18 functions is called
 * @param pop population struct of the current population
 * @param temp population struct that stores the newly generated population
 * @param ftnI the current index for the ftnBounds data array
 * @return callCount
 */
int stSelect(int select, input *in, int callCount, population *pop, population *temp, const int ftnI){

    switch(select) {
        case 1:
            callCount = strategy1(in, pop, temp, ftnI, callCount);
            break;
        case 2:
            callCount = strategy2(in, pop, temp, ftnI, callCount);
            break;
        case 3:
            callCount = strategy3(in, pop, temp, ftnI, callCount);
            break;
        case 4:
            callCount = strategy4(in, pop, temp, ftnI, callCount);
            break;
        case 5:
            callCount = strategy5(in, pop, temp, ftnI, callCount);
            break;
        case 6:
            callCount = strategy6(in, pop, temp, ftnI, callCount);
            break;
        case 7:
            callCount = strategy7(in, pop, temp, ftnI, callCount);
            break;
        case 8:
            callCount = strategy8(in, pop, temp, ftnI, callCount);
            break;
        case 9:
            callCount = strategy9(in, pop, temp, ftnI, callCount);
            break;
        case 10:
            callCount = strategy10(in, pop, temp, ftnI, callCount);
            break;
    }

    return callCount;
}


/** /brief Strategy 1 for Differential Evolution Algorithm DE/best/1/exp
 *
 * @param in input struct with function data
 * @param pop population struct with the current population
 * @param temp population struct which holds the new generation being created
 * @param ftnI  The current index of the ftnBounds data array
 * @param callCount a count of how many times one of the 18 original functions is called
 * @return callCount
 */
int strategy1(input *in, population *pop, population *temp, const int ftnI, int callCount){
    int i=0;

    int best = calculateBestFit(pop, in);
    //best
    double *bestV = vectgenDoub(in->dim);
    copyVect(pop->popMatrix[best], bestV, in->dim);

    for(i = 0; i < in->popsize; i++) {
        double rand=0;
        double *trial = vectgenDoub(in->dim);

        //select 2 other random vectors
        int *randVectI = vectgenInt(2);
        uniqueRandI(randVectI, in->popsize, 2, best, i);

        double *r1 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[0]], r1, in->dim);

        double *r2 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[1]], r2, in->dim);

        //crossover and mutate
        int crpt = (int)(genrand_real1()*in->dim);
        int j = (crpt + 1) % in->dim;

        while(rand < in->crRate && (j % in->dim) != crpt){
            rand = genrand_real1();
            trial[j % in->dim] = bestV[j % in->dim] + in->F*(r1[j % in->dim] - r2[j % in->dim]);

            if(trial[j % in->dim] < in->ftnBounds[3*ftnI + 1]){
                trial[j % in->dim] = in->ftnBounds[3*ftnI + 1];
            }else if(trial[j % in->dim] > in->ftnBounds[3*ftnI + 2]){
                trial[j % in->dim] = in->ftnBounds[3*ftnI + 2];
            }
            j++;
        }
        while((j % in->dim) != crpt){
            trial[j % in->dim] = pop->popMatrix[i][j % in->dim];
            j++;
        }

        if(pop->fitness[i] < runftns(in->ftnBounds[3*ftnI], in->dim, trial)){
            copyVect(pop->popMatrix[i], temp->popMatrix[i], in->dim);
        }else{
            copyVect(trial, temp->popMatrix[i], in->dim);
        }
        callCount++;

        free(r1);
        free(r2);
        free(trial);
        free(randVectI);
    }
    free(bestV);
    return callCount;
}

/** /brief Strategy 2 for Differential Evolution Algorithm DE/rand/1/exp
 *
 * @param in input struct with function data
 * @param pop population struct with the current population
 * @param temp population struct which holds the new generation being created
 * @param ftnI  The current index of the ftnBounds data array
 * @param callCount a count of how many times one of the 18 original functions is called
 * @return callCount
 */
int strategy2(input *in, population *pop, population *temp, const int ftnI, int callCount){
    int *randVectI, i;

    for(i = 0; i < in->popsize; i++) {
        double rand=0;
        double *trial = vectgenDoub(in->dim);

        //select 2 other random vectors
        randVectI = vectgenInt(3);
        uniqueRandI(randVectI, in->popsize, 2, i, -1);

        double *r1 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[0]], r1, in->dim);

        double *r2 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[1]], r2, in->dim);

        double *r3 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[2]], r3, in->dim);

        //crossover and mutate
        int crpt = (int)(genrand_real1()*in->dim);
        int j = (crpt + 1) % in->dim;
        while(rand < in->crRate && (j % in->dim) != crpt){
            rand = genrand_real1();
            trial[j % in->dim] = r1[j % in->dim] + in->F*(r2[j % in->dim] - r3[j % in->dim]);

            if(trial[j % in->dim] < in->ftnBounds[3*ftnI + 1]){
                trial[j % in->dim] = in->ftnBounds[3*ftnI + 1];
            }else if(trial[j % in->dim] > in->ftnBounds[3*ftnI + 2]){
                trial[j % in->dim] = in->ftnBounds[3*ftnI + 2];
            }
            j++;
        }
        while((j % in->dim) != crpt){
            trial[j % in->dim] = pop->popMatrix[i][j % in->dim];
            j++;
        }

        if(pop->fitness[i] < runftns(in->ftnBounds[3*ftnI], in->dim, trial)){
            copyVect(pop->popMatrix[i], temp->popMatrix[i], in->dim);
        }else{
            copyVect(trial, temp->popMatrix[i], in->dim);
        }
        callCount++;

        free(r1);
        free(r2);
        free(r3);
        free(trial);

    }

    return callCount;
}

/** /brief Strategy 3 for Differential Evolution Algorithm DE/rand-to-best/1/exp
 *
 * @param in input struct with function data
 * @param pop population struct with the current population
 * @param temp population struct which holds the new generation being created
 * @param ftnI  The current index of the ftnBounds data array
 * @param callCount a count of how many times one of the 18 original functions is called
 * @return callCount
 */
int strategy3(input *in, population *pop, population *temp, const int ftnI, int callCount){
    int i;
    int best = calculateBestFit(pop, in);
    //best
    double *bestV = vectgenDoub(in->dim);
    copyVect(pop->popMatrix[best], bestV, in->dim);

    for(i = 0; i < in->popsize; i++) {
        double rand=0;
        double *trial = vectgenDoub(in->dim);

        //select 2 other random vectors
        int *randVectI = vectgenInt(2);
        uniqueRandI(randVectI, in->popsize, 2, best, i);

        double *r1 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[0]], r1, in->dim);

        double *r2 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[1]], r2, in->dim);

        //crossover and mutate
        int crpt = (int)(genrand_real1()*in->dim);
        int j = (crpt + 1) % in->dim;

        while(rand < in->crRate && (j % in->dim) != crpt){
            rand = genrand_real1();
            trial[j % in->dim] = pop->popMatrix[i][j % in->dim] + (bestV[j % in->dim] - pop->popMatrix[i][j % in->dim])
                                 + in->F*(r1[j % in->dim] - r2[j % in->dim]);

            if(trial[j % in->dim] < in->ftnBounds[3*ftnI + 1]){
                trial[j % in->dim] = in->ftnBounds[3*ftnI + 1];
            }else if(trial[j % in->dim] > in->ftnBounds[3*ftnI + 2]){
                trial[j % in->dim] = in->ftnBounds[3*ftnI + 2];
            }
            j++;
        }
        while((j % in->dim) != crpt){
            trial[j % in->dim] = pop->popMatrix[i][j % in->dim];
            j++;
        }

        if(pop->fitness[i] < runftns(in->ftnBounds[3*ftnI], in->dim, trial)){
            copyVect(pop->popMatrix[i], temp->popMatrix[i], in->dim);
        }else{
            copyVect(trial, temp->popMatrix[i], in->dim);
        }
        callCount++;

        free(r1);
        free(r2);
        free(trial);

    }
    free(bestV);
    return callCount;
}

/** /brief Strategy 4 for Differential Evolution Algorithm DE/best/2/exp
 *
 * @param in input struct with function data
 * @param pop population struct with the current population
 * @param temp population struct which holds the new generation being created
 * @param ftnI  The current index of the ftnBounds data array
 * @param callCount a count of how many times one of the 18 original functions is called
 * @return callCount
 */
int strategy4(input *in, population *pop, population *temp, const int ftnI, int callCount){
    int i;

    int best = calculateBestFit(pop, in);
    //best
    double *bestV = vectgenDoub(in->dim);
    copyVect(pop->popMatrix[best], bestV, in->dim);

    for(i = 0; i < in->popsize; i++) {
        double rand=0;
        double *trial = vectgenDoub(in->dim);

        //select 2 other random vectors
        int *randVectI = vectgenInt(4);
        uniqueRandI(randVectI, in->popsize, 2, best, i);

        double *r1 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[0]], r1, in->dim);

        double *r2 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[1]], r2, in->dim);

        double *r3 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[2]], r3, in->dim);

        double *r4 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[3]], r4, in->dim);

        //crossover and mutate
        int crpt = (int)(genrand_real1()*in->dim);
        int j = (crpt + 1) % in->dim;

        while(rand < in->crRate && (j % in->dim) != crpt){
            rand = genrand_real1();
            trial[j % in->dim] = bestV[j % in->dim] + in->F*((r1[j % in->dim] + r2[j % in->dim])
                                                             - (r3[j % in->dim] + r4[j % in->dim]));

            if(trial[j % in->dim] < in->ftnBounds[3*ftnI + 1]){
                trial[j % in->dim] = in->ftnBounds[3*ftnI + 1];
            }else if(trial[j % in->dim] > in->ftnBounds[3*ftnI + 2]){
                trial[j % in->dim] = in->ftnBounds[3*ftnI + 2];
            }
            j++;
        }
        while((j % in->dim) != crpt){
            trial[j % in->dim] = pop->popMatrix[i][j % in->dim];
            j++;
        }

        if(pop->fitness[i] < runftns(in->ftnBounds[3*ftnI], in->dim, trial)){
            copyVect(pop->popMatrix[i], temp->popMatrix[i], in->dim);
        }else{
            copyVect(trial, temp->popMatrix[i], in->dim);
        }
        callCount++;

        free(r1);
        free(r2);
        free(r3);
        free(r4);
        free(trial);

    }
    free(bestV);
    return callCount;
}

/** \brief Strategy 5 for Differential Evolution Algorithm DE/rand/2/exp
 *
 * @param in input struct with function data
 * @param pop population struct with the current population
 * @param temp population struct which holds the new generation being created
 * @param ftnI  The current index of the ftnBounds data array
 * @param callCount a count of how many times one of the 18 original functions is called
 * @return callCount
 */
int strategy5(input *in, population *pop, population *temp, const int ftnI, int callCount){
    int i;

    for(i = 0; i < in->popsize; i++) {
        double rand=0;
        double *trial = vectgenDoub(in->dim);

        //select 2 other random vectors
        int *randVectI = vectgenInt(5);
        uniqueRandI(randVectI, in->popsize, 2, i, -1);

        double *r1 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[0]], r1, in->dim);

        double *r2 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[1]], r2, in->dim);

        double *r3 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[2]], r3, in->dim);

        double *r4 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[3]], r4, in->dim);

        double *r5 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[4]], r5, in->dim);

        //crossover and mutate
        int crpt = (int)(genrand_real1()*in->dim);
        int j = (crpt + 1) % in->dim;

        while(rand < in->crRate && (j % in->dim) != crpt){
            rand = genrand_real1();
            trial[j % in->dim] = r5[j % in->dim] + in->F*((r1[j % in->dim] + r2[j % in->dim])
                                                          - (r3[j % in->dim] + r4[j % in->dim]));

            if(trial[j % in->dim] < in->ftnBounds[3*ftnI + 1]){
                trial[j % in->dim] = in->ftnBounds[3*ftnI + 1];
            }else if(trial[j % in->dim] > in->ftnBounds[3*ftnI + 2]){
                trial[j % in->dim] = in->ftnBounds[3*ftnI + 2];
            }
            j++;
        }
        while((j % in->dim) != crpt){
            trial[j % in->dim] = pop->popMatrix[i][j % in->dim];
            j++;
        }

        if(pop->fitness[i] < runftns(in->ftnBounds[3*ftnI], in->dim, trial)){
            copyVect(pop->popMatrix[i], temp->popMatrix[i], in->dim);
        }else{
            copyVect(trial, temp->popMatrix[i], in->dim);
        }
        callCount++;

        free(r1);
        free(r2);
        free(r3);
        free(r4);
        free(r5);
        free(trial);

    }
    return callCount;
}

/** \brief Strategy 6 for Differential Evolution Algorithm DE/best/1/bin
 *
 * @param in input struct with function data
 * @param pop population struct with the current population
 * @param temp population struct which holds the new generation being created
 * @param ftnI  The current index of the ftnBounds data array
 * @param callCount a count of how many times one of the 18 original functions is called
 * @return callCount
 */
int strategy6(input *in, population *pop, population *temp, const int ftnI, int callCount){
    int i, j;
    int best = calculateBestFit(pop, in);
    //best
    double *bestV = vectgenDoub(in->dim);
    copyVect(pop->popMatrix[best], bestV, in->dim);

    for(i = 0; i < in->popsize; i++) {
        double rand=0;
        double *trial = vectgenDoub(in->dim);

        //select 2 other random vectors
        int *randVectI = vectgenInt(2);
        uniqueRandI(randVectI, in->popsize, 2, best, i);

        double *r1 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[0]], r1, in->dim);

        double *r2 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[1]], r2, in->dim);

        //crossover and mutate
        int crpt = (int)(genrand_real1()*in->dim);

        for(j = (crpt + 1) % in->dim; (j % in->dim) != crpt; j++){
            rand = genrand_real1();

            if(rand < in->crRate) {
                trial[j % in->dim] = bestV[j % in->dim] + in->F * (r1[j % in->dim] - r2[j % in->dim]);

                if (trial[j % in->dim] < in->ftnBounds[3 * ftnI + 1]) {
                    trial[j % in->dim] = in->ftnBounds[3 * ftnI + 1];
                } else if (trial[j % in->dim] > in->ftnBounds[3 * ftnI + 2]) {
                    trial[j % in->dim] = in->ftnBounds[3 * ftnI + 2];
                }
            }else{
                trial[j % in->dim] = pop->popMatrix[i][j % in->dim];
            }
        }

        if(pop->fitness[i] < runftns(in->ftnBounds[3*ftnI], in->dim, trial)){
            copyVect(pop->popMatrix[i], temp->popMatrix[i], in->dim);
        }else{
            copyVect(trial, temp->popMatrix[i], in->dim);
        }
        callCount++;

        free(r1);
        free(r2);
        free(trial);

    }
    free(bestV);
    return callCount;
}

/** \brief Strategy 7 for Differential Evolution Algorithm DE/rand/1/bin
 *
 * @param in input struct with function data
 * @param pop population struct with the current population
 * @param temp population struct which holds the new generation being created
 * @param ftnI  The current index of the ftnBounds data array
 * @param callCount a count of how many times one of the 18 original functions is called
 * @return callCount
 */
int strategy7(input *in, population *pop, population *temp, const int ftnI, int callCount){
    int *randVectI, i, j;

    for(i = 0; i < in->popsize; i++) {
        double rand=0;
        double *trial = vectgenDoub(in->dim);

        //select 2 other random vectors
        randVectI = vectgenInt(3);
        uniqueRandI(randVectI, in->popsize, 2, i, -1);

        double *r1 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[0]], r1, in->dim);

        double *r2 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[1]], r2, in->dim);

        double *r3 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[2]], r3, in->dim);

        //crossover and mutate
        int crpt = (int)(genrand_real1()*in->dim);

        for(j = (crpt + 1) % in->dim; (j % in->dim) != crpt; j++){
            rand = genrand_real1();

            if(rand < in->crRate) {
                trial[j % in->dim] = r1[j % in->dim] + in->F*(r2[j % in->dim] - r3[j % in->dim]);

                if (trial[j % in->dim] < in->ftnBounds[3 * ftnI + 1]) {
                    trial[j % in->dim] = in->ftnBounds[3 * ftnI + 1];
                } else if (trial[j % in->dim] > in->ftnBounds[3 * ftnI + 2]) {
                    trial[j % in->dim] = in->ftnBounds[3 * ftnI + 2];
                }
            }else{
                trial[j % in->dim] = pop->popMatrix[i][j % in->dim];
            }
        }

        if(pop->fitness[i] < runftns(in->ftnBounds[3*ftnI], in->dim, trial)){
            copyVect(pop->popMatrix[i], temp->popMatrix[i], in->dim);
        }else{
            copyVect(trial, temp->popMatrix[i], in->dim);
        }
        callCount++;

        free(r1);
        free(r2);
        free(r3);
        free(trial);
        free(randVectI);
    }
    return callCount;
}

/** \brief Strategy 8 for Differential Evolution Algorithm DE/rand-to-best/1/bin
 *
 * @param in input struct with function data
 * @param pop population struct with the current population
 * @param temp population struct which holds the new generation being created
 * @param ftnI  The current index of the ftnBounds data array
 * @param callCount a count of how many times one of the 18 original functions is called
 * @return callCount
 */
int strategy8(input *in, population *pop, population *temp, const int ftnI, int callCount){
    int i, j;

    int best = calculateBestFit(pop, in);
    //best
    double *bestV = vectgenDoub(in->dim);
    copyVect(pop->popMatrix[best], bestV, in->dim);

    for(i = 0; i < in->popsize; i++) {
        double rand=0;
        double *trial = vectgenDoub(in->dim);

        //select 2 other random vectors
        int *randVectI = vectgenInt(2);
        uniqueRandI(randVectI, in->popsize, 2, best, i);

        double *r1 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[0]], r1, in->dim);

        double *r2 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[1]], r2, in->dim);

        //crossover and mutate
        int crpt = (int)(genrand_real1()*in->dim);

        for(j = (crpt + 1) % in->dim; (j % in->dim) != crpt; j++){
            rand = genrand_real1();

            if(rand < in->crRate) {
                trial[j % in->dim] = pop->popMatrix[i][j % in->dim] + (bestV[j % in->dim] - pop->popMatrix[i][j % in->dim])
                                     + in->F*(r1[j % in->dim] - r2[j % in->dim]);

                if (trial[j % in->dim] < in->ftnBounds[3 * ftnI + 1]) {
                    trial[j % in->dim] = in->ftnBounds[3 * ftnI + 1];
                } else if (trial[j % in->dim] > in->ftnBounds[3 * ftnI + 2]) {
                    trial[j % in->dim] = in->ftnBounds[3 * ftnI + 2];
                }
            }else{
                trial[j % in->dim] = pop->popMatrix[i][j % in->dim];
            }
        }

        if(pop->fitness[i] < runftns(in->ftnBounds[3*ftnI], in->dim, trial)){
            copyVect(pop->popMatrix[i], temp->popMatrix[i], in->dim);
        }else{
            copyVect(trial, temp->popMatrix[i], in->dim);
        }
        callCount++;

        free(r1);
        free(r2);
        free(trial);
        free(randVectI);
    }
    free(bestV);
    return callCount;
}

/** \brief Strategy 9 for Differential Evolution Algorithm DE/best/2/bin
 *
 * @param in input struct with function data
 * @param pop population struct with the current population
 * @param temp population struct which holds the new generation being created
 * @param ftnI  The current index of the ftnBounds data array
 * @param callCount a count of how many times one of the 18 original functions is called
 * @return callCount
 */
int strategy9(input *in, population *pop, population *temp, const int ftnI, int callCount){
    int i, j;

    int best = calculateBestFit(pop, in);
    //best
    double *bestV = vectgenDoub(in->dim);
    copyVect(pop->popMatrix[best], bestV, in->dim);

    for(i = 0; i < in->popsize; i++) {
        double rand=0;
        double *trial = vectgenDoub(in->dim);

        //select 2 other random vectors
        int *randVectI = vectgenInt(4);
        uniqueRandI(randVectI, in->popsize, 2, best, i);

        double *r1 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[0]], r1, in->dim);

        double *r2 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[1]], r2, in->dim);

        double *r3 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[2]], r3, in->dim);

        double *r4 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[3]], r4, in->dim);

        //crossover and mutate
        int crpt = (int)(genrand_real1()*in->dim);

        for(j = (crpt + 1) % in->dim; (j % in->dim) != crpt; j++){
            rand = genrand_real1();

            if(rand < in->crRate) {
                trial[j % in->dim] = bestV[j % in->dim] + in->F*((r1[j % in->dim] + r2[j % in->dim])
                                                                 - (r3[j % in->dim] + r4[j % in->dim]));

                if (trial[j % in->dim] < in->ftnBounds[3 * ftnI + 1]) {
                    trial[j % in->dim] = in->ftnBounds[3 * ftnI + 1];
                } else if (trial[j % in->dim] > in->ftnBounds[3 * ftnI + 2]) {
                    trial[j % in->dim] = in->ftnBounds[3 * ftnI + 2];
                }
            }else{
                trial[j % in->dim] = pop->popMatrix[i][j % in->dim];
            }
        }


        if(pop->fitness[i] < runftns(in->ftnBounds[3*ftnI], in->dim, trial)){
            copyVect(pop->popMatrix[i], temp->popMatrix[i], in->dim);
        }else{
            copyVect(trial, temp->popMatrix[i], in->dim);
        }
        callCount++;

        free(r1);
        free(r2);
        free(r3);
        free(r4);
        free(trial);
        free(randVectI);

    }
    free(bestV);
    return callCount;
}

/** \brief Strategy 10 for Differential Evolution Algorithm DE/rand/2/bin
 *
 * @param in input struct with function data
 * @param pop population struct with the current population
 * @param temp population struct which holds the new generation being created
 * @param ftnI  The current index of the ftnBounds data array
 * @param callCount a count of how many times one of the 18 original functions is called
 * @return callCount
 */
int strategy10(input *in, population *pop, population *temp, const int ftnI, int callCount){
    int i, j;
    for(i = 0; i < in->popsize; i++) {
        double rand=0;
        double *trial = vectgenDoub(in->dim);

        //select 2 other random vectors
        int *randVectI = vectgenInt(5);
        uniqueRandI(randVectI, in->popsize, 2, i, -1);

        double *r1 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[0]], r1, in->dim);

        double *r2 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[1]], r2, in->dim);

        double *r3 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[2]], r3, in->dim);

        double *r4 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[3]], r4, in->dim);

        double *r5 = vectgenDoub(in->dim);
        copyVect(pop->popMatrix[randVectI[4]], r5, in->dim);

        //crossover and mutate
        int crpt = (int)(genrand_real1()*in->dim);
        for(j = (crpt + 1) % in->dim; (j % in->dim) != crpt; j++){
            rand = genrand_real1();

            if(rand < in->crRate) {
                trial[j % in->dim] = r5[j % in->dim] + in->F*((r1[j % in->dim] + r2[j % in->dim])
                                                              - (r3[j % in->dim] + r4[j % in->dim]));

                if (trial[j % in->dim] < in->ftnBounds[3 * ftnI + 1]) {
                    trial[j % in->dim] = in->ftnBounds[3 * ftnI + 1];
                } else if (trial[j % in->dim] > in->ftnBounds[3 * ftnI + 2]) {
                    trial[j % in->dim] = in->ftnBounds[3 * ftnI + 2];
                }
            }else{
                trial[j % in->dim] = pop->popMatrix[i][j % in->dim];
            }
        }

        if(pop->fitness[i] < runftns(in->ftnBounds[3*ftnI], in->dim, trial)){
            copyVect(pop->popMatrix[i], temp->popMatrix[i], in->dim);
        }else{
            copyVect(trial, temp->popMatrix[i], in->dim);
        }
        callCount++;

        free(r1);
        free(r2);
        free(r3);
        free(r4);
        free(r5);
        free(trial);
        free(randVectI);
    }
    return callCount;
}