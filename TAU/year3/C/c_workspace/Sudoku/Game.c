/*
 * Game.c
 *
 *  Created on: 12 May 2018
 *      Author: Shif
 */
#include <string.h> // TODO: delete unused includes
#include <stdlib.h>
#include <stdbool.h>
#include "Game.h"
#include "Solver.h"
#include "ILPSolver.h"
#include <stdio.h>
#include <ctype.h>

Game* createGame(int fixedAmount) {
	Game* game=(Game *)calloc(1, sizeof(Game));
	if (!game) {
		printf("the game calloc failed :( \n");
		return NULL;
	}

	game->fixedCount = fixedAmount;
    game->moves = NULL;
    game->current_move = NULL;
	// generatePuzzle(game->gameSolution);
//	int row;
//	int col;
//	int count = 0;
//	while (count<fixedAmount) {
//		row = rand() % N;
//		col= rand() % N;
//		if (game->fixedCells[row][col] == 0){
//			game->fixedCells[row][col] = 1;
//			count++;
//		}
//	}
//	row = 0;
//	col = 0;
//	for (; row < N; row++) {
//		for (;col < N; col++) {
//			if (game->fixedCells[row][col] == 1) {
//				game->gameBoard[row][col] = game->gameSolution[row][col];
//			}
//		}
//	}
	return game;

	// Create an empty board

	// Use randomized backtracking to get a random solved board

	// store the solution inside int gameSolution[N][N]

	// Repeat fixedAmount times:
	//  Randomly select an empty cell <X, Y>. If cell <X,Y> is "fixed" (was already selected),
	//  repeat randomizing X,Y until cell <X,Y> is not fixed.
	//  Mark the chosen cell as a "fixed" cell.

	// Clear all cells that are not fixed (NxN – fixedAmount cells that were not selected).

}

Game* createEmptyGame() {
	Game *game = (Game *) calloc(1, sizeof(Game));
	if (!game) {
		printf("the game calloc failed :( \n");
		return NULL;
	}

	game->fixedCount = 0;
	game->m = 3; // number of rows in each box
	game->n = 3; // number of columns in each box
	game->rows = 9;
	game->columns = 9;
	game->size = 81;

	game->gameBoard = (int **)calloc(game->n*game->m, sizeof(int *));
	if (!game->gameBoard) {
		printf("the gameBoard calloc failed :( \n");
		return NULL;
	}
	for (int row = 0; row < game->n*game->m; row++) {
		game->gameBoard[row] = (int *)calloc(game->n*game->m, sizeof(int));
		if (!game->gameBoard[row]) {
			printf("the gameBoard row calloc failed :( \n");
			return NULL;
		}
	}

	// allocate memory for the fixed cells 2D array
	game->fixedCells = (int **)calloc(game->n*game->m, sizeof(int *));
	if (!game->fixedCells) {
		printf("the fixedCells calloc failed :( \n");
		return NULL;
	}
	for (int row = 0; row < game->n*game->m; row++) {
		game->fixedCells[row] = (int *)calloc(game->n*game->m, sizeof(int));
		if (!game->fixedCells[row]) {
			printf("the fixedCells row calloc failed :( \n");
			return NULL;
		}
	}

	// allocate memory for the error cells 2D array
	game->errorCells = (int **)calloc(game->n*game->m, sizeof(int *));
	if (!game->errorCells) {
		printf("the errorCells calloc failed :( \n");
		return NULL;
	}
	for (int row = 0; row < game->n*game->m; row++) {
		game->errorCells[row] = (int *)calloc(game->n*game->m, sizeof(int));
		if (!game->errorCells[row]) {
			printf("the errorCells row calloc failed :( \n");
			return NULL;
		}
	}

	// allocate memory for the game solution
	game->gameSolution = (int **)calloc(game->n*game->m, sizeof(int *));
	if (!game->gameSolution) {
		printf("the gameSolution calloc failed :( \n");
		return NULL;
	}
	for (int row = 0; row < game->n*game->m; row++) {
		game->gameSolution[row] = (int *)calloc(game->n*game->m, sizeof(int));
		if (!game->gameSolution[row]) {
			printf("the gameSolution row calloc failed :( \n");
			return NULL;
		}
	}

	game->moves = NULL;
	game->current_move = NULL;

	return game;
}

bool isValidMove(Game* game, int row, int col, int value) {
	bool legalMove = true;
	if (value == 0) {
	    return legalMove;
	}
	int blockStartRow;
	int blockStartColumn;

	// already exists in row?
	for (int i = 0; i < game->columns; i++) {
		if (col == i) {
			continue;
		}
		if (value == game->gameBoard[row][i]) {
			legalMove = false;
		}
	}

    // already exists in column?
	for (int j = 0; j < game->rows; j++) {
	    if (row == j) {
	        continue;
	    }
	    if (value == game->gameBoard[j][col]) {
	        legalMove = false;
	    }
	}

	// already exists in block?
	int i = blockStartRow = row - (row%game->m); // block rows
	int j = blockStartColumn = col - (col%game->n); // block columns
	for (; i < blockStartRow + game->m; i++) {
		for (; j < blockStartColumn + game->n; j++) {
			if (i == row && j == col) {
				continue;
			}
			if (game->gameBoard[i][j] == value) {
				legalMove = false;
			}
		}
	}

	if (!legalMove) {
		printf("%s", "Error: value is invalid\n");
	}
	return legalMove;
}

void setValue(Game* game, int row, int col, int value) {

	// check if the move is valid
	bool validMove = isValidMove(game, row - 1, col - 1, value);

	// set the value anyway
    game->gameBoard[row - 1][col - 1] = value;

    // mark the cell as erroneous if invalid move
	if (!validMove) {
		game->errorCells[row - 1][col - 1] = 1;
	} else {
        // if the cell was previously erroneous but now it isn't, mark accordingly
        game->errorCells[row - 1][col - 1] = 0;
	}

	if (isBoardFull(game) && isNoError(game)) {
		printf("Puzzle solved successfully\n");
	}
}

void printSeparatorRow(int m, int rows) {
	int dash_count = 4*rows + m + 1;
	for (int i = 0; i < dash_count; i++) {
		printf("-");
	}
	printf("\n");
}

void printBoard(Game* game, bool mark_errors) {
	printSeparatorRow(game->m, game->rows);

	for (int row = 0; row < game->rows; row++) {
		printf("|");
		for (int col = 0; col < game->columns; col++) {
			if (game->gameBoard[row][col] == 0) {
				printf("    ");
			} else {
				printf(" %2d", game->gameBoard[row][col]);

				// print dot after the number if it's a fixed cell
				if (game->fixedCells[row][col] == 1) {
					printf(".");
				}
				// print a star after the number if it's an error
				else if (mark_errors && game->errorCells[row][col] == 1) {
					printf("*");
				}
				else {
					printf(" ");
				}
			}
			if ((col + 1) % game->n == 0 && col != (game->columns - 1)) {
				printf("|");
			}
		}
		printf("|\n");

		if ((row + 1) % game->m == 0) {
			printSeparatorRow(game->n, game->rows);
		}

	}
}

bool isBoardFull(Game* game) {
	bool isFull = true;
	for (int row = 0; row < game->rows; row++) {
		for (int col = 0; col < game->columns; col++) {
			if (game->gameBoard[row][col] == 0) {
				isFull = false;
				return isFull;
			}
		}
	}
	return isFull;
}

bool isBoardEmpty(Game* game) {
    bool isEmpty = true;
    for (int row = 0; row < game->rows; row++) {
        for (int col = 0; col < game->columns; col++) {
            if (game->gameBoard[row][col] != 0) {
                isEmpty = false;
                return isEmpty;
            }
        }
    }
    return isEmpty;
}

int** copyBoard(int **gameBoard, int rows, int columns) {
	int** board_copy = (int **)calloc(rows*columns, sizeof(int *));
	if (board_copy == NULL) {
		printf("the board_copy calloc failed :(\n");
		return NULL;
	}
	for (int row = 0; row < rows; row++) {
		board_copy[row] = (int *)calloc(rows*columns, sizeof(int));
		if (!board_copy[row]) {
			printf("the board_copy row calloc failed :(\n");
			return NULL;
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			board_copy[i][j] = gameBoard[i][j];
		}
	}
	return board_copy;
}

void autofill(Game* game) {
	int** board_copy = copyBoard(game->gameBoard, game->rows, game->columns);
	// iterate over the cells
	for (int i = 0; i < game->rows; i++) {
		for (int j = 0; j < game->columns; j++) {
			if (board_copy[i][j] == 0) {
				printf("cell %d,%d is empty\n", i + 1, j + 1);
				// if empty, check for possible values

				// go over the row and make a list of the values that are not in the row already
				int* possible_row_values = (int *)calloc(game->columns, sizeof(int));
				if (possible_row_values == NULL) {
					printf("the possible_row_values calloc failed :(\n");
					return;
				}
				// initiate all possible values row to 1
				for (int a = 0; a < game->columns; a++) {
					possible_row_values[a] = 1;
				}
				for (int c = 0; c < game->columns; c++) {
					if (board_copy[i][c] != 0) {
						// printf("impossible value in cell %d,%d with regard to row %d is %d\n", i, j, i, board_copy[i][c]);
						possible_row_values[board_copy[i][c] - 1] = 0;

					}
				}
				printf("These are the possible values in row %d\n", i);
				for (int possible_row_value = 0; possible_row_value < game->columns; possible_row_value++) {
					printf("%d ", possible_row_values[possible_row_value]);
				}
				printf("\n");

				// go over the column and make a list of the values that are not in the column already
				int* possible_col_values = (int *)calloc(game->rows, sizeof(int));
				if (possible_col_values == NULL) {
					printf("the possible_col_values calloc failed :(\n");
					return;
				}
				// initiate all possible values col to 1
				for (int a = 0; a < game->rows; a++) {
					possible_col_values[a] = 1;
				}
				for (int r = 0; r < game->rows; r++) {
					if (board_copy[r][j] != 0) {
						possible_col_values[board_copy[r][j] - 1] = 0;
					}
				}
				printf("These are the possible values in column %d\n", j);
				for (int possible_col_value = 0; possible_col_value < game->rows; possible_col_value++) {
					printf("%d ", possible_col_values[possible_col_value]);
				}
				printf("\n");

				// go over the box and make a list of the values that are not in the box already
				int* possible_box_values = (int *)calloc(game->m*game->n, sizeof(int));
				if (possible_box_values == NULL) {
					printf("the possible_box_values calloc failed :(\n");
					return;
				}
				// initiate all possible values box to 1
				for (int a = 0; a < game->m*game->n; a++) {
					possible_box_values[a] = 1;
				}
				int boxStartRow;
				int boxStartColumn;
				int br = boxStartRow = i - (i % game->m); // box rows
				int bc = boxStartColumn = j - (j % game->n); // box columns
				for (; br < boxStartRow + game->m; br++) {
					for (; bc < boxStartColumn + game->n; bc++) {
						if (board_copy[br][bc] != 0) {
							possible_box_values[board_copy[br][bc] - 1] = 0;
						}
					}
				}
				printf("These are the possible values in the box\n");
				for (int possible_box_value = 0; possible_box_value < game->rows; possible_box_value++) {
					printf("%d ", possible_box_values[possible_box_value]);
				}
				printf("\n");

				// now we have 3 int arrays, with values 0,1
				// 1 means the index is a possible value
				// go over the 3 arrays and find out if there is only one possible value
				// for now, assume all arrays are the same length
				int count_of_possible_values = 0;
				int possible_value = 0;
				for (int v = 0; v < game->rows; v++) {
					if (possible_row_values[v] == 1 && possible_col_values[v] == 1 && possible_box_values[v] == 1) {
						count_of_possible_values++;
						possible_value = v + 1;
						if (count_of_possible_values > 1) {
							break;
						}
					}
				}
				// if all 3 lists have only one number in commmon, this is the solution
				// if only 1 possible value, fill that value in game->gameBoard
				if (count_of_possible_values == 1) {
					game->gameBoard[i][j] = possible_value;
					printf("Cell <%d,%d> set to %d\n",i + 1, j + 1, possible_value);
				}

				// free memory of the possible row, col and box values
				free(possible_row_values);
				free(possible_col_values);
				free(possible_box_values);
			}
		}
	}
	// free memory for board_copy
	for (int i = 0; i < game->rows; i++) {
		free(board_copy[i]);
	}
	free(board_copy);
}

// return 1 on success, 0 on failure
int randomlyFillXCellsAndSolve(Game* game, int x) {
    int i, success;
    for (i = 0; i < MAX_NUMBER_OF_ATTEMPTS; i++) {
        success = fillXCellsRandomly(game, x); /* Works on game->userBoard */
        if (!success) {
            cleanUserBoardAndSolution(game); /* Cleans game->userBoard and game->solution values to zeros */
            continue; /* Attempt failed - continue to next iteration */
        }
        markFullCellsAsFixed(game->userBoard, game->N); /* Mark all x chosen cells as fixed before passing to ILP solver */
        /* At this point fillXCellsRandomly should have filled X cells and marked them as FIXED */
        success = solveWithILP(game, game->m, game->n, game->gameSolution);   /* On success: game->solution holds the solution */
        if (!success) {
            cleanUserBoardAndSolution(game); /* Cleans game->userBoard and game->solution */
            continue; /* Attempt failed - continue to next iteration */
        }
        /* Getting here means solution holds a valid complete board */
        break;
    }
    return ((success == TRUE) ? TRUE : FALSE);
}

int fillXCellsRandomly(Game *game, int X) {
    int **matrixOfChoices; /* To track already-chosen cells */
    int counter, randomRow, randomCol, randomVal, N;

    N = game->m*game->n;
    matrixOfChoices = allocateIntMatrix(N);
    setToEmpty(matrixOfChoices, N);

    counter = 0;
    while (counter < x) {
        randomRow = rand() % N;
        randomCol = rand() % N;

        while (matrixOfChoices[randomRow][randomCol] == FULL) {
            randomRow = rand() % N;
            randomCol = rand() % N;
        }
        randomVal = getRandomLegalValue(game, randomRow, randomCol);
        if (randomVal == INVALID) {
            freeIntMatrix(matrixOfChoices, N);
            return FALSE;
        }
        game->userBoard[randomRow][randomCol]->value = randomVal;
        counter++;
    }
    freeIntMatrix(matrixOfChoices, N);
    return TRUE;
}

int generate(Game* game, int X, int Y) {

    // step 2: run ILP and solve the board. If the board is not solvable,
    // start again, up to 1000 times.

    int succeeded;

    // first make sure the board is empty
    if (!isBoardEmpty(game)) {
        printf("Error: board is not empty\n");
        return 1;
    }

    // step 1: randomly choose X cells and fill them with random values
    // if at any point there is a cell that doesn't have a legal value,
    // start again, up to 1000 times.
    for (int i = 0; i < 1000; i++) {

    }


    succeeded = randomlyFillXCellsAndSolve(game, X);

    if (!succeeded) {
        printf("Error: puzzle generator failed\n");
        return 1;
    }

    // step 3: clear all cells except for Y cells
    randomlyClearYCells(game, Y);
    markFullCellsAsFixed(game->userBoard, game->N); /* Mark as FIXED all remaining cells */

    return 0;
}

int numSolutions(Game *game) {
	int result = 0;
	int** board_copy = copyBoard(game->gameBoard, game->rows, game->columns);
	result = solveBoard(board_copy, game->m*game->n);
	return result;
}

bool isNoError(Game* game) {
	bool isNoError = true;
	for (int row = 0; row < game->rows; row++) {
		for (int col = 0; col < game->columns; col++) {
			if (game->errorCells[row][col] == 1) {
				isNoError = false;
				return isNoError;
			}
		}
	}
	return isNoError;
}

void destroyGame(Game* game) {
	// free game board
	for (int i = 0; i < game->n*game->m; i++) {
	  free(game->gameBoard[i]);
	}
	free(game->gameBoard);

	// free fixed cells
	for (int i = 0; i < game->n*game->m; i++) {
		free(game->fixedCells[i]);
	}
	free(game->fixedCells);

	// free error cells
	for (int i = 0; i < game->n*game->m; i++) {
		free(game->errorCells[i]);
	}
	free(game->errorCells);

	// free game solution
	for (int i = 0; i < game->n*game->m; i++) {
		free(game->gameSolution[i]);
	}
	free(game->gameSolution);

	if (game->moves != NULL) {
	    free(game->moves);
	}
//    if (game->current_move != NULL) {
//        free(game->current_move);
//    }
	// free game itself
	free(game);
}
