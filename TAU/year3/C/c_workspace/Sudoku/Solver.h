/*
 * Solver.h
 *
 *  Created on: 12 May 2018
 *      Author: Shif
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "Game.h"

typedef struct empty_cell_location_t {
    int x;
    int y;
} EmptyCellLocation;

int numSolutions(Game* game, int N);

#endif /* SOLVER_H_ */
