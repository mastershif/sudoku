#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_
#include "Game.h"

/**
 * This module deals with file input and output.
 */

/**
 * Loads a sudoku puzzle from a file and updates the game fields accordingly.
 *
 * @param filename - the name of the file where the game board data is.
 * @param game - the game that will use that board data from the file.
 * @return
 * Returns 1 if the loading failed, 0 if the loading succeeded.
 */
int loadPuzzleFromFile(char* filename, Game* game);

/**
 * Saves a sudoku puzzle to a file.
 *
 * @param filename - the name of the file where the game board will be saved.
 * @param game - the game that contains the board data for the file.
 * @param non_empty_cells_are_fixed - whether or non empty cells will be saved
 * with a "." next to them.
 * @return
 * Returns 1 if the saving failed, 0 if the saving succeeded.
 */
int savePuzzleToFile(char* filename, Game* game, bool non_empty_cells_are_fixed);

#endif /* FILEMANAGER_H_ */
