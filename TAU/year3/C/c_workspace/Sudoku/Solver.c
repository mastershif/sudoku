#include <string.h> // TODO: delete unused includes
#include <stdlib.h>
#include <stdbool.h>
#include "Solver.h"
#include <stdio.h>
#include <ctype.h>
#include "Game.h"

EmptyCellLocation* getEmptyCellsLocations(int** board, int N) {
	// first count how many empty cells there are
	int count_empty_cells = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == 0) {
				count_empty_cells++;
			}
		}
	}
	printf("The number of empty cells in the board inside method getEmptyCellsLocations: %d\n", count_empty_cells);
	EmptyCellLocation* result = (EmptyCellLocation *)calloc(count_empty_cells, sizeof(EmptyCellLocation));
    if (!result) {
        printf("the empty cell locations calloc failed :( \n");
        return NULL;
    }
	// now populate the list of empty cells with the locations of the empty cells
	int index = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == 0) {
				result[index].x = i;
				result[index].y = j;
				index++;
			}
		}
	}
	return result;
}

int* getPreFilledIntArray(int item_count, int initial_value) {
	int* result = (int *)calloc(item_count, sizeof(int));
    if (!result) {
        printf("the pre-filled int array calloc failed :( \n");
        return NULL;
    }
	for (int i = 0; i < item_count; i++) {
		result[i] = initial_value;
	}
	return result;
}

int numSolutions(Game* game, int N) {

	// TODO: debug

	// make a copy of the gameBoard,
	// because counting the number of solutions should not change the game state
	int** board_copy = copyBoard(game->gameBoard, game->rows, game->columns);

	// first make an array of empty cells locations
	EmptyCellLocation* empty_cells_locations = getEmptyCellsLocations(game->gameBoard, N);
	int empty_cells_count = sizeof(empty_cells_locations)/sizeof(empty_cells_locations[0]);
	printf("The number of empty cells in the board is: %d\n", empty_cells_count);

	// the stack is implemented as an int array
	// each index corresponds to the matching index in the empty_cells_locations array.
	// the value in each index represents the value of that cell in the board.
	// for example:
	// stack[2] corresponds to the third location in the empty_cells_locations array.
	// the value stored in stack[2] represents the value to be inserted into
	// the third location in the empty_cells_locations array.
	// the stack is initialized with ones because this is the first value to be checked.
	int* stack = getPreFilledIntArray(empty_cells_count, 1);
	int stack_top = 0;

	int num_solutions = 0;

	while (stack_top >= 0) {

		EmptyCellLocation current_loc = empty_cells_locations[stack_top];
		if (stack[stack_top] > N) {
			// if the value in the stack top is over N, we are done changing this cell
			// we restore its value to 1
			stack[stack_top] = 1;
			// and "pop" the next item in the stack
			stack_top -= 1;

		} else if (isValidMove2(board_copy, game->m, game->n, N, current_loc.x, current_loc.y, stack[stack_top])) {
			board_copy[current_loc.x][current_loc.y] = stack[stack_top];
			if (stack_top < empty_cells_count - 1) {
				// if we are not at the last empty cell, move on to next cell
				// basically "push" the next cell to the stack and move to next iteration
				stack_top += 1;
				continue;
			}
			// if we are at the last empty cell and we populated it, we reached a valid solution
			num_solutions++;
			// now on to checking the next possible solution
			stack[stack_top]++;

		} else {
			// the value is invalid, check next value
			stack[stack_top]++;
		}
	}

	return num_solutions;
}
