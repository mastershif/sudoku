#include <string.h> // TODO: delete unused includes
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include "Game.h"
#include "ILPSolver.h"

Game* createGame(int fixedAmount) {
	Game* game=(Game *)calloc(1, sizeof(Game));
	if (!game) {
		printf("the game calloc failed :( \n");
		return NULL;
	}

	game->fixedCount = fixedAmount;
	game->moves_count = 0;
    game->moves_anchor = NULL;
    game->moves_head = NULL; // moves_head is the current_move
	return game;
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

	// save a copy of the gameBoard's original state
    game->originalBoard = copyBoard(game->gameBoard, game->rows, game->columns);

    game->moves_count = 0;
    game->moves_anchor = NULL;
    game->moves_head = NULL;

	return game;
}

bool isValidMove(int **board, int m, int n, int N, int row, int col, int value) {
    bool legalMove = true;
    if (value == 0) {
        return legalMove;
    }
    int blockStartRow = row - (row % m);
    int blockStartColumn = col - (col%n);

    // already exists in row?
    for (int i = 0; i < N; i++) {
        if (col == i) {
            continue;
        }
        if (value == board[row][i]) {
            legalMove = false;
            return legalMove;
        }
    }

    // already exists in column?
    for (int j = 0; j < N; j++) {
        if (row == j) {
            continue;
        }
        if (value == board[j][col]) {
            legalMove = false;
            return legalMove;
        }
    }

    // already exists in block?
    for (int i = blockStartRow; i < blockStartRow + m; i++) {
        for (int j = blockStartColumn; j < blockStartColumn + n; j++) {
            if (i == row && j == col) {
                continue;
            }
            if (board[i][j] == value) {
                legalMove = false;
                return legalMove;
            }
        }
    }

    return legalMove;
}

void setValue(Game* game, int row, int col, int value) {

	// check if the move is valid
	bool validMove = isValidMove(game->gameBoard, game->m, game->n, game->m * game->n, row - 1, col - 1, value);

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

Node* insertNewMove(Game *game) {
    // printf("was ordered to insert move node with x = %d, y = %d, value = %d\n", X, Y, value);
    Node* newNode = createNewNode(game->gameBoard, game->rows, game->columns);
    // printf("newNode was created with x = %d, y = %d, value = %d\n", newNode->X, newNode->Y, newNode->value);

    // if there are more than zero moves but all of them were undone
    if (game->moves_head == NULL && game->moves_anchor != NULL) {
        freeLinkedList(game->moves_anchor, game->m*game->n);
        game->moves_count = 0;
        game->moves_anchor = NULL;
    }

    // if this is the first move ever:
    if (game->moves_count == 0) {
        game->moves_anchor = newNode;
        game->moves_head = newNode;
        game->moves_count = 1;
        game->gameBoard = newNode->board;
        return game->moves_head;
    }

    // free the moves after what was the current move (the head) up until now
    // (clear the redo part of the list)

    if (game->moves_head->next != NULL) {
        // free the next nodes
        int countOfNodesFreed = freeLinkedList(game->moves_head->next, game->m*game->n);
        // and update moves_count (substract count of freed nodes)
        game->moves_count = game->moves_count - countOfNodesFreed;
    }

    game->moves_head->next = newNode;
    game->moves_count++;
    newNode->prev = game->moves_head;
    game->moves_head = newNode;
    game->gameBoard = newNode->board;
    return game->moves_head;
}

// returns the number of different cells between the boards
int compareBoards(int **boardFrom, int **boardTo, int rows, int columns, bool shouldPrint, char* prefix) {
    int from = 0;
    int to = 0;
    char from_str[10] = {0};
    char to_str[10] = {0};
    int counter = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            from = boardFrom[row][col];
            to = boardTo[row][col];
            if (from != to) {
                counter ++;
            }
            if (shouldPrint && (from != to)) {

                sprintf(from_str, "%d", from);
                if (from == 0) {
                    sprintf(from_str, "_");
                }

                sprintf(to_str, "%d", to);
                if (to == 0) {
                    sprintf(to_str, "_");
                }

                printf("%s %d,%d: from %s to %s\n", prefix, col+1, row+1, from_str, to_str);
            }
        }
    }
    return counter;
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
			printSeparatorRow(game->m, game->rows);
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
    insertNewMove(game);
	int** board_copy = copyBoard(game->gameBoard, game->rows, game->columns);
	// iterate over the cells
	for (int i = 0; i < game->rows; i++) {
		for (int j = 0; j < game->columns; j++) {
			if (board_copy[i][j] == 0) {
				// printf("cell %d,%d is empty\n", i + 1, j + 1);
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

void clearGameBoardAndSolution(Game* game) {
    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->columns; j++) {
            game->gameBoard[i][j] = 0;
            game->gameSolution[i][j] = 0;
        }
    }
}

void markNonZeroCellsAsFixed(Game* game) {
    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->columns; j++) {
            if (game->gameBoard[i][j] != 0) {
                game->fixedCells[i][j] = 1;
            } else {
                game->fixedCells[i][j] = 0;
            }
        }
    }
}

int** allocateBoardMemory(int rows, int columns) {
    int** board = (int **)calloc(rows, sizeof(int *));
    if (!board) {
        printf("Error: could not callocate memory for board\n");
        return NULL;
    }
    for (int row = 0; row < rows; row++) {
        board[row] = (int *)calloc(columns, sizeof(int));
        if (!board[row]) {
            printf("Error: could not callocate memory for board's rows\n");
            return NULL;
        }
    }
    return board;
}

void freeBoardMemory(int** board, int rows) {
    for (int row = 0; row < rows; row++) {
        free(board[row]);
    }
    free(board);
}

int getPossibleValues(Game* game, int row, int col, int *possibleValidValues) {
    int numberOfValidValues;
    int value;
    int N = game->m*game->n;

    numberOfValidValues = 0;
    for (value = 1; value <= N; value++) {
        if (isValidMove(game->gameBoard, game->m, game->n, N, row, col, value)) {
            possibleValidValues[numberOfValidValues] = value;
            numberOfValidValues++;
        }
    }
    // at this point the array of possible valid values starts with
    // numberOfValidValues values, followed by N - numberOfValidValues zeroes.
    return numberOfValidValues;
}

int getRandomValidValue(Game *game, int row, int col) {

    // strategy:
    // 1. find out what are all the valid values for that cell
    // 2. randomly choose one of the valid values

    int *possibleValidValues;
    int N = game->m*game->n;
    int numberOfValidValues, randomIndex, randomValue;

    // callocating an int array of size N to hold possible valid values
    possibleValidValues = (int *)calloc((size_t)N, sizeof(int));
    if (possibleValidValues == NULL) {
        printf("Error: could not callocate memory for possibleValidValues\n");
        exit(1);
    }

    numberOfValidValues = getPossibleValues(game, row, col, possibleValidValues);
    if (numberOfValidValues == 0) {
        // no possible values for cell (row, col)
        return 0;
    }
    // choose a random index between 0 to (numberOfValidValues - 1)
    randomIndex = rand() % numberOfValidValues;
    randomValue = possibleValidValues[randomIndex];

    free(possibleValidValues);
    return randomValue;
}

int fillXCellsRandomly(Game *game, int X) {
    // keep a record of the already chosen cells
    int** alreadyChosenCells = allocateBoardMemory(game->rows, game->columns);

    int counter = 0;
    int N = game->m*game->n;
    int randomRow, randomCol, randomValue;

    while (counter < X) {
        randomRow = rand() % N;
        randomCol = rand() % N;

        // make sure this cell was not already chosen
        while (alreadyChosenCells[randomRow][randomCol] == 1) {
            randomRow = rand() % N;
            randomCol = rand() % N;
        }
        randomValue = getRandomValidValue(game, randomRow, randomCol);
        if (randomValue == 0) {
            // failed to find a valid value for current cell, got to start over
            freeBoardMemory(alreadyChosenCells, game->rows);
            return 1;
        }
        game->gameBoard[randomRow][randomCol] = randomValue;
        alreadyChosenCells[randomRow][randomCol] = 1;
        counter++;
    }

    freeBoardMemory(alreadyChosenCells, game->rows);
    return 0;
}

int clearAllButYCellsRandomly(Game *game, int Y) {
    // keep a record of the already cleared cells
    int** alreadyClearedCells = allocateBoardMemory(game->rows, game->columns);

    int counter = 1;
    int N = game->m*game->n;
    int numberOfCellsToClear = (N * N) - Y;
    // numberOfCellsToClear should never be negative,
    // such error should be handled at the command parsing stage
    int randomRow, randomCol;

    while (counter <= numberOfCellsToClear) {
        randomRow = rand() % N;
        randomCol = rand() % N;

        // make sure this cell was not already cleared
        while (alreadyClearedCells[randomRow][randomCol] == 1) {
            randomRow = rand() % N;
            randomCol = rand() % N;
        }

        game->gameBoard[randomRow][randomCol] = 0;
        alreadyClearedCells[randomRow][randomCol] = 1;
        counter++;
    }

    freeBoardMemory(alreadyClearedCells, game->rows);
    return 0;
}

void copySolutionToBoard(Game* game) {
    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->columns; j++) {
            game->gameBoard[i][j] = game->gameSolution[i][j];
        }
    }
}

int generate(Game* game, int X, int Y) {

    // first make sure the board is empty
    if (!isBoardEmpty(game)) {
        printf("Error: board is not empty\n");
        return 1;
    }

    int failedToFillXCells;
    int failedToSolve;

    for (int i = 0; i < 1000; i++) {

        // step 1: randomly choose X cells and fill them with random values
        // if at any point there is a cell that doesn't have a legal value,
        // start again, up to 1000 times.
        failedToFillXCells = fillXCellsRandomly(game, X);
        if (failedToFillXCells) { // failed to fill X cells randomly with legal values
            clearGameBoardAndSolution(game);
            continue; // move on to next iteration
        }

        // step 2: run ILP and solve the board. If the board is not solvable,
        // start again, up to 1000 times.
        failedToSolve = solveWithILP(game->m, game->n, game->gameBoard, game->gameSolution);
        if (failedToSolve) {
            clearGameBoardAndSolution(game);
            continue; // move on to next iteration
        }

        break;
    }

    if (failedToFillXCells || failedToSolve) {
        printf("Error: puzzle generator failed\n");
        return 1;
    }

    // copy the solution to the game board
    copySolutionToBoard(game);

    // step 3: clear all cells except for Y cells, in the gameBoard
    clearAllButYCellsRandomly(game, Y);

    // mark the Y cells as fixed
    markNonZeroCellsAsFixed(game);

    return 0;
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

void free2DIntArray(int** array, int N) {
    for (int i = 0; i < N; i++) {
        free(array[i]);
    }
    free(array);
}

void destroyGame(Game* game) {

    int N = game->n*game->m;

    // free2DIntArray(game->gameBoard, N); // the game board is freed with the linked list
    free2DIntArray(game->fixedCells, N);
    free2DIntArray(game->errorCells, N);
    free2DIntArray(game->gameSolution, N);

	if (game->moves_anchor != NULL) {
        freeLinkedList(game->moves_anchor, N);
	}

	// free game itself
	free(game);
}
