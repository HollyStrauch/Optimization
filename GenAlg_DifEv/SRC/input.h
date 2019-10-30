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

#ifndef STRAUCH_PROJECT3_INPUT_H
#define STRAUCH_PROJECT3_INPUT_H

//Struct to hold data for functions and algorithms
typedef struct _input {
    int generations;
    int popsize;
    double crRate;
    double mRate;
    double mRange;
    double mPrecision;
    double er;
    double F;
    double L;
    int dim;
    int numFtns;
    double *ftnBounds;
} input;

//Initializes an input struct from data read in from a file
input *getInput(const char *filename);

#endif //STRAUCH_PROJECT3_INPUT_H
