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
#include <sys/time.h>
#include "gAlg.h"
#include "MT/mt19937ar.h"
#include "deAlg.h"
#include "algInput.h"



/*! /brief chooseAlg() allows the user to enter an integer to run a Random Walk, Local Search, or Iterative
 *      Local Search Algorithm
 *
 * @param input is a pointer to a initialized input struct
 */

void chooseAlg(){
    algInput *algIn = getAlgIn("algInput.txt");

    switch(algIn->alg) {
        case 1:
           selectGA(algIn);
           break;
        case 2:
            deAlg(algIn);
            break;
    }
}

/*! /brief main() initializes an input struct and launches the method to choose an algorithm to run.  Seed
 *      for Mersenne Twister is initialized.
 *
 * @return
 */
int main(){
    init_genrand(time(0));
    chooseAlg();

    return 0;
}


