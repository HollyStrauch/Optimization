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

#ifndef STRAUCH_P5_OUTPUT_H
#define STRAUCH_P5_OUTPUT_H

#include "Input.h"
#include "Schedule.h"

/** \brief Output struct with fields to hold the final permutation, schedule, and permutation from a run of NEH, along
 *      with the Cmax, run time, and number of objective function calls
 */
typedef struct _Output{
    Schedule *finalSched;     /**< Pointer to a Schedule struct that will hold the final processing and departure times */
    int *perm;                /**< An array of the final ordering of jobs */
    int Cmax;                 /**< The makespan or flow time of the objective function, depending of the function */
    double time;              /**< The runtime of NEH on a function */
    int ftnCalls;             /**< The number of time the algorithm ran the objective function*/
}Output;

//Allocates data and initializes an Output struct to hold results from NEH algorithm
Output *initOutput(Input *in);

//Creates the final schedule of departure times after the NEH algorithm has determined the best ordering of
//      jobs, and sets the final Cmax value based on the objective function.
void setFinalSched(Input *in, Output *out, int *perm);

//Prints the results stored in an Output struct to a file
void printOutput(Output * out, Input * in, char const *filename);

//Prints data from an Output struct in a format that can be converted into a Gantt Chart. The machine and job
//      are listed, followed by the start and end time for that job on that machine.
void printGanttChartData(Output * out, Input *in, const char *filename, int *perm);

//Frees the memory allocated for an Output struct
void freeOutput(Output *out, Input *in);

#endif //STRAUCH_P5_OUTPUT_H
