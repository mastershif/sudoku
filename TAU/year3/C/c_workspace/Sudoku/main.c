#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include "Game.h"
#include "Parser.h"
#include "FileManager.h"
#include "LinkedList.h"
#include "ILPSolver.h"
#include "Solver.h"

#define ERROR_MESSAGE "ERROR: invalid command\n"

typedef enum {
	INITMODE,
	SOLVEMODE,
	EDITMODE
} MODE;

bool errorsExist(Game* game);

void updateErrorCells(Game *game);

void deduplicateMovesHead(Game* game);

void handleSolveCommand(Game* game, Command* command, MODE* mode);

void handleEditCommand(Command* command, MODE* mode, bool* mark_errors, Game** game);

void handleMarkErrorsCommand(Command* command, MODE* mode, bool* mark_errors);

void handlePrintBoardCommand(MODE *mode, bool mark_errors, Game *game);

void handleSetCommand(Command* command, MODE* mode, bool mark_errors, Game* game);

void handleValidateCommand(MODE *mode, Game *game);

void handleGenerateCommand(MODE *mode, bool mark_errors, Game *game, Command *command);

void handleSaveCommand(Command *command, MODE *mode, Game *game);

void handleHintCommand(Command *command, MODE *mode, Game *game);

void handleNumSolutions(MODE *mode, Game *game);

void handleAutofillCommand(MODE *mode, bool mark_errors, Game *game);

void handleResetCommand(MODE *mode, Game *game);

void handleExitCommand(Game *game);

void handleUndoCommand(MODE *mode, bool mark_errors, Game *game);

void handleRedoCommand(MODE *mode, bool mark_errors, Game *game);

int main() {

	MODE mode = INITMODE;
	bool mark_errors = 1;
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

		Command command = parserParseLine(str, game->rows);

		if (command.cmd == INVALID_LINE) {
			printf(ERROR_MESSAGE);
		}

		else if (command.cmd == SOLVE) {
            handleSolveCommand(game, &command, &mode);
        }

		else if (command.cmd == EDIT) {
            handleEditCommand(&command, &mode, &mark_errors, &game);
        }

		else if (command.cmd == MARK_ERRORS) {
            handleMarkErrorsCommand(&command, &mode, &mark_errors);
        }

		else if (command.cmd == PRINT_BOARD) {
            handlePrintBoardCommand(&mode, mark_errors, game);
        }

		else if (command.cmd == SET) {
            handleSetCommand(&command, &mode, mark_errors, game);
        }

		else if (command.cmd == VALIDATE) {
            handleValidateCommand(&mode, game);
        }

		else if (command.cmd == GENERATE) {
            handleGenerateCommand(&mode, mark_errors, game, &command);
        }

		else if (command.cmd == UNDO) {
            handleUndoCommand(&mode, mark_errors, game);
        }

		else if (command.cmd == REDO) {
            handleRedoCommand(&mode, mark_errors, game);
        }

		else if (command.cmd == SAVE) {
            handleSaveCommand(&command, &mode, game);
		}

		else if (command.cmd == HINT) {
            handleHintCommand(&command, &mode, game);
        }

		else if (command.cmd == NUM_SOLUTIONS) {
            handleNumSolutions(&mode, game);
        }

		else if (command.cmd == AUTOFILL) {
            handleAutofillCommand(&mode, mark_errors, game);
        }

		else if (command.cmd == RESET) {
            handleResetCommand(&mode, game);
        }

		else if (command.cmd == EXIT) {
		    handleExitCommand(game);
            return 0;
        }
	}
}

void updateErrorCells(Game *game) {
    int N = game->m*game->n;
    for (int row = 0; row < game->rows; row++) {
        for (int col = 0; col < game->columns; col++) {
            int value = game->gameBoard[row][col];
            bool isValidValue = isValidMove(game->gameBoard, game->m, game->n, N, row, col, value);
            if (isValidValue) {
                game->errorCells[row][col] = 0;
            } else {
                game->errorCells[row][col] = 1;
            }
        }
    }
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

void deduplicateMovesHead(Game* game) {
    if (game->moves_anchor == NULL) { // there were never any moves
        return;
    }
    if (game->moves_head == NULL) { // there are no duplicates moves
        return;
    }
    if (game->moves_head->next == NULL) { // there is only 1 move, no duplicates
        return;
    }
    // go to the last move that was added to the list
    Node* one_move_before_last_move = game->moves_anchor;
    Node* last_move = game->moves_anchor->next;

    while (last_move->next != NULL) {
        last_move = last_move->next;
        one_move_before_last_move = last_move->prev;
    }
    // now check if both boards are the same, if so remove the last move
    // (because it is a duplicate)
    int diff = compareBoards(one_move_before_last_move->board, last_move->board, game->rows, game->columns, 0, "");
    if (diff == 0) {
        freeBoardMemory(last_move->board, game->rows);
        free(last_move);
        one_move_before_last_move->next = NULL;
    }
}

void handleSolveCommand(Game* game, Command *command, MODE* mode) {
    (*mode) = SOLVEMODE;
    loadPuzzleFromFile((*command).filename, game);
    updateErrorCells(game);
    // printBoard(game, mark_errors); // no need to print board according to published test
}

void handleEditCommand(Command* command, MODE* mode, bool* mark_errors, Game** game) {
    (*mode) = EDITMODE;
    (*mark_errors) = 1;
    if (NULL != (*command).filename) {
        loadPuzzleFromFile((*command).filename, (*game));
    } else {
        // start an empty game size 9X9
        (*game) = createEmptyGame();
        // printBoard(game, mark_errors);
    }
}

void handleMarkErrorsCommand(Command* command, MODE* mode, bool* mark_errors) {
    if ((*mode) != SOLVEMODE) {
        printf(ERROR_MESSAGE);
    } else {
        (*mark_errors) = (*command).X;
    }
}

void handlePrintBoardCommand(MODE *mode, bool mark_errors, Game *game) {
    if ((*mode) == INITMODE) {
        printf(ERROR_MESSAGE);
    } else {
        printBoard(game, mark_errors);
    }
}

bool areValidArgsForSetCommand(Command *command, Game *game) {
    bool result = 1; // 1 means valid args
    if ((*command).X <= 0 || (*command).X > game->rows) {
        printf("Error: value not in range 1-%d\n", game->rows);
        printf(ERROR_MESSAGE);
        result = 0;
        return result;
    } else if ((*command).Y <= 0 || (*command).Y > game->columns) {
        printf("Error: value not in range 1-%d\n", game->columns);
        printf(ERROR_MESSAGE);
        result = 0;
        return result;
    } else if ((*command).Z < 0 || (*command).Z > game->columns) {
        printf("Error: value not in range 0-%d\n", game->columns);
        printf(ERROR_MESSAGE);
        result = 0;
        return result;
    } else if (game->fixedCells[(*command).X - 1][(*command).Y - 1] == 1) {
        printf("Error: cell is fixed\n");
        result = 0;
        return result;
    } else {
        return result;
    }
}

void handleSetCommand(Command* command, MODE* mode, bool mark_errors, Game* game) {
    if ((*mode) == INITMODE) {
        printf(ERROR_MESSAGE);
        return;
    }
    bool areValidArgs = areValidArgsForSetCommand(command, game);
    if (!areValidArgs) {
        return;
    }
    if (game->gameBoard[(*command).X - 1][(*command).Y - 1] == (*command).Z) {
        // no need to add a move
        printBoard(game, mark_errors);
        if ((*mode) == SOLVEMODE) {
            if (isBoardFull(game) && errorsExist(game)) {
                printf("Puzzle solution erroneous\n");
            } else if (isBoardFull(game) && !errorsExist(game)) {
                printf("Puzzle solved successfully\n");
                (*mode) = INITMODE;
            }
        }
        return;
    }
    game->moves_head = insertNewMove(game);
    setValue(game, (*command).X, (*command).Y, (*command).Z);
    updateErrorCells(game);
    printBoard(game, mark_errors);
    if ((*mode) == SOLVEMODE) {
        if (isBoardFull(game) && errorsExist(game)) {
            printf("Puzzle solution erroneous\n");
        } else if (isBoardFull(game) && !errorsExist(game)) {
            printf("Puzzle solved successfully\n");
            (*mode) = INITMODE;
        }
    }
    deduplicateMovesHead(game);
}

void handleValidateCommand(MODE *mode, Game *game) {
    if ((*mode) == INITMODE) {
        printf(ERROR_MESSAGE);
    } else if (errorsExist(game)) {
        printf("Error: board contains erroneous values\n");
    } else {
        int solver_result = solveWithILP(game->m, game->n, game->gameBoard, game->gameSolution);
        if (solver_result == 0) {
            printf("Validation passed: board is solvable\n");
        } else {
            printf("Validation failed: board is unsolvable\n");
        }
    }
}

void handleGenerateCommand(MODE *mode, bool mark_errors, Game *game, Command *command) {
    if ((*mode) != EDITMODE) {
        printf(ERROR_MESSAGE);
    } else {
        int generate_result = generate(game, (*command).X, (*command).Y);
        printf("generating a new game returned %d\n", generate_result);
        if (generate_result == 0) {
            printBoard(game, mark_errors);
        }
    }
}

void handleRedoCommand(MODE *mode, bool mark_errors, Game *game) {
    if ((*mode) == INITMODE) {
        printf(ERROR_MESSAGE);
        return;
    }

    if (game->moves_anchor == NULL) {
        printf("Error: no moves to redo\n");
        return;
    }
    if (game->moves_head != NULL && game->moves_head->next == NULL) {
        printf("Error: no moves to redo\n");
        return;
    }

    int** curr_board = game->gameBoard;
    int** next_board;

    if (game->moves_head == NULL) {
        next_board = game->moves_anchor->board;
        game->moves_head = game->moves_anchor;
    } else {
        next_board = game->moves_head->next->board;
        game->moves_head = game->moves_head->next;
    }

    // 1: first redo the move
    // change the board state to the next move
    game->gameBoard = next_board;

    // 2: then print the board
    updateErrorCells(game);
    printBoard(game, mark_errors);

    // 3: print differences
    compareBoards(curr_board, next_board, game->rows, game->columns, 1, "Redo");
}

void handleUndoCommand(MODE *mode, bool mark_errors, Game *game) {
    if ((*mode) == INITMODE) {
        printf(ERROR_MESSAGE);
        return;
    }

    if (game->moves_anchor == NULL || game->moves_head == NULL) {
        printf("Error: no moves to undo\n");
        return;
    }

    int **prev_board;
    int **curr_board = game->gameBoard;

    // 1: first undo the move
    // if there is only 1 move in the list, need to clear the list
    // and return to original board state
    if (
            (game->moves_anchor != NULL && game->moves_head == NULL) ||
            (game->moves_anchor != NULL && game->moves_head != NULL && game->moves_head->prev == NULL)){
//        prev_board = copyBoard(game->originalBoard, game->rows, game->columns);
        prev_board = game->originalBoard;
    } else {
        // otherwise, simply return to the board state from the previous move
        prev_board =  game->moves_head->prev->board;
    }
    game->gameBoard = prev_board;
    game->moves_head = game->moves_head->prev;

    // 2: then print the board
    updateErrorCells(game);
    printBoard(game, mark_errors);
    compareBoards(curr_board, prev_board, game->rows, game->columns, 1, "Undo");
}

void handleSaveCommand(Command *command, MODE *mode, Game *game) {
    if ((*mode) == INITMODE) {
        printf(ERROR_MESSAGE);
        return;
    }
    if ((*mode) == EDITMODE && errorsExist(game)) {
        printf("Puzzles with erroneous values may not be saved!\n");
        return;
    }
    if ((*mode) == EDITMODE) {
        // make sure the board is solvable
        int solver_result = solveWithILP(game->m, game->n, game->gameBoard, game->gameSolution);
        if (solver_result == 1) {
            printf("Error: board validation failed\n");
            return;
        }
    }
    bool non_empty_cells_are_fixed = 0;
    if ((*mode) == EDITMODE) {
        non_empty_cells_are_fixed = 1;
    }
    savePuzzleToFile((*command).filename, game, non_empty_cells_are_fixed);
    printf("Saved to: %s\n", (*command).filename);
}

void handleHintCommand(Command *command, MODE *mode, Game *game) {
    if ((*mode) != SOLVEMODE) {
        printf(ERROR_MESSAGE);
    } else if (errorsExist(game)) {
        printf("Error: board contains erroneous values\n");
    } else if ((*command).X <= 0 || (*command).X > game->rows) {
        printf("Error: value not in range 1-%d\n", game->rows);
        printf(ERROR_MESSAGE);
    } else if ((*command).Y <= 0 || (*command).Y > game->columns) {
        printf("Error: value not in range 1-%d\n", game->columns);
        printf(ERROR_MESSAGE);
    } else if (game->fixedCells[(*command).X - 1][(*command).Y - 1] == 1) {
        printf("Error: cell is fixed\n");
    } else if (game->gameBoard[(*command).X - 1][(*command).Y - 1] != 0) {
        printf("Error: cell already contains a value\n");
    } else {
        int solver_result = solveWithILP(game->m, game->n, game->gameBoard, game->gameSolution);
        if (solver_result == 1) {
            printf("Error: board is unsolvable\n");
        } else {
            printf("Hint: set cell to %d\n", game->gameSolution[(*command).X - 1][(*command).Y - 1]);
        }
    }
}

void handleNumSolutions(MODE *mode, Game *game) {
    if ((*mode) == INITMODE) {
        printf(ERROR_MESSAGE);
    } else {
        // first make sure there are no erroneous values
        if (errorsExist(game)) {
            printf("Error: board contains erroneous values\n");
        } else {
            // run the exhaustive backtracking algorithm
            int number_of_solutions = numSolutions(game, game->m*game->n);
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

void handleAutofillCommand(MODE *mode, bool mark_errors, Game *game) {
    if ((*mode) != SOLVEMODE) {
        printf(ERROR_MESSAGE);
        return;
    }
    // first make sure there are no erroneous values
    if (errorsExist(game)) {
        printf("Error: board contains erroneous values\n");
        return;
    }
    autofill(game);
    printBoard(game, mark_errors);
    deduplicateMovesHead(game);
}

void handleResetCommand(MODE *mode, Game *game) {
    if ((*mode) == INITMODE) {
        printf(ERROR_MESSAGE);
        return;
    }
    // undo until there are no more moves to undo
    if (game->moves_anchor != NULL) {
        game->gameBoard = game->originalBoard;
        // free the memory for the moves list
        freeLinkedList(game->moves_anchor, game->m*game->n);
        game->moves_anchor = NULL;
        game->moves_count = 0;
        game->moves_head = NULL;
        game->moves_index = 0;
    }
    printf("Board reset\n");
//    printBoard(game, mark_errors);

}

void handleExitCommand(Game *game) {
    printf("Exiting...\n");
    destroyGame(game);
}
