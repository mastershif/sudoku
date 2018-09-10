#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_
#include "Game.h"

int loadPuzzleFromFile(char* filename, Game* game);

int savePuzzleToFile(char* filename, Game* game, bool non_empty_cells_are_fixed);

#endif /* FILEHANDLER_H_ */
