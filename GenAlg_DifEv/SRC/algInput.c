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

#include "algInput.h"
#include <stdio.h>
#include <stdlib.h>

/** /brief Initializes the data in a algInput struct from a file, used for choosing algorithms
 *
 * @param filename The file being read in from
 * @return pointer to the initialized struct
 */
algInput *getAlgIn(const char *filename){
    algInput *algIn = (algInput *)calloc(1, sizeof(algInput));
    FILE *fp;
    int i;

    fp = fopen(filename, "r");
    if (fp == NULL){
        fprintf(stderr, "No such file: getAlgIn\n");
        exit(-1);
    }

    fscanf(fp, "%d", &algIn->alg);
    fscanf(fp, "%d", &algIn->strategy);
    fscanf(fp, "%d", &algIn->select);
    fscanf(fp, "%d", &algIn->experiments);


    fclose(fp);
    return algIn;
}
