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

#include "FSFtns.h"
#include "Input.h"
#include "Schedule.h"
#include "Util.h"

/** \brief Sets of the first column and row for FSS and calls the rest of the calculation, which allows for unlimited
 *      jobs to be queued in between machines
 *
 * @param jobs Number of jobs
 * @param machines Number of machines
 * @param sched Schedule struct with process time info and where the departure time schedule will be stored
 */
void FSscheduling(int jobs, int machines, Schedule * sched){
    FScolumnInit(machines, sched);
    FSSrowInit(jobs, sched);
    FSSctCalc(jobs, machines, sched);
}

/** \brief Calculates the completion time of each job in a machine for FSS
 *
 * @param jobs Number of jobs
 * @param machines Number of machines
 * @param sched Schedule struct with process time info and where the departure time schedule will be stored
 */
void FSSctCalc(int jobs, int machines, Schedule *sched){
    int i=0, j=0;

    for(j = 1; j < jobs; j++){
        for(i = 1; i < machines; i++){
            sched->schedule[i][j] = sched->processTime[i][j] + iMAX(sched->schedule[i-1][j], sched->schedule[i][j-1]);
        }
    }

    sched->makespan = sched->schedule[machines-1][jobs-1];
}

/** \brief Sets of the first column for FSB and calls the rest of the calculation which has no storage space between
 *      machines
 *
 * @param jobs Number of jobs
 * @param machines Number of machines
 * @param sched Schedule struct with process time info and where the departure time schedule will be stored
 */
void FSBlocking(int jobs, int machines, Schedule * sched){
    FScolumnInit(machines, sched);
    FSBctCalc(jobs, machines, sched);
}

/** \brief Calculates the departure time for FSB
 *
 * @param jobs Number of jobs
 * @param machines Number of machines
 * @param sched Schedule struct with process time info and where the departure time schedule will be stored
 */
void FSBctCalc(int jobs, int machines, Schedule * sched){
    int i=0, j=0;

    for(j = 1; j < jobs; j++){
        sched->schedule[0][j] = iMAX(sched->processTime[0][j] + sched->schedule[0][j-1], sched->schedule[1][j-1]);
        for(i = 1; i < machines - 1; i++){
            sched->schedule[i][j] = iMAX(sched->processTime[i][j] + sched->schedule[i-1][j], sched->schedule[i+1][j-1]);
        }
        sched->schedule[machines - 1][j] =sched->processTime[machines-1][j] + sched->schedule[machines - 2][j];
    }

    sched->makespan = sched->schedule[machines-1][jobs-1];
}

/** \brief Sets the first column of values then runs the remaining calculations for FSNW, which requires a job to be able
 *      to move immediately from one machine to the next.
 *
 * @param jobs Number of jobs
 * @param machines Number of machines
 * @param sched Schedule struct with process time info and where the departure time schedule will be stored
 */
void FSNoWait(int jobs, int machines, Schedule * sched){
    FScolumnInit(machines, sched);
    FSNWctCalc(jobs, machines, sched);
    setFlowTime(machines, jobs, sched);

}

/** \brief Calculates the departure time for FSNW
 *
 * @param jobs Number of jobs
 * @param machines Number of machines
 * @param sched Schedule struct with process time info and where the departure time schedule will be stored
 */
void FSNWctCalc(int jobs, int machines, Schedule * sched){
    int i=0, j=0;

    for(j = 1; j < jobs; j++){
        sched->schedule[0][j] = sched->schedule[0][j-1] + sched->processTime[0][j];
        for(i = 1; i < machines; i++){
            if(sched->schedule[i-1][j] < sched->schedule[i][j-1]) {
                FSNWbacktrack(sched, j, i, sched->schedule[i][j-1] - sched->schedule[i-1][j]);
            }

            sched->schedule[i][j] = sched->schedule[i-1][j] + sched->processTime[i][j];
        }
    }
}

/** \brief Backtrack function used by FSNB which will update the departure times of the specified job in all previous
 *      machines
 *
 * @param sched Schedule struct with process time info and where the departure time schedule will be stored
 * @param job The job where departure times are being updated
 * @param machine The machine from which all prior machines will be updated
 * @param dif The amount that will be added to all previous departure times
 */
void FSNWbacktrack(Schedule *sched, int job, int machine, int dif){
    int i=0;

    for(i = 0; i < machine; i++){
        sched->schedule[i][job] += dif;
    }
}

/** \brief Initializes the first row of departure time values for a FS function by adding previous processing times for
 *      each machine
 *
 * @param machines the number machines
 * @param sched Schedule struct with process time info and where the departure time schedule will be stored
 */
void FScolumnInit(int machines, Schedule * sched){
    int i = 0, j = 0, sum = 0;

    for(i = 0; i < machines; i++) {
        for (j = 0; j <= i; j++) {
            sum += sched->processTime[j][0];
        }
        sched->schedule[i][0] = sum;
        sum = 0;
    }
}

/** \brief Initializes the values for the first row for FS departure times by summing the previous departure times for
 *      each job from the first machine.
 *
 * @param jobs
 * @param sched Schedule struct with process time info and where the departure time schedule will be stored
 */
void FSSrowInit(int jobs, Schedule * sched){
    int i = 0, j = 0, sum = 0;

    for(i = 0; i < jobs; i++) {
        for (j = 0; j <= i; j++) {
            sum += sched->processTime[0][j];
        }
        sched->schedule[0][i] = sum;
        sum = 0;
    }
}

