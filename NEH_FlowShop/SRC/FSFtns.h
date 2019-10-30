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

#ifndef STRAUCH_P5_FSFTNS_H
#define STRAUCH_P5_FSFTNS_H

#include "Input.h"
#include "Schedule.h"

//Sets of the first column and row for FSS and calls the rest of the calculation, which allows for unlimited
//     jobs to be queued in between machines
void FSscheduling(int jobs, int machines, Schedule * sched);

//Sets of the first column for FSB and calls the rest of the calculation which has no storage space between
//     machines
void FSBlocking(int jobs, int machines, Schedule * sched);

//Sets the first column of values then runs the remaining calculations for FSNW, which requires a job to be able
//     to move immediately from one machine to the next.
void FSNoWait(int jobs, int machines, Schedule * sched);

//Calculates the departure time for FSNW
void FSNWctCalc(int jobs, int machines, Schedule * sched);

//Backtrack function used by FSNW which will update the departure times of the specified job in all previous
//     machines
void FSNWbacktrack(Schedule *sched, int job, int machine, int dif);

//Calculates the departure time for FSB
void FSBctCalc(int jobs, int machines, Schedule * sched);

//Initializes the first row of departure time values for a FS function by adding previous processing times for
//     each machine
void FScolumnInit(int machines, Schedule * sched);

//Initializes the values for the first row for FS departure times by summing the previous departure times for
//      each job from the first machine.
void FSSrowInit(int jobs, Schedule * sched);

//Calculates the completion time of each job in a machine for FSS
void FSSctCalc(int jobs, int machines, Schedule * sched);

#endif //STRAUCH_P5_FSFTNS_H
