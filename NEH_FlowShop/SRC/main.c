/*
 * 	PROJECT 5: NEH Algorithm on Flow Shop Functions

Author: Holly Strauch
CS 471
Project 5
May 31, 2019

This program runs the NEH algorithm on three functions: Flow Shop Scheduling (FSS),
Flow Shop with Blocking (FSB), and Flow Shop with No Wait (FSNW).  It is a
combinatorial algorithm which attempts to find the ordering n jobs being
processed in m machines that will results in the minimum amount of total time.
 */

#include <stdio.h>
#include <stdlib.h>
#include "Input.h"
#include "FSFtns.h"
#include "MT/mt19937ar.h"
#include <time.h>
#include "NEH/NEH.h"
#include "Util.h"
#include "Output.h"

/** \brief main.c Sets up the input and output files then runs either a computation on a permutation provided or
 *      runs the entire algorithm on all files with a specified function
 *
 * @return
 */
int main() {
    int i=0;
    for(i = 1; i <= 120; i++) {
        Input *in = initInput("input.txt", i);

        Output *out = initOutput(in);
        init_genrand(time(0));


        if (in->runPerm != 0) {
            puts("Reading Given Permutation");
            setPermToCounter(in->perm, in->jobs);
            setFinalSched(in, out, in->perm);
            printf("Cmax: %d\n", out->Cmax);
            break;
        } else {
            NEHrun(in, out);
        }
        freeInput(in);
    }
    return 0;
}
