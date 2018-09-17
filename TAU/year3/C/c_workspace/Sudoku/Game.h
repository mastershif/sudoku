#ifndef GAME_H_
#define GAME_H_
#include <stdbool.h>
#include "LinkedList.h"

/**
 * This module defines the game struct and contains different actions that can be taken on the game.
 */

//Definitions

typedef struct game_t {
	int fixedCount;
	int m; // number of rows in each box
	int n; // number of columns in each box
	int rows;
	int columns;
	int size;
	int **gameBoard;
	int **originalBoard;
	int **fixedCells; // 1 represents this location has a fixed cell, 0 otherwise
	int **errorCells; // 1 represents this location has an error, 0 otherwise
	int **gameSolution;
    Node *moves_anchor;
    Node *moves_head; // this points to the current move
	int moves_count;
	int moves_index;
} Game;

/**
 * Creates a new game with a specified number of pre-populated cells
 * ("fixed" cells).
 *
 * @param fixedAmount - the total number of fixed cells to start the game.
 * @return
 * NULL if a memory allocation failure occurs.
 * Otherwise, a new game instant is returned.
 */
Game* createGame(int fixedAmount);

/**
 * Creates a new game with an empty board of size 9X9.
 * Allocated needed memory for the game's fields.
 *
 * @return
 * NULL if a memory allocation failure occurs.
 * Otherwise, a new game instant is returned.
 */
Game* createEmptyGame();

/**
 * Frees all memory allocation associated with a given game. If game == NULL
 * the function does now work.
 *
 * @param game - the game to be destroyed
 */
void destroyGame(Game* game);

/**
 * Sets a value in a given game by specifying row and column index,
 * as well as the value itself. The rows and columns are 0-based and
 * in the ranges [0,N - 1] and [0,N - 1], respectively.
 *
 * @param game - The target game
 * @param row - The target row, the rows are 0-based
 * @param col - The target column, the columns are 0-based
 * @param value - The specified value
 */
void setValue(Game* game, int row, int col, int value);

/**
 * Adds a new move to the linked list of moves.
 *
 * @param game - The game
 * @param X - The row where the new value was entered
 * @param Y - The column where the new value was entered
 * @param value - The value entered during the move
 * @return
 * The head (the current move).
 */
Node* insertNewMove(Game *game);

/**
 * Checks if a value can be put in the specified cell.
 * Checks if the specified cell is not a fixed cell.
 *
 * @param game - The source game
 * @param row - The specified row
 * @param col - The specified column
 * @param value - The specified value
 * @return
 * true  - if the given value can be put in the target cell
 * false - otherwise.
 */
bool isValidMove(int **board, int m, int n, int N, int row, int col, int value);

/**
 * On success, the function prints the game board. If an error occurs, then the
 * function does nothing.
 *
 * @param game - the target game
 * @param mark_errors - should erroneous values be marked or not
 */
void printBoard(Game* game, bool mark_errors);

/**
 * Checks if the game board is full.
 *
 * @param game - the target game
 * @return
 * true  - if the game board is full of values
 * false - otherwise.
 */
bool isBoardFull(Game* game);

/**
 * Checks if the game board is empty.
 *
 * @param game - the target game
 * @return
 * true  - if the game board is empty of values
 * false - otherwise.
 */
bool isBoardEmpty(Game* game);

/**
 * Automatically fill "obvious" values – cells which contain a single legal value.
 * This function goes over the board cells from top to bottom, left to right
 * and checks for an obvious value for each cell according to the state
 * of the board when this function started running.
 *
 * @param game - the game with the sudoku board to be autofilled.
 */
void autofill(Game* game);

/**
 * Generates a new, random and solvable sudoku puzzle.
 * Generates a puzzle by randomly filling X cells with random legal values,
 * running ILP to solve the resulting board, and then clearing all but Y random cells.
 * The function randomly choose X cells, filling each with a legal random value.
 * Once X cells contain values, the function runs ILP to solve the resulting board.
 * After the board is solved, the function randomly chooses Y cells,
 * and clear the values of all other cells.
 * If one of the X randomly-chosen cells has no legal value available,
 * or the resulting board has no solution (the ILP solver fails),
 * the function clears the board entirely and repeats the previous step.
 * After 1000 such iterations, the function prints:
 * "Error: puzzle generator failed\n", and the command is not executed.
 *
 * @param game - the game with the board to be generated.
 * @param x - the number of cells to be filled with random legal values.
 * @param y - the number of cells to remain with values at the end of this function run.
 * @return
 * 1 if the function failed, 0 otherwise.
 */
int generate(Game* game, int x, int y);

/**
 * Checks if the game board is free of errors.
 *
 * @param game - the target game
 * @return
 * true  - if the game board is free of errors
 * false - otherwise.
 */
bool isNoError(Game* game);

/**
 * Makes a copy of a sudoku board.
 *
 * @param gameBoard - the board to be copied.
 * @param rows - the number of rows in the board.
 * @param columns - the number of columns in the board.
 * @return
 * an independent copy of the board.
 */
int** copyBoard(int **gameBoard, int rows, int columns);

/**
 * Free the memory used by a sudoku board.
 *
 * @param board - the board to be freed.
 * @param rows - the number of rows in the board.
 */
void freeBoardMemory(int** board, int rows);

/**
 * Compares two boards and prints the differences for the Undo and Redo commands.
 *
 * @param boardFrom - board number 1 to compare.
 * @param boardTo - board number 2 to compare.
 * @param rows - the number of rows in the boards.
 * @param columns - the number of columns in the boards.
 * @param shouldPrint - whether or not the differences should be printed to the user.
 * @param prefix - used for the printing of "Undo" or "Redo",
 * according to the command using this function
 * @return
 * true  - if the game board is free of errors
 * false - otherwise.
 */
int compareBoards(int **boardFrom, int **boardTo, int rows, int columns, bool shouldPrint, char* prefix);

#endif /* GAME_H_ */
