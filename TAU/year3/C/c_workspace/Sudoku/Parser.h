/*
 * Parcer.h
 *
 *  Created on: 30 May 2018
 *      Author: Shif
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <stdbool.h>

//specify the maximum line length
#define MAX_LINE_LENGTH 256

#define MISSING_ARGS "missing args"

//a type used to represent a command
typedef enum {
	SOLVE, // solve filename *available in all modes*
	EDIT, // edit filename *available in all modes*
	MARK_ERRORS, // only on solve mode
	PRINT_BOARD, // available on edit and solve modes
	SET, // set X Y Z. available on edit and solve modes
	VALIDATE, // available on edit and solve modes
	GENERATE, // only on edit mode
	UNDO, // available on edit and solve modes
	REDO, // available on edit and solve modes
	SAVE, // available on edit and solve modes
	HINT, // hint X Y. only on solve mode
	NUM_SOLUTIONS, // available on edit and solve modes
	AUTOFILL, // fill in obvious cells that have only one option. only on solve mode
	RESET, // undo all moves. available on edit and solve modes
	EXIT, // *available in all modes*
	INVALID_LINE
} COMMAND;

//a new type that is used to encapsulate a parsed line
typedef struct command_t {
	int X;
	int Y;
	int Z;
	char *filename;
	COMMAND cmd;
} Command;

/**
 * Checks if a specified string represents a valid integer. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */
bool parserIsInt(const char* str);

/**
 * Parses a specified line. If the line is a command which has an integer
 * argument then the argument is parsed and is saved in the field arg and the
 * field validArg is set to true. In any other case then 'validArg' is set to
 * false and the value 'arg' is undefined
 *
 * @return
 * A parsed line such that:
 *   cmd - contains the command type, if the line is invalid then this field is
 *         set to INVALID_LINE
 *   validArg - is set to true if the command is add_disc and the integer argument
 *              is valid
 *   arg      - the integer argument in case validArg is set to true
 */
Command parserParseLine(char* str, int nm);

/**
 * Checks what command a specified string represents.
 *
 * @return
 * an integer representing the matching command.
 */
int parserWhichCommand(char* command);

/**
 * Populate the 3 arguments of the command SET.
 *
 * @return
 * the next token in the splitted command.
 */
char* extractArgsForSet(char* token, Command* command, int nm);

/**
 * Populate the 2 arguments of the command HINT.
 *
 * @return
 * the next token in the splitted command.
 */
char* extractArgsForHint(char* token, Command* command);

#endif /* PARCER_H_ */
