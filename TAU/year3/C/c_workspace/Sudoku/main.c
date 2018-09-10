/*
 * main.c
 *
 *  Created on: 20 May 2018
 *      Author: Shif
 */
#include <string.h> // TODO: delete unused includes
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include "Game.h"
#include "Parser.h"
#include "FileHandler.h"
#include "LinkedList.h"
#include "ILPSolver.h"
#define ERROR_MESSAGE "ERROR: invalid command\n"

typedef enum {
	INITMODE,
	SOLVEMODE,
	EDITMODE
} MODE;

int countDigits(int n) {
	int count = 0;
	while(n != 0) {
		n /= 10;
		++count;
	}
	return count;
}

char* zeroToUnderscore(char *str, int value) {
	if (value == 0) {
		str = "_";
	} else {
		sprintf(str, "%d", value);
	}
	return str;
}

bool errorsExist(Game* game) {
	for (int i = 0; i < game->rows; i++) {
		for (int j = 0; j < game->columns; j++) {
			if (game->errorCells[i][j] == 1) {
				return 1;
			}
		}
	}
	return 0;
}

void printGameSolution(Game* game) {
    printf("this is the solution:\n");
    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->columns; j++) {
            printf("%d ", game->gameSolution[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {

	MODE mode = INITMODE;
	bool mark_errors = 0;
	printf("Sudoku\n------\n");

	// allocate memory for the input string from the user
	char* str = (char*) malloc(MAX_LINE_LENGTH * sizeof(char));

	// take care of failure to allocate memory
	if (!str) {
		printf("Error: sudoku game has failed");
		free(str);
		exit(EXIT_FAILURE);
	}

	// create an empty game
	Game* game = createGame(0);

	while(1) {
		printf("Enter your command:\n");

		// take care of failure to read the user input
		if (!fgets(str, MAX_LINE_LENGTH, stdin)) {
			printf("Error: sudoku game has failed");
			free(str);
			exit(EXIT_FAILURE);
		}

		// at this stage the user input is in str
		// use the parser to parse the command in str
		Command command = parserParseLine(str, game->rows);

		if (command.cmd == INVALID_LINE) {
			printf(ERROR_MESSAGE);
		}

		else if (command.cmd == SOLVE) {
			mode = SOLVEMODE;
			int loading_for_solve_result = loadPuzzleFromFile(command.filename, game);
            // TODO: look for erroneous values and fix game->errorCells accordingly
			printBoard(game, mark_errors);
		}

		else if (command.cmd == EDIT) {
			mode = EDITMODE;
			mark_errors = 1;
			printf("the filename is: %s\n", command.filename);
			if (NULL != command.filename) {
				int loading_for_edit_result = loadPuzzleFromFile(command.filename, game);
				printf("the loading of the game for editing returned: %d\n", loading_for_edit_result);
			} else {
				// start an empty game size 9X9
				game = createEmptyGame();
				printBoard(game, mark_errors);
			}

		}

		else if (command.cmd == MARK_ERRORS) {
			if (mode != SOLVEMODE) {
				printf(ERROR_MESSAGE);
			} else {
				mark_errors = command.X;
			}
		}

		else if (command.cmd == PRINT_BOARD) {
			if (mode == INITMODE) {
				printf(ERROR_MESSAGE);
			} else {
				printBoard(game, mark_errors);
			}
		}

		else if (command.cmd == SET) {
			if (mode == INITMODE) {
				printf(ERROR_MESSAGE);
			} else {
				if (command.X <= 0 || command.X > game->rows) {
					printf("Error: value not in range 1-%d\n", game->rows);
					printf(ERROR_MESSAGE);
				} else if (command.Y <= 0 || command.Y > game->columns) {
					printf("Error: value not in range 1-%d\n", game->columns);
					printf(ERROR_MESSAGE);
				} else if (command.Z < 0 || command.Z > game->columns) {
					printf("Error: value not in range 0-%d\n", game->columns);
					printf(ERROR_MESSAGE);
				} else {
					if (game->fixedCells[command.X - 1][command.Y - 1] == 1) {
						printf("Error: cell is fixed\n");
					} else {
						int value_before = game->gameBoard[command.X - 1][command.Y - 1];
						setValue(game, command.X, command.Y, command.Z);
						// first make the current move the head of the list
						// (clear the redo part of the list)
						if (NULL != game->moves) {
							game->moves = game->current_move;
							game->moves->prev = NULL;
						}
						// add the command to the game linked list
						game->moves = InsertAtHead(command.X - 1, command.Y - 1, command.Z, value_before, game->moves);
						game->current_move = game->moves;
						printf("game->moves are:\n");
						Node *temp = game->moves;
						while (temp != NULL) {
							printf("move was set cell %d,%d to value %d\n", temp->X, temp->Y, temp->value);
							temp = temp->prev;
						}
						printBoard(game, mark_errors);
						if (mode == SOLVEMODE) {
						    if (isBoardFull(game) && errorsExist(game)) {
                                printf("Puzzle solution erroneous\n");
						    } else if (isBoardFull(game) && !errorsExist(game)) {
                                printf("Puzzle solved successfully\n");
                                mode = INITMODE;
						    }
						}
					}
				}
			}
		}

		else if (command.cmd == VALIDATE) {
			if (mode == INITMODE) {
                printf(ERROR_MESSAGE);
            } else if (errorsExist(game)) {
                printf("Error: board contains erroneous values\n");
			} else {
                int solver_result = solveWithILP(game->m, game->n, game->gameBoard, game->gameSolution);
                if (solver_result == 0) {
                    printf("Validation passed: board is solvable\n");

                    // TODO: remove this part later
                    printGameSolution(game);

                } else {
                    printf("Validation failed: board is unsolvable\n");
                }
			}
		}

		else if (command.cmd == GENERATE) {
			if (mode != EDITMODE) {
				printf(ERROR_MESSAGE);
			} else {
                int generate_result = generate(game, command.X, command.Y);
			}
		}

		else if (command.cmd == UNDO) {
			if (mode == INITMODE) {
				printf(ERROR_MESSAGE);
			} else {
				if (game->moves == NULL || game->current_move == NULL) {
				    printf("Error: no moves to undo\n");
				} else {
				    // first undo the move
				    int curr_value = game->current_move->value;
					int prev_value = game->current_move->prev_value;
					int x = game->current_move->X;
					int y = game->current_move->Y;
					game->gameBoard[x][y] = prev_value;
				    // then move the 'current move' pointer
                    game->current_move = game->current_move->prev;

					printBoard(game, mark_errors);

					int from_value_len = countDigits(curr_value);
					char *from = (char *)calloc(from_value_len, sizeof(char));
					if (from == NULL) {
						printf("Problem: could not allocate memory to string 'from'\n");
						printf("Exiting... \n");
						return 1;
					}
					from = zeroToUnderscore(from, curr_value);

					int to_value_len = countDigits(prev_value);
					char *to = (char *)calloc(to_value_len, sizeof(char));
					if (to == NULL) {
						printf("Problem: could not allocate memory to string 'to'\n");
						printf("Exiting... \n");
						return 1;
					}
					to = zeroToUnderscore(to, prev_value);

                    printf("Undo %d,%d: from %s to %s\n", x+1, y+1, from, to);
                    // free(from); // How come I don't need to free this?
                    // free(to);
				}
			}
		}

		else if (command.cmd == REDO) {
			if (mode == INITMODE) {
				printf(ERROR_MESSAGE);
			} else {
				if (game->moves == NULL) {
					printf("Error: no moves to redo\n");
				} else if (game->current_move != NULL && game->current_move->next == NULL) {
					printf("Error: no moves to redo\n");
				} else {
					// first redo the move
					// if all of the moves were undone, current_move is NULL
					// therefore, the next move to redo is at the end of the list
					Node *move_to_redo = game->moves;
					if (game->current_move == NULL) {
						while (move_to_redo->prev != NULL) {
							move_to_redo = move_to_redo->prev;
						}
					} else {
						move_to_redo = game->current_move->next;
					}
					int next_value = move_to_redo->value;
					int x = move_to_redo->X;
					int y = move_to_redo->Y;
					game->gameBoard[x][y] = next_value;
					printBoard(game, mark_errors);
					int from_value = 0;
					if (game->current_move != NULL) {
						from_value = game->current_move->value;
					}

					int from_value_len = countDigits(from_value);
					char *from = (char *)calloc(from_value_len, sizeof(char));
					if (from == NULL) {
						printf("Problem: could not allocate memory to string 'from'\n");
						printf("Exiting... \n");
						return 1;
					}
					from = zeroToUnderscore(from, from_value);

					int to_value_len = countDigits(next_value);
					char *to = (char *)calloc(to_value_len, sizeof(char));
					if (to == NULL) {
						printf("Problem: could not allocate memory to string 'to'\n");
						printf("Exiting... \n");
						return 1;
					}
					to = zeroToUnderscore(to, next_value);

					printf("Redo %d,%d: from %s to %s\n", x, y, from, to);
					// free(from);
					// free(to);

					// then move the 'current move' pointer
					game->current_move = move_to_redo;
				}
			}
		}

		else if (command.cmd == SAVE) {
			if (mode == INITMODE) {
				printf(ERROR_MESSAGE);
				continue;
			}
            if (mode == EDITMODE) {
                // first make sure there are no erroneous values
                if (errorsExist(game)) {
                    printf("Puzzles with erroneous values may not be saved!\n");
                    continue;
                }
                // now make sure the board is solvable
                int solver_result = solveWithILP(game->m, game->n, game->gameBoard, game->gameSolution);
                if (solver_result == 1) {
                    printf("Error: board validation failed\n");
                    continue;
                }
            }

            bool non_empty_cells_are_fixed = 0;
            if (mode == EDITMODE) {
                non_empty_cells_are_fixed = 1;
            }
			int saving_result = savePuzzleToFile(command.filename, game, non_empty_cells_are_fixed);
			printf("the saving of the game to file named %s returned: %d\n", command.filename, saving_result);
			printf("Saved to: %s\n", command.filename);
		}

		else if (command.cmd == HINT) {
			if (mode != SOLVEMODE) {
				printf(ERROR_MESSAGE);
            } else if (errorsExist(game)) {
                printf("Error: board contains erroneous values\n");
            } else if (command.X <= 0 || command.X > game->rows) {
			    printf("Error: value not in range 1-%d\n", game->rows);
			    printf(ERROR_MESSAGE);
			} else if (command.Y <= 0 || command.Y > game->columns) {
			    printf("Error: value not in range 1-%d\n", game->columns);
			    printf(ERROR_MESSAGE);
            } else if (game->fixedCells[command.X - 1][command.Y - 1] == 1) {
			    printf("Error: cell is fixed\n");
			} else if (game->gameBoard[command.X - 1][command.Y - 1] != 0) {
				printf("Error: cell already contains a value\n");
			} else {
                int solver_result = solveWithILP(game->m, game->n, game->gameBoard, game->gameSolution);
                if (solver_result == 1) {
                    printf("Error: board is unsolvable\n");
                } else {
                    // TODO: remove this part later
                    printGameSolution(game);

                    printf("Hint: set cell to %d\n", game->gameSolution[command.X - 1][command.Y - 1]);
                }
			}
		}

		else if (command.cmd == NUM_SOLUTIONS) {
			if (mode == INITMODE) {
				printf(ERROR_MESSAGE);
			} else {
                // first make sure there are no erroneous values
                if (errorsExist(game)) {
                    printf("Error: board contains erroneous values\n");
                } else {
                    // run the exhaustive backtracking algorithm
					int number_of_solutions = numSolutions(game);
                    // print out how many solutions exist
					printf("Number of solutions: %d\n",number_of_solutions);
					if (number_of_solutions == 1) {
						printf("This is a good board!\n");
					} else if (number_of_solutions > 1) {
						printf("The puzzle has more than 1 solution, try to edit it further\n");
					}
                }
			}
		}

		else if (command.cmd == AUTOFILL) {
			if (mode != SOLVEMODE) {
				printf(ERROR_MESSAGE);
			} else {
				// first make sure there are no erroneous values
				if (errorsExist(game)) {
					printf("Error: board contains erroneous values\n");
				} else {
					autofill(game);
					printBoard(game, mark_errors);
				}
			}
		}

		else if (command.cmd == RESET) {
			if (mode == INITMODE) {
				printf(ERROR_MESSAGE);
			} else {
				// undo until there are no more moves to undo
				if (game->moves == NULL || game->current_move == NULL) {
					// no moves to undo
				} else {
					while (game->current_move != NULL) {
						int prev_value = game->current_move->prev_value;
						int x = game->current_move->X;
						int y = game->current_move->Y;
						game->gameBoard[x][y] = prev_value;
						// then move the 'current move' pointer
						game->current_move = game->current_move->prev;
					}
				}
				printf("Board reset\n");
				printBoard(game, mark_errors);
			}
		}

		else if (command.cmd == EXIT) {
			printf("Exiting...\n");
			// free all memory
			destroyGame(game);
			printf("freed game memory successfully\n");
			return 0;
		}
	}

	return 0;
}
