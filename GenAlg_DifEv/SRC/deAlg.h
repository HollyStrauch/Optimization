/*
PROJECT 3: Genetic Algorithm and Differential Evolution

Author: Holly Strauch
CS 471
Project 3
May 3, 2019

This program uses Genetic Algorithm and Differential Evolution to optimize
18 different functions. Genetic Algorithm is run with either tournament
select or roulette select, and Differential Evolution is run with one of
10 DE strategies
*/

#ifndef STRAUCH_PROJECT3_DEALG_H
#define STRAUCH_PROJECT3_DEALG_H
#include "pop.h"
#include "input.h"
#include "algInput.h"

//deAlg sets up the Differential Evolution Algorithm, calls a strategy, and prints results to
//   a csv file 'deResults.csv'
void deAlg(algInput *algIn);

//stSelect is a switch statement that chooses which of the 10 DE strategies to run
int stSelect(int select, input *in, int callCount, population *pop, population *temp, const int ftnI);

//Strategy 1 for Differential Evolution Algorithm DE/best/1/exp
int strategy1(input *in, population *pop, population *temp, const int ftnI, int callCount);

//Strategy 2 for Differential Evolution Algorithm DE/rand/1/exp
int strategy2(input *in, population *pop, population *temp, const int ftnI, int callCount);

//Strategy 3 for Differential Evolution Algorithm DE/rand-to-best/1/exp
int strategy3(input *in, population *pop, population *temp, const int ftnI, int callCount);

//Strategy 4 for Differential Evolution Algorithm DE/best/2/exp
int strategy4(input *in, population *pop, population *temp, const int ftnI, int callCount);

//Strategy 5 for Differential Evolution Algorithm DE/rand/2/exp
int strategy5(input *in, population *pop, population *temp, const int ftnI, int callCount);

//Strategy 6 for Differential Evolution Algorithm DE/best/1/bin
int strategy6(input *in, population *pop, population *temp, const int ftnI, int callCount);

//Strategy 7 for Differential Evolution Algorithm DE/rand/1/bin
int strategy7(input *in, population *pop, population *temp, const int ftnI, int callCount);

//Strategy 8 for Differential Evolution Algorithm DE/rand-to-best/1/bin
int strategy8(input *in, population *pop, population *temp, const int ftnI, int callCount);

//Strategy 9 for Differential Evolution Algorithm DE/best/2/bin
int strategy9(input *in, population *pop, population *temp, const int ftnI, int callCount);

//Strategy 10 for Differential Evolution Algorithm DE/rand/2/bin
int strategy10(input *in, population *pop, population *temp, const int ftnI, int callCount);

#endif //STRAUCH_PROJECT3_DEALG_H
