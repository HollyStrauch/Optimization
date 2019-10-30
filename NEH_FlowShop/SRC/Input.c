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
#include "Util.h"
#include "FSFtns.h"
#include "NEH/NEH.h"
#include "Schedule.h"

/** \brief Allocates memory and initializes an Input struct by reading in data from a file with algorithm info and a
 *      file with processing time information
 *
 * @param fileAlg the name of the file with algorithm input data
 * @param fileNum the number of the Taillard set data file
 * @return pointer to initialized Input struct
 */
Input * initInput(const char *fileAlg, int fileNum){
    char fileDataLoc[0x50];

    Input *in = (Input *)calloc(1, sizeof(Input));
    FILE *datap, *algp;
    int i=0, j=0;

    algp = fopen(fileAlg, "r");
    if (algp == NULL){
        fprintf(stderr, "No such file: initInput Algorithm\n");
        exit(-1);
    }

    fscanf(algp, "%d", &in->runPerm);
    fscanf(algp, "%d", &in->ftn);

    if(in->runPerm != 0){
        fscanf(algp, "%d", &in->fileNum);
    }else{
        in->fileNum = fileNum;
    }
    snprintf(fileDataLoc, sizeof(fileDataLoc), "..\\DataFiles\\%d.txt", in->fileNum);
    printf(fileDataLoc);
    datap = fopen(fileDataLoc, "r");
    if (datap == NULL){
        fprintf(stderr, "No such file: initInput Data\n");
        exit(-1);
    }

    fscanf(datap, "%d", &in->machines);
    fscanf(datap, "%d", &in->jobs);


    if(in->runPerm != 0){
        in->perm = vectgenInt(in->jobs);
        for(i = 0; i < in->jobs; i++){
            fscanf(algp, "%d", &in->perm[i]);
        }
    }

    fclose(algp);

    in->processTimeComplete = matrixGenInt(in->machines, in->jobs);
    for(i = 0; i < in->machines; i++){
        for(j = 0; j < in->jobs; j++){
             fscanf(datap, "%d", &in->processTimeComplete[i][j]);
        }
    }

    fclose(datap);

    in->pTimeSums = vectgenInt(in->jobs);
    setSums(in);

    in->order = vectgenInt(in->jobs);
    initOrder(in);

    return in;
}

/** \brief Calculates the sum of processing times for each job to be used to sort the jobs
 *
 * @param in The Input struct where the sums are being calculated
 */
void setSums(Input *in){
    int i=0, j=0;

    for(j = 0; j < in->jobs; j++){
        for(i = 0; i < in->machines; i++){
            in->pTimeSums[j] +=in->processTimeComplete[i][j];
        }
    }
}

/** \brief Fills the order array with values 0 to n-1
 *
 * @param in Input struct where the order array is being set
 */
void initOrder(Input *in){
    int i = 0;

    for(i = 0; i < in->jobs; i++){
        in->order[i] = i;
    }
}

/** \brief Frees the memory allocated for an Input struct
 *
 * @param in Input struct being freed
 */
void freeInput(Input * in){
    freematrix(in->machines, in->processTimeComplete);
    free(in->pTimeSums);
    free(in->order);
    free(in);
}