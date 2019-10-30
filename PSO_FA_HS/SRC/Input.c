/*
 * 	PROJECT 4: Particle Swarm Optimization, Firefly Algorithm,
			and Harmony Search

Author: Holly Strauch
CS 471
Project 4
May 19, 2019

This program uses Particle Swarm Optimization (PSO), Firefly Algorithm (FA), and
Harmony Search (HS) to attempt to optimize the fitness values of 18 different
functions. The equations that the algorithms are run on take vectors as inputs
and the populations are scalable in dimension and size.
 */

#include <stdio.h>
#include <stdlib.h>
#include "Input.h"

/** /brief Initializes an input struct from data read in from a file
 *
 * @param filename
 * @return pointer to initialized struct
 */
Input *getInput(char *filename){
    Input *in = (Input *)calloc(1, sizeof(Input));
    FILE *fp;
    int i;

    fp = fopen(filename, "r");
    if (fp == NULL){
        fprintf(stderr, "No such file: getInput\n");
        exit(1);
    }
    fscanf(fp, "%d", &in->experiments);
    fscanf(fp, "%d", &in->popsize);
    fscanf(fp, "%d", &in->itrs);
    fscanf(fp, "%d", &in->dim);
    fscanf(fp, "%lf", &in->C1);
    fscanf(fp, "%lf", &in->C2);
    fscanf(fp, "%lf", &in->C3);

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
