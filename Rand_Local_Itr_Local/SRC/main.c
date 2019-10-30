#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "ftnInput.h"
#include "searchAlgs.h"
#include "MT/mt19937ar.h"
#include "util.h"


/*! /brief chooseAlg() allows the user to enter an integer to run a Random Walk, Local Search, or Iterative
 *      Local Search Algorithm
 *
 * @param input is a pointer to a initialized input struct
 */

void chooseAlg(ftnInput *input){
    int alg=0;
    char buf[2], *endPtr;


    printf(" Enter '1' for Random Walk\n Enter '2' for Local Search\n Enter '3' for Iterative Local Search\n");

    do {
        printf("Please enter a valid selection:\n");
        fgets(buf, 2, stdin);
        alg = (int)strtol(buf, &endPtr, 10);
    }while( alg < 1 ||  alg > 3);

    switch(alg) {
        case 1:
            randWalk(input);
            break;
        case 2:
            localSearch(input, 1);
            break;
        case 3:
            itrLocSearch(input);
            break;
    }
}

/*! /brief main() initializes an input struct and launches the method to choose an algorithm to run.  Seed
 *      for Mersenne Twister is initialized.
 *
 * @return
 */
int main(){
    ftnInput *input = getInput("input.txt");
    init_genrand(time(0));
    chooseAlg(input);
    return 0;
}

