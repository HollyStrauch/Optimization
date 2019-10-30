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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ftns.h"

/*! \brief Runs an equation from the function list using switch statements

	\param ftn the number indicating which function is being run
	\param dim the dimension of the vector to be run on the function
	\param *vect the array of the vector
	\return result the solution from the selected function
*/
double runftns(double ftnNum, int dim, double *vect){
    double result;

    switch((int) ftnNum){
        case 1:
            result = schwefels(dim, vect);
            break;
        case 2:
            result = dejong(dim, vect);
            break;
        case 3:
            result = rosenbrock(dim, vect);
            break;
        case 4:
            result = rastrigin(dim, vect);
            break;
        case 5:
            result = griewangk(dim, vect);
            break;
        case 6:
            result = sinenv(dim, vect);
            break;
        case 7:
            result = stretchv(dim, vect);
            break;
        case 8:
            result = ackley1(dim, vect);
            break;
        case 9:
            result = ackley2(dim, vect);
            break;
        case 10:
            result = eggholder(dim, vect);
            break;
        case 11:
            result = rana(dim, vect);
            break;
        case 12:
            result = path(dim, vect);
            break;
        case 13:
            result = michalewicz(dim, vect);
            break;
        case 14:
            result = mastercos(dim, vect);
            break;
        case 15:
            result = quartic(dim, vect);
            break;
        case 16:
            result = levy(dim, vect);
            break;
        case 17:
            result = step(dim, vect);
            break;
        case 18:
            result = alpine(dim, vect);
            break;

    }
    return result;
}

/*! \brief Fn1 Schwefel's function

	\param dim length of vectors
	\param *vect points to vector
	\return sum the result of the equation on the given vector
 */
double schwefels(int dim, double *vect)
{
    int i=0;
    double sum = 0.0;

    for(i = 0; i < dim; i++)
    {
        sum += -1.0 * vect[i] * sin(sqrt(fabs(vect[i])));
    }
    return 418.9829 * dim - sum;

}


/*! \brief Fn2 1st De Jong's function

	\param dim length of vectors
	\param *vect points to vector
	\return sum the result of the equation on the given vector
 */
double dejong(int dim, double *vect)
{
    int i=0;
    double sum = 0;

    for(i = 0;i < dim; i++)
    {
        sum += pow(vect[i], 2);
    }

    return sum;
}

/*! \brief Fn3 Rosenbrock

	\param dim length of vectors
	\param *vect points to vector
	\return sum the result of the equation on the given vector
 */
double rosenbrock(int dim, double *vect)
{
    int i=0;
    double sum = 0;
    for(i = 1 ; i < dim - 1; i++)
    {
        sum += 100 * pow((pow(vect[i], 2) - vect[i+1]), 2) + pow((1 - vect[i]),2);
    }

    return sum;

}

/*! \brief Fn4 Rastrigin

	\param dim length of vectors
	\param *vect points to vector
	\return sum the result of the equation on the given vector
 */
double rastrigin(int dim, double *vect)
{
    int i=0;
    double sum = 0;

    for(i = 0; i < dim; i++)
    {
        sum += (pow(vect[i], 2) - (10 * cos(2 * M_PI * vect[i])));
    }

    return 10 * dim * sum;

}

/*! \brief Fn5 Griewangk

 \param dim length of vectors
 \param *vect points to vector
 \return sum the result of the equation on the given vector
 */
double griewangk(int dim, double *vect)
{
    int i=0;
    double sum = 0;
    double prod = 1;

    for(i = 1; i <= dim; i++)
    {
        sum += pow(vect[i], 2) / 4000;
        prod *= cos(vect[i] / sqrt(i));
    }

    return 1 + sum - prod;

}

/*! \brief Fn6 Sine Envelope Sine Wave

	\param dim length of vectors
	\param *vect points to vector
	\return sum the result of the equation on the given vector
 */
double sinenv(int dim, double *vect)
{
    int i=0;
    double sum = 0;
    double vecsq;

    for(i = 0; i < dim - 1; i++)
    {
        vecsq = pow(vect[i], 2) + pow(vect[i+1], 2);
        sum = sum + .5 + sin(pow(vecsq - .5, 2)) /
            pow(1 + .001 * vecsq, 2);
    }

    return -1.0 * sum;

}

/*! \brief Fn7 Stretched V Sine Wave

	\param dim length of vectors
	\param *vect points to vector
	\return sum the result of the equation on the given vector
 */
double stretchv(int dim, double *vect)
{
    int i=0;
    double sum = 0;
    double vecsq;

    for(i = 0; i < dim - 1; i++)
    {
        vecsq = pow(vect[i], 2) + pow(vect[i+1], 2);
        sum += pow(vecsq, .25) * sin(pow(50 * pow(vecsq, .1), 2)) + 1;
    }

    return sum;

}

/*! \brief Fn8 Ackley's One

	\param dim length of vectors
	\param *vect points to vector
	\return sum the result of the equation on the given vector
 */
double ackley1(int dim, double *vect)
{
    int i=0;
    double sum = 0;
    double vecsq;

    for(i = 0; i < dim - 1; i++)
    {
        vecsq = pow(vect[i], 2) + pow(vect[i+1], 2);
        sum += pow(M_E, -.2) * sqrt(vecsq) +
            3 * (cos(2 * vect[i]) + sin(2 * vect[i+1]));
    }

    return sum;

}

/*! \brief Fn9 Ackley's Two

	\param dim length of vectors
	\param *vect points to vector
	\return sum the result of the equation on the given vector
*/
double ackley2(int dim, double *vect)
{
    int i=0;
    double sum = 0;

    for(i = 0; i < dim - 1; i++)
    {
        sum += 20 + M_E - 20 * pow(M_E, -.2 * sqrt((pow(vect[i], 2) + pow(vect[i+1], 2)) / 2))
            - pow(M_E, .5 * (cos(2 * M_PI * vect[i]) + cos(2 * M_PI * vect[i+ 1])));
    }

    return sum;
}

/*! \brief Fn10 Egg Holder

	\param dim length of vectors
	\param *vect points to vector
	\return sum the result of the equation on the given vector
 */
double eggholder(int dim, double *vect)
{
    int i=0;
    double sum = 0;

    for(i = 0 ;i < dim - 1; i++)
    {
        sum += -1.0 * vect[i] * sin(sqrt(fabs(vect[i] - vect[i+1] - 47)))
            - (vect[i+1] + 47) * sin(sqrt(fabs(vect[i+1] + 47 + vect[i] / 2)));

    }

    return sum;

}

/*! \brief Fn11 Rana

	\param dim length of vectors
	\param *vect points to vector
	\return sum the result of the equation on the given vector
 */
double rana(int dim, double *vect)
{
    int i=0;
    double sum = 0;
    double negply, posply;

    for(i = 0; i < dim - 1; i++)
    {
        negply = sqrt(fabs(vect[i+1] - vect[i] + 1));
        posply = sqrt(fabs(vect[i+1] + vect[i] + 1));
        sum += vect[i] * sin(negply) * cos(posply)
            +(vect[i+1] + 1) * cos(negply) * sin(posply);
    }

    return sum;

}

/*! \brief Fn12 Pathological

	\param dim length of vectors
	\param *vect points to vector
	\return sum the result of the equation on the given vector
 */
double path(int dim, double *vect)
{
    int i=0;
    double sum = 0;

    for(i = 0;i < dim - 1; i++)
    {
        sum += .5 + (sin(pow(sqrt(100 * pow(vect[i], 2) + pow(vect[i+1], 2)),2)) - .5)
            / (1 + .001 * pow(pow(vect[i], 2)- (2 * vect[i] * vect[i+1]) + pow(vect[i+1], 2), 2));

    }

    return sum;

}

/*! \brief Fn13 Michalewicz

	\param dim length of vectors
	\param *vect points to vector
	\return sum the result of the equation on the given vector
 */
double michalewicz(int dim, double *vect)
{
    int i=0;
    double sum = 0;

    for(i = 1; i <= dim; i++)
    {
        sum += sin(vect[i]) * pow(sin(i * pow(vect[i], 2) / M_PI), 20);
    }

    return -1.0 * sum;
}

/*! \brief Fn14 Masters Cosine Wave

	\param dim length of vector
	\param *vect points to vector
	\return sum the result of the equation on the given vector
 */
double mastercos(int dim, double *vect)
{
    int i=0;
    double subfn;
    double sum = 0;

    for(i = 0; i < dim - 1; i++)
    {
        subfn = pow(vect[i], 2) + pow(vect[i+1], 2) + .5 * (vect[i+1] * vect[i]);
        sum += pow(M_E, -.125 * subfn) * cos(4 * sqrt(subfn));
    }

    return -1.0 * sum;
}

/*! \brief Fn15 Quartic

	\param dim length of vector
	\param *vect points to vector
	\return sum the result of the equation on the given vector
 */
double quartic(int dim, double *vect)
{
    int i=0;
    double sum = 0;

    for(i = 1; i <= dim; i++)
    {
        sum += i * pow(vect[i], 4.0);
    }

    return sum;
}

/*! \brief Fn16 Levy

	\param dim length of vector
	\param *vect points to vector
	\return sum the result of the equation on the given vector
*/
double levy(int dim, double *vect)
{
    int i=0;
    double wi = 0.0;
    double wn = 1.0 + (vect[dim - 1] - 1.0) / 4.0;
    double sum = pow(sin(M_PI * (1 + (vect[0] - 1.0) / 4.0)), 2.0);

    for(i = 0; i < dim - 1; i++)
    {
        wi = 1 + (vect[i] - 1.0) / 4.0;
        sum += pow(wi - 1.0, 2.0) * (1.0 + 10.0 *  pow(sin(M_PI * wi + 1.0), 2.0))
            + pow(wn - 1.0, 2.0) * (1.0 + pow(sin(2.0 * M_PI * wn), 2.0));
    }

    return sum;
}


/*! \brief Fn17 Step

	\param dim length of vector
	\param *vect points to vector
	\return sum the result of the equation on the given vector
 */
double step(int dim, double *vect)
{
    int i=0;
    double sum = 0;

    for(i = 0; i < dim; i++)
    {
        sum += pow(fabs(vect[i]) + .5, 2);
    }

    return sum;
}


/*! \brief Fn18 Alpine

	\param dim length of vector
	\param *vect points to vector
	\return sum the result of the equation on the given vector
 */
double alpine(int dim, double *vect)
{
    int i=0;
    double sum = 0;

    for(i = 0; i < dim - 1; i++)
    {
        sum = sum + fabs(vect[i] * sin(vect[i]) + .1 * vect[i]);
    }

    return sum;
}



