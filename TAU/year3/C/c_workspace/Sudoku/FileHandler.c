#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "FileHandler.h"
#include "LinkedList.h"

// TODO: change file name to FileManager instead of FileHandler

int loadPuzzleFromFile(char* filename, Game* game) {
	FILE* inputfile;
	inputfile = fopen(filename, "r");

	if(inputfile == NULL) {
		printf("Error: File doesn’t exist or cannot be opened\n");
		exit(1);
	}

	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	// the first line is "m n" : m the number of rows in each box
	// read the first line
	read = getline(&line, &len, inputfile);
	game->m = atoi(line);
	line += 2;
	game->n = atoi(line);
	game->rows = game->n*game->m;
	game->columns = game->n*game->m;
	game->size = game->rows*game->columns;
	game->moves = NULL;
	game->current_move = NULL;

//	game->moves = (Node *)calloc(1, sizeof(Node));
//	if(game->moves == NULL) {
//		printf("Error: could not callocate memory for moves\n");
//		exit(1);
//	}
//    game->current_move = (Node *)calloc(1, sizeof(Node));
//	if(game->current_move == NULL) {
//		printf("Error: could not callocate memory for current_move\n");
//		exit(1);
//	}

	// allocate memory for the game board
	game->gameBoard = (int **)calloc(game->n*game->m, sizeof(int *));
	if (!game->gameBoard) {
		return 1;
	}
	for (int row = 0; row < game->n*game->m; row++) {
		game->gameBoard[row] = (int *)calloc(game->n*game->m, sizeof(int));
		if (!game->gameBoard[row]) {
			return 1;
		}
	}

	// allocate memory for the fixed cells 2D array
	game->fixedCells = (int **)calloc(game->n*game->m, sizeof(int *));
	if (!game->fixedCells) {
		return 1;
	}
	for (int row = 0; row < game->n*game->m; row++) {
		game->fixedCells[row] = (int *)calloc(game->n*game->m, sizeof(int));
		if (!game->fixedCells[row]) {
			return 1;
		}
	}

	// allocate memory for the error cells 2D array
	game->errorCells = (int **)calloc(game->n*game->m, sizeof(int *));
	if (!game->errorCells) {
		return 1;
	}
	for (int row = 0; row < game->n*game->m; row++) {
		game->errorCells[row] = (int *)calloc(game->n*game->m, sizeof(int));
		if (!game->errorCells[row]) {
			return 1;
		}
	}

	// allocate memory for the game solution
	game->gameSolution = (int **)calloc(game->n*game->m, sizeof(int *));
	if (!game->gameSolution) {
		return 1;
	}
	for (int row = 0; row < game->n*game->m; row++) {
		game->gameSolution[row] = (int *)calloc(game->n*game->m, sizeof(int));
		if (!game->gameSolution[row]) {
			return 1;
		}
	}

	// going back to having line = NULL and len = 0 so getline works out the memory by itself
	line = NULL;
	len = 0;
	// iterate over the file and load the content to the game board
	int row = 0;
	int column = 0;
	game->fixedCount = 0;
	while ((read = getline(&line, &len, inputfile)) != -1 && row < game->n*game->m) {
	    char* token = strtok(line, " "); // split the line
	    while (token != NULL) {
	    	char* temp = (char*)malloc(sizeof(char));
	    	if (temp == NULL) {
	    		return 1;
	    	}
	    	temp = strncpy(temp, token, 1);
	    	game->gameBoard[row][column] = atoi(temp);

			if (NULL != strrchr(token, '.')) { // if the token contains '.'
				// this is a fixed cell
				game->fixedCells[row][column] = 1;
				game->fixedCount++;
			}
	    	free(temp);
	    	column++;
	    	token = strtok(NULL, " ");
	    }
	    printf("\n");
	    column = 0;
	    row++;
	}

//	printf("printing the game board content again: \n");
//	for (int i = 0; i <  game->n*game->m; i++) {
//		for (int j = 0; j < game->n*game->m; j++) {
//			printf("%d ", game->gameBoard[i][j]);
//		}
//		printf("\n");
//	}
//
//	printf("printing the fixed cells array: \n");
//	for (int i = 0; i <  game->n*game->m; i++) {
//		for (int j = 0; j < game->n*game->m; j++) {
//			printf("%d ", game->fixedCells[i][j]);
//		}
//		printf("\n");
//	}
//	printf("the count of fixed cells is: %d\n", game->fixedCount);

	fclose(inputfile);
	if (line) {
		free(line);
	}
	return 0;
}

int savePuzzleToFile(char* filename, Game* game, bool non_empty_cells_are_fixed) {

	FILE* output;
	output = fopen(filename, "wt"); // if the file already exists, its contents are destroyed

	if(output == NULL) {
		printf("Error: File cannot be created or modified\n");
		exit(1);
	}

	fprintf(output, "%d %d\n", game->m, game->n);

	// save the rest of the file
	for (int row = 0; row < game->rows; row++) {
		for (int col = 0; col < game->columns; col++) {
			// print cell value to file
			fprintf(output, "%d", game->gameBoard[row][col]);
			// print . if cell is not 0 and we are in EDIT mode
			if (non_empty_cells_are_fixed && game->gameBoard[row][col] != 0) {
				fprintf(output, ".");
			}
			// print 1 space
			fprintf(output, " "); // TODO: should I not print a space if end of row?
		}
		fprintf(output, "\n");
	}
	fflush(output);
	fclose(output);

	return 0;
}

