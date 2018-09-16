#ifndef GAME_H_
#define GAME_H_
#include <stdbool.h>
#include "LinkedList.h"

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
 * ("fixed" cells). Calls initBoard to initiate the game board.
 *
 * @fixedAmount - The total number of fixed cells to start the game.
 * @return
 * NULL if a memory allocation failure occurs.
 * Otherwise, a new game instant is returned.
 */
Game* createGame(int fixedAmount);

Game* createEmptyGame();
/**
 * Frees all memory allocation associated with a given game. If game == NULL
 * the function does nothing.
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
 */
Node* insertNewMove(Game *game);

/**
 * Checks if a value can be put in the specified cell.
 * Checks both is the specified cell is not a fixed cell
 * and if the proposed value doesn't break the solution.
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

bool isBoardEmpty(Game* game);

void autofill(Game* game);

int generate(Game* game, int x, int y);

bool isNoError(Game* game);

int** copyBoard(int **gameBoard, int rows, int columns);

void freeBoardMemory(int** board, int rows);

int compareBoards(int **boardFrom, int **boardTo, int rows, int columns, bool shouldPrint, char* prefix);

#endif /* GAME_H_ */
