/*
 * 	PROJECT 4: Particle Swarm Optimization, Firefly Algorithm,
			and Harmony Search

Author: Holly Strauch
CS 471
Project 4
May 19, 2019

This program uses Particle Swarm Optimization (PSO), Firefly Algorithm (FA), and
Harmony Search (HS) to attempt to optimize the fitness values of 18 different
functions. The equations that the algorithms are run on take vectors as inputs
and the populations are scalable in dimension and size.
 */
#ifndef STRAUCH4_PSO_H
#define STRAUCH4_PSO_H

#include "../Input.h"
#include "PSOpopulation.h"

//Runs the PSO algorithm.  The population is initialized then for each iteration the function for moving
//     particles is called.  This function also prints output to a file.
void PSORun(Input * in);

//Calculates the new velocities for each dimension for a vector C3 is a dampening factor, while C1 and C2
//     effect whether the personal best or global best has a greater effect on the overall movement
void PSONewVelocity(Input *in, int index, PSOpopulation *pop);

//Updates the values in the vector by adding the new velocity per each dimension
void PSOUpdateParticle(Input *in, int index, PSOpopulation *pop);

//For each individual in the popultion, a new velocity is calculated, the particle is updated,
//     then the new fitness, personal best, and global best values are calculated.
void PSOparticles(PSOpopulation *pop, Input * in);

#endif //STRAUCH4_PSO_H
