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

#ifndef STRAUCH_PROJECT3_FTNS_H
#define STRAUCH_PROJECT3_FTNS_H

//Runs an equation from the function list using switch statements
double runftns(double ftn, int dim, double *vect);

//F1 Schwefel's
double schwefels(int dim, double *vect);

//F2 1st De Jong's function
double dejong(int dim, double *vect);

//Fn3 Rosenbrock
double rosenbrock(int dim, double *vect);

//Fn4 Rastrigin
double rastrigin(int dim, double *vect);

//Fn5 Griewangk
double griewangk(int dim, double *vect);

//Fn6 Sine Envelope Sine Wave
double sinenv(int dim, double *vect);

//Fn7 Stretched V Sine Wave
double stretchv(int dim, double *vect);

//Fn8 Ackley's One
double ackley1(int dim, double *vect);

//Fn9 Ackley's Two
double ackley2(int dim, double *vect);

//Fn10 Egg Holder
double eggholder(int dim, double *vect);

//Fn11 Rana
double rana(int dim, double *vect);

//Fn12 Pathological
double path(int dim, double *vect);

//Fn13 Michalewicz
double michalewicz(int dim, double *vect);

//Fn14 Masters Cosine Wave
double mastercos(int dim, double *vect);

//Fn15 Quartic
double quartic(int dim, double *vect);

//Fn16 Levy
double levy(int dim, double *vect);

//Fn17 Step
double step(int dim, double *vect);

//Fn18 Alpine
double alpine(int dim, double *vect);


#endif //STRAUCH_PROJECT3_FTNS_H