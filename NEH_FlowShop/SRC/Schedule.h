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

#ifndef STRAUCH_P5_SCHEDULE_H
#define STRAUCH_P5_SCHEDULE_H

#include "Input.h"

/** \brief Schedule struct that will hold process times, a completed schedule, makespan, and flowtime for Flow Schedule
 *      Problems
 */
typedef struct _Schedule{
    int **processTime;     /**< Matrix holding the process times*/
    int **schedule;        /**< Matrix holding the final departure times*/
    int makespan;          /**< Will hold the makespan after the schedule is processed*/
    int flowTime;          /**< Will hold the flowtime for FSNW after the schedule is processed*/

}Schedule;

//Allocates memory for the Schedule Struct
Schedule * initSched(int machines, int jobs);

//Creates a matrix which is a subset of the complete processing times read in from a file.  It is made by
//    inserting job into a specified point in an existing permutation of jobs.
Schedule *create_sched(int L, int index, int *perm, Input *in);

//Calculates flow time for FS No Wait by summing all the departure values for the final machine
void setFlowTime(int machines, int jobs, Schedule *sched);

//Frees the memory for a Schedule struct
void freeSchedule(int machines, Schedule *sched);

#endif //STRAUCH_P5_SCHEDULE_H
