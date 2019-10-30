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

#ifndef STRAUCH_P5_NEH_H
#define STRAUCH_P5_NEH_H


#include "../Schedule.h"
#include "../Input.h"
#include "../Output.h"

//Runs the NEH algorithm.  Sorts the jobs, then threads each round of permutations as jobs are added in.
void NEHrun(Input * in, Output *out);

//Runs a processing time matrix through the specified objective function and returs the Cmax.
int findObjective(int numJobs, int machines, Input *in, Schedule *sched, Output * out);

//Prints the results from NEH algorithm to file.  General results are printed for each run to a results file
//    corresponding to the FS function being used, and every tenth file has data for the Gantt Chart printed out to
//     a second file.
void printResults(Input * in, Output *out, int *perm);

//Sets the permutation array to job values instead of index values
void finalizePerm(int *perm, int length);

//Sets a permutation array to an array of indicies to create the corresponding departure time matrix
void setPermToCounter(int *perm, int length);

#endif //STRAUCH_P5_NEH_H


