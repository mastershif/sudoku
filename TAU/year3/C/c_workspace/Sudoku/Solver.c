/*
 * Solver.c
 *
 *  Created on: 20 May 2018
 *      Author: Shif
 */
#include <string.h> // TODO: delete unused includes
#include <stdlib.h>
#include <stdbool.h>
#include "Solver.h"
#include <stdio.h>
#include <ctype.h>

int already_exists_in_row(int **grid, int row, int num) {
	for (int col = 0; col < 9; col++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}

int already_exists_in_col(int **grid, int col, int num) {
	for (int row = 0; row < 9; row++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}

int already_exists_in_box(int **grid, int startRow, int startCol, int num) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (grid[row + startRow][col + startCol] == num) {
				return 1;
			}
		}
	}
	return 0;
}

int is_num_allowed(int **grid, int row, int col, int num) {
	return !already_exists_in_row(grid, row, num)
			&& !already_exists_in_col(grid, col, num)
			&& !already_exists_in_box(grid, row - (row % 3), col - (col % 3), num);
}

int find_empty_cells(int **grid, int N, int *row, int *col) {
	for (*row = 0; *row < N; (*row)++) {
		for (*col = 0; *col < N; (*col)++) {
			if (grid[*row][*col] == 0) {
				return 1;
			}
		}
	}
	return 0;
}

int solveBoard(int **grid, int N) { // TODO: need to be exhaustive and count solutions
	// step 1: replace the recursion with a stack
	// the stack will contain grids
	// each grid represents a state of the game
	// step 2: make it exhaustive
	int row = 0;
	int col = 0;

	if (!find_empty_cells(grid, N, &row, &col)) {
		return 1; // if there are no empty cells, the board is solved
	}

	for (int num = 1; num <= N; num++) {

		if (is_num_allowed(grid, row, col, num)) {
			grid[row][col] = num;

			if (solveBoard(grid, N)) { // recursive call
				return 1;
			}
			// if the num is allowed but doesn't lead to a solution, empty the cell:
			grid[row][col] = EMPTY_CELL;
		}
	}

	return 0;
}

int generatePuzzle(int **grid, int N) {
	int row = 0;
	int col = 0;

	if (!find_empty_cells(grid, N, &row, &col)) {
		return 1;
	}

	// create an int[N] with randomly ordered ints 1 to N
	int* array = getRandomOrderArray(1, N, N);
	// then use this array for the iteration loop below:
	for (int index = 0; index < N; index++) {
		int num = array[index];

		if (is_num_allowed(grid, row, col, num)) {
			grid[row][col] = num;

			if (generatePuzzle(grid, N)) { // recursive call
				return 1;
			}
			// if the num is allowed but doesn't lead to a solution, empty the cell:
			grid[row][col] = EMPTY_CELL;
			}
	}

	// game->gameBoard = grid;
	return 0;
}

int * getRandomOrderArray(int min, int max, int N) {
	int* array = (int *)calloc(N, sizeof(int));
	if (!array) {
		printf("the array calloc failed :( \n");
		return NULL;
	}

   for (int i = 0; i < N; ++i) {
	  int digit = (rand() % (max + 1 - min)) + min;
	  bool alreadyExistsInArray = false;
	  for (int j = 0; j < N; ++j) {
		  if (array[j] == digit) {
			  alreadyExistsInArray = true;
		  }
	  }
	  if (!alreadyExistsInArray) {
		  array[i] = rand();
	  } else {
		  i--;
	  }
   }

   return array;
}

