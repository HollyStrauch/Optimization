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

#include <stdlib.h>
#include <stdio.h>
#include "Output.h"
#include "Util.h"
#include "Schedule.h"
#include "NEH/NEH.h"

/** \brief Allocates data and initializes an Output struct to hold results from NEH algorithm
 *
 * @param in Input struct with function and algorithm data
 * @return initialized Output struct pointer
 */
Output *initOutput(Input *in){
    Output *out = (Output *)calloc(1, sizeof(Output));

    out->finalSched = initSched(in->machines, in->jobs);
    out->perm = vectgenInt(in->jobs);
    out->Cmax = 0;
    out->time = 0;
    out->ftnCalls = 0;

    return out;
}

/** \brief Prints the results stored in an Output struct to a file
 *
 * @param out Output struct with data to print out
 * @param in Input struct with function and algorithm data
 * @param filename Name of the file being printed to
 */
void printOutput(Output * out, Input * in, char const *filename){
    int i=0;
    FILE *op = fopen(filename, "a");

    fprintf(op, "%d,", in->fileNum);
    fprintf(op, "%d,", out->Cmax);
    fprintf(op, "%d,", out->ftnCalls);
    fprintf(op, "%lf,", out->time);

    for(i = 0; i < in->jobs; i++){
        fprintf(op, "%d,", out->perm[i]);
    }

    fprintf(op, "\n");
    fclose(op);
}

/** \brief Prints data from an Output struct in a format that can be converted into a Gantt Chart. The machine and job
 *      are listed, followed by the start and end time for that job on that machine.
 *
 * @param out The Output struct being read from
 * @param in Input struct with function and algorithm data
 * @param filename The name of the file being printed to
 * @param perm The ordering of the jobs being printed out
 */
void printGanttChartData(Output * out, Input *in, const char *filename, int *perm){
    int i=0, j = 0, count = 1;
    FILE *op = fopen(filename, "a");

    fprintf(op, "Item, Activity, Jobs, Start, End \n");

    for(j = 0; j < in->jobs; j++){
        for(i = 0; i < in->machines; i++){
            fprintf(op, "%d,", count);
            fprintf(op, "M%d,J%d,", i + 1, perm[j]);
            fprintf(op, "%d,%d\n", out->finalSched->schedule[i][j] - out->finalSched->processTime[i][j],
                    out->finalSched->schedule[i][j]);
            count += 1;
        }
    }

    fclose(op);
}

/** \brief Creates the final schedule of departure times after the NEH algorithm has determined the best ordering of
 *      jobs, and sets the final Cmax value based on the objective function.
 *
 * @param in Input struct with function and algorithm data
 * @param out The Output struct that the schedule is being created in.
 * @param perm The final permutation of jobs
 */
void setFinalSched(Input *in, Output *out, int *perm){
    int i = 0, j=0;

    for(j = 0; j < in->jobs; j++){
        for(i = 0; i < in->machines; i++){
            out->finalSched->processTime[i][j] = in->processTimeComplete[i][perm[j]];
        }
    }

    out->Cmax = findObjective(in->jobs, in->machines, in, out->finalSched, out);
}

/** \brief Frees the memory allocated for an Output struct
 *
 * @param out The Output struct being freed
 * @param in Input struct with function and algorithm data
 */
void freeOutput(Output *out, Input *in){
    freeSchedule(in->machines, out->finalSched);
    free(out->perm);
    free(out);
}