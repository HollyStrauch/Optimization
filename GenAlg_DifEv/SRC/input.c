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
#include "input.h"

/** /brief Initializes an input struct from data read in from a file
 *
 * @param filename
 * @return pointer to initialized struct
 */
input *getInput(const char *filename){
    input *in = (input *)calloc(1, sizeof(input));
    FILE *fp;
    int i=0;

    fp = fopen(filename, "r");
    if (fp == NULL){
        fprintf(stderr, "No such file: getInput\n");
        exit(-1);
    }

    fscanf(fp, "%d", &in->generations);
    fscanf(fp, "%d", &in->popsize);
    fscanf(fp, "%lf", &in->crRate);
    fscanf(fp, "%lf", &in->mRate);
    fscanf(fp, "%lf", &in->mRange);
    fscanf(fp, "%lf", &in->mPrecision);
    fscanf(fp, "%lf", &in->er);
    fscanf(fp, "%lf", &in->F);
    fscanf(fp, "%lf", &in->L);
    fscanf(fp, "%d", &in->dim);

    //scan in number of functions
    fscanf(fp, "%d", &in->numFtns);

    //create array and scan in functions and their bounds
    in->ftnBounds = (double *)calloc(in->numFtns * 3, sizeof(double));
    if (in->ftnBounds == NULL){
        fprintf(stderr, "Out of memory: ftnInput ftnBounds\n");
        exit(1);
    }

    for (i = 0; i < (in->numFtns * 4); i++){
        fscanf(fp, "%lf", &in->ftnBounds[i]);
    }

    fclose(fp);
    return in;
}
