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
#include <sys/time.h>
#include "Input.h"
#include "MT/mt19937ar.h"
#include "Util.h"
#include "FA/FA.h"
#include "HS/HS.h"
#include "PSO/PSO.h"



/*! /brief chooseAlg() allows the user to enter an integer to run a PSO, FA, or HS algorithm
 *
 * @param input is a pointer to a initialized input struct
 */

void chooseAlg(Input *input){
    int alg=0;
    char buf[2], *endPtr;


    printf(" Enter '1' for PSO\n Enter '2' for FA\n Enter '3' for HS\n");

    do {
        printf("Please enter a valid selection:\n");
        fgets(buf, 2, stdin);
        alg = (int)strtol(buf, &endPtr, 10);
    }while( alg < 1 ||  alg > 3);

    switch(alg) {
        case 1:
            PSORun(input);
            break;
        case 2:
            firefly(input);
            break;
        case 3:
            harmonySearch(input);
            break;
    }
}

int main() {
    Input *in = getInput("ftnInput");
    init_genrand(time(0));

    chooseAlg(in);
}