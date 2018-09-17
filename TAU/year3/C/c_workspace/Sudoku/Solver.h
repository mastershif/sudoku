#ifndef SOLVER_H_
#define SOLVER_H_

#include "Game.h"

/**
 * This module implements the exhaustive backtracking algorithm with a stack
 * to calculate the number of possible solutions for a given sudoku game.
 */

typedef struct empty_cell_location_t {
    int x;
    int y;
} EmptyCellLocation;

/**
 * Calculates the number of possible solutions for a given sudoku game,
 * using the exhaustive backtracking algorithm with a stack (without recursion).
 *
 * @param game - the game to be solved.
 * @param N - the number of rows in the game board.
 * @return
 * The number of solutions for the game.
 * If there are no solutions, returns 0.
 */
int numSolutions(Game* game, int N);

#endif /* SOLVER_H_ */
