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
#include "Schedule.h"
#include "Input.h"
#include "Util.h"
#include <stdlib.h>

/** \brief Allocates memory for the Schedule Struct
 *
 * @param machines Number of machines
 * @param jobs Number of jobs
 * @return Initialized Schedule strucct
 */
Schedule * initSched(int machines, int jobs){
    Schedule *sched = (Schedule *)calloc(1, sizeof(Schedule));

    sched->processTime = matrixGenInt(machines, jobs);
    sched->schedule = matrixGenInt(machines, jobs);
    sched->makespan = 0;
    sched->flowTime = 0;

    return sched;
}

/** \brief Creates a matrix which is a subset of the complete processing times read in from a file.  It is made by
 *      inserting job into a specified point in an existing permutation of jobs.
 *
 * @param numJobs The new job being inserted into the existing permutation
 * @param index The index at which to insert the new job
 * @param perm Int array representing the current permutation
 * @param in Input struct with algorithm data
 * @return
 */
Schedule *create_sched(int numJobs, int index, int *perm, Input *in){
    int i=0, j=0;
    Schedule *sched = initSched(in->machines, numJobs);

    for(j = numJobs - 1; j >= 0; j--){
        for(i = 0; i < in->machines; i++) {
            if(j > index){
                sched->processTime[i][j] = in->processTimeComplete[i][perm[j-1]];
            }else if(j == index){
                sched->processTime[i][j] = in->processTimeComplete[i][in->order[numJobs-1]];
            }else if(j < index){
                sched->processTime[i][j] = in->processTimeComplete[i][perm[j]];
            }
        }
    }


    return sched;
}

/** \brief Calculates flow time for FS No Wait by summing all the departure values for the final machine
 *
 * @param machines The number of machines
 * @param jobs Number of jobs
 * @param sched The Schedule struct with the departure times and where the flowTime is being set
 */
void setFlowTime(int machines, int jobs, Schedule *sched){
    int i = 0;

    for (i = 0; i < jobs; i++){
        sched->flowTime += sched->schedule[machines-1][i];
    }
}

/** \brief Frees the memory for a Schedule struct
 *
 * @param machines The number of machines in the schedule
 * @param sched The Schedule struct being freed
 */
void freeSchedule(int machines, Schedule *sched){
    freematrix(machines, sched->schedule);
    freematrix(machines, sched->processTime);
    free(sched);
}
