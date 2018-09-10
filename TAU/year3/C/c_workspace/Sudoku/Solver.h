/*
 * Solver.h
 *
 *  Created on: 12 May 2018
 *      Author: Shif
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#define EMPTY_CELL 0

/**
 * Checks if a given number already exists in a given row.
 *
 * @grid - the grid to check.
 * @row - the row to check.
 * @num - the number to check.
 * @return
 * 1 if the given number already exists in the given row, return 0 otherwise.
 */
int already_exists_in_row(int **grid, int row, int num);

/**
 * Checks if a given number already exists in a given col.
 *
 * @grid - the grid to check.
 * @col - the col to check.
 * @num - the number to check.
 * @return
 * 1 if the given number already exists in the given col, return 0 otherwise.
 */
int already_exists_in_col(int **grid, int col, int num);

/**
 * Checks if a given number already exists in a given block (3X3).
 *
 * @grid - the grid to check.
 * @startRow - the row where the block starts.
 * @startCol - the col where the block starts.
 * @num - the number to check.
 * @return
 * 1 if the given number already exists in the given block, return 0 otherwise.
 */
int already_exists_in_box(int **grid, int startRow, int startCol, int num);

/**
 * Checks if a given number is allowed in a given cell, by
 * calling already_exists_in_row, already_exists_in_col and already_exists_in_block.
 *
 * @grid - the grid to check.
 * @row - the row where the number is supposed to be.
 * @col - the col where the number is supposed to be.
 * @num - the number to check.
 * @return
 * 1 if the given number is a valid option for the given cell, return 0 otherwise.
 */
int is_num_allowed(int **grid, int row, int col, int num);

/**
 * Solves a given game. Uses the Backtrack algorithm to solve the game.
 *
 * @game - the game to solve.
 * @return
 * 1 when the game is solved, 0 otherwise.
 */
int solveBoard(int **grid, int N);

/**
 * Generates a new game with a specified number of pre-populated cells
 * ("fixed" cells). Uses the Backtrack algorithm to randomly generate
 * a solved board.
 *
 * @game - the game to generate.
 * @return
 * a new game instant is returned. TODO: not sure about the new instance.
 */
int generatePuzzle(int **grid, int N);

int * getRandomOrderArray(int min, int max, int N);

#endif /* SOLVER_H_ */
