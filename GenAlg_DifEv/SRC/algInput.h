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

#ifndef STRAUCH_PROJECT3ROUGHDONE_ALGINTPUT_H
#define STRAUCH_PROJECT3ROUGHDONE_ALGINTPUT_H

//Struct to hold information on which algorithms to run
typedef struct _algInput{
    int alg;
    int strategy;
    int select;
    int experiments;
} algInput;

//Initializes the data in a algInput struct from a file, used for choosing algorithms
algInput *getAlgIn(const char *filename);
#endif //STRAUCH_PROJECT3ROUGHDONE_ALGINTPUT_H
