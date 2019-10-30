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

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Schedule.h"
#include "../Input.h"
#include "../Util.h"
#include "NEH.h"
#include "../FSFtns.h"
#include "../Output.h"
#include <time.h>

/** \brief Runs the NEH algorithm.  Sorts the jobs, then threads each round of permutations as jobs are added in.
 *
 * @param in Input struct with algorithm and ftn data
 * @param out The Output struct which holds final results
 */
void NEHrun(Input *in, Output *out){
	int L=0, i=0;
	int *perm = vectgenInt(in->jobs);

    clock_t start = clock();

    quickSortFS(0, in->jobs-1, in->pTimeSums, in->order, in->machines);
	perm[0] = in->order[0];

	for(L = 2; L <= in->jobs; L++){
		//create comparison vector
		int *compare = vectgenInt(L);
		
		//index represents where the new job will be inserted in the mini schedule
        #pragma omp parallel for
		for(i = 0; i < L; i++){
			Schedule *sched = create_sched(L, i, perm, in);
			compare[i] = findObjective(L, in->machines, in, sched, out);
			freeSchedule(in->machines, sched);
		}

        insertAt(perm, L, findMin(compare, L), in->order[L-1]);
        free(compare);
	}
    setFinalSched(in, out, perm);

    finalizePerm(perm, in->jobs);
    out->perm = perm;
    clock_t stop = clock();
    out->time = (out, 1000 * ((double) stop - (double) start) / CLOCKS_PER_SEC);

    printResults(in, out, perm);
    printf("File %d Cmax: %d\n", in->fileNum, out->Cmax);

	free(perm);
	freeOutput(out, in);
}

/** \brief Prints the results from NEH algorithm to file.  General results are printed for each run to a results file
 *      corresponding to the FS function being used, and every tenth file has data for the Gantt Chart printed out to
 *      a second file.
 *
 * @param in Input struct with algorithm and function data
 * @param out The Output struct where the results were stored
 * @param perm The final permutation of the jobs
 */
void printResults(Input * in, Output *out, int *perm){

    char resultOutputFile[0x50];
    snprintf(resultOutputFile, sizeof(resultOutputFile), "FS%dResultsfile.csv", in->ftn);
    printOutput(out, in, resultOutputFile);

    if(in->fileNum % 10 == 1) {
        puts("Creating Gantt Chart");
        char gcOutputFile[0x50];
        snprintf(gcOutputFile, sizeof(gcOutputFile), "gcFS%dfile%d.csv", in->ftn, in->fileNum);
        printGanttChartData(out, in, gcOutputFile, perm);
    }
}

/** \brief Runs a processing time matrix through the specified objective function and returs the Cmax.
 *
 * @param numJobs The number of jobs in the processing time matrix
 * @param machines The number of machines in the processing time matrix
 * @param in Input struct with algorithm and function data
 * @param sched The Schedule struct with the processing time matrix and where the results are stored
 * @param out Ouput function that stores final results
 * @return
 */
int findObjective(int numJobs, int machines, Input *in, Schedule *sched, Output * out){
    int objFtn=0;

    if(in->ftn == 1){
        FSscheduling(numJobs, machines, sched);
        objFtn = sched->makespan;
    }else if(in->ftn == 2){
        FSBlocking(numJobs, machines, sched);
        objFtn = sched->makespan;
    }else if(in->ftn == 3){
        FSNoWait(numJobs, machines, sched);
        objFtn = sched->flowTime;
    }

    out->ftnCalls += 1;
    return objFtn;
}

/** \brief Sets the permutation array to job values instead of index values
 *
 * @param perm The permutation array to be set
 * @param length The length of the permutation array
 */
void finalizePerm(int *perm, int length){
    int i =0;

    for(i = 0; i < length; i++){
        perm[i] += 1;
    }

}

/** \brief Sets a permutation array to an array of indicies to create the corresponding departure time matrix
 *
 * @param perm The permutation to be set
 * @param length The length of the permutation array
 */
void setPermToCounter(int *perm, int length){
    int i =0;

    for(i = 0; i < length; i++){
        perm[i] -= 1;
    }
}