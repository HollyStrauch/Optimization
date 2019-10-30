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

#ifndef STRAUCH_P5_INPUT_H
#define STRAUCH_P5_INPUT_H

/** \brief Input struct contains all the data read in from a file which will be used by the algorithm and functions,
 *      along with information obtained from this info such as the sum of processing times
 *
 */
typedef struct _Input{
    int runPerm;         /**< 0 or 1 value indicating if a permutation is being inputted to run through a function*/
    int ftn;             /**< A specified function, only used if runPerm != 0*/
    int *perm;           /**< A permutation read from a file, only used if runPerm != 0*/
    int fileNum;         /**< A number specifying a specific Taillard file, only used if runPerm != 0*/
    int jobs;            /**< The total number of jobs in the data file */
    int machines;         /**< The total number of machines in the data file */
    int **processTimeComplete; /**< A matrix of processing times read in by the file of dimensions machines X jobs*/
    int *pTimeSums;        /**< The sum of the processing from each job, calculated from processTimeComplete */
    int *order;            /**< An array indicating the ordering of the pTimeSums */
}Input;

//Allocates memory and initializes an Input struct by reading in data from a file with algorithm info and a
//      file with processing time information
Input * initInput(const char *fileAlg, int fileNum);

//Calculates the sum of processing times for each job to be used to sort the jobs
void setSums(Input *in);

//Fills the order array with values 0 to n-1
void initOrder(Input *in);

//Frees the memory allocated for an Input struct
void freeInput(Input * in);

#endif //STRAUCH_P5_INPUT_H
