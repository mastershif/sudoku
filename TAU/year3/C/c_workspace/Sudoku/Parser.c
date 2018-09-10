/*
 * Parser.c
 *
 *  Created on: 5 May 2018
 *      Author: Shif
 */
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include "Parser.h"

bool parserIsInt(const char* str) {
	if (*str == '-') // if the number is negative
		++str; // keep parsing
	if (!*str)
		return false;
	while (*str) // if some character is not a digit
		if (!isdigit(*str))
			return false;
		else ++str; // keep parsing
	return true;
}

char* extractArgsForSolveSave(char *token, Command *command) {
	if (NULL == token) {
		return MISSING_ARGS;
	}
	command->filename = token;
	// printf("the file name in the command is now :%s\n", command->filename);
	token = strtok(NULL, " \t\r\n");
	return token;
}

char* extractArgsForEdit(char *token, Command *command) {
    command->filename = token;
    token = strtok(NULL, " \t\r\n");
    return token;
}

char* extractArgsForSet(char* token, Command* command, int nm) {
	int arguments_count;
	for (arguments_count = 0; arguments_count < 3;
			arguments_count = arguments_count + 1) {
		if (NULL == token) {
			return MISSING_ARGS;
		}
		int argument = atoi(token);
		if (arguments_count == 0) {
			command->X = argument;
		}
		if (arguments_count == 1) {
			command->Y = argument;
		}
		if (arguments_count == 2) {
			if (strcmp(token, "0") != 0 && argument == 0) {
				// invalid argument
				printf("Error: value not in range 0-%d\n", nm);
				return MISSING_ARGS;
			}
			command->Z = argument;
		}
		token = strtok(NULL, " \t\r\n"); // move to the next token in the splitted string
	}
	return token;
}

char* extractArgsForMarkErrors(char* token, Command* command) {
	if (NULL == token) {
		return MISSING_ARGS;
	}
	if (strcmp(token, "1") == 0 || strcmp(token, "0") == 0) {
		command->X = atoi(token);
	} else {
		printf("Error: the value should be 0 or 1\n");
		return MISSING_ARGS;
	}
	token = strtok(NULL, " \t\r\n");
	return token;
}

char* extractArgsForHint(char* token, Command* command) {
	int arguments_count;
	for (arguments_count = 0; arguments_count < 2;
			arguments_count = arguments_count + 1) {
		if (NULL == token) {
			return MISSING_ARGS;
		}
		int argument = atoi(token);
		if (arguments_count == 0) {
			command->X = argument;
		}
		if (arguments_count == 1) {
			command->Y = argument;
		}
		token = strtok(NULL, " \t\r\n"); // move to the next token in the splitted string
	}
	return token;
}

Command parserParseLine(char* str, int nm) {
	char* stringCopy = (char*) malloc(strlen(str)+1); // first make a copy of the string
	strcpy(stringCopy, str);
	Command command;
	command.cmd = INVALID_LINE; // initiate the command to INVALID_LINE
	if (strcmp(str,"") == 0) {
		command.cmd = INVALID_LINE; // if the string is empty, it is invalid
		return command;
	}
	if(strlen(str) > MAX_LINE_LENGTH) {
		command.cmd = INVALID_LINE; // if the string is too long, it is invalid
		return command;
	}
	char* token = strtok(stringCopy, " \t\r\n"); // split the string according to the delimiters
	int cmd = parserWhichCommand(token);
	command.cmd = cmd;
	token = strtok(NULL, " \t\r\n"); // move to the next token in the splitted string
	if (cmd == SOLVE || cmd == SAVE) {
		token = extractArgsForSolveSave(token, &command);
	}
    if (cmd == EDIT) {
        token = extractArgsForEdit(token, &command);
    }
	if (cmd == SET) {
		token = extractArgsForSet(token, &command, nm);
	}
	if (cmd == MARK_ERRORS) {
		token = extractArgsForMarkErrors(token, &command);
	}
	if (cmd == HINT) {
		token = extractArgsForHint(token, &command);
	}
	if (NULL != token && strcmp(token, MISSING_ARGS) == 0) {
		command.cmd = INVALID_LINE; // missing argument
	}
	free(stringCopy);
	return command;
}

int parserWhichCommand(char* command) {
	if (strcmp(command, "solve") == 0) {
		return SOLVE;
	}
	if (strcmp(command, "edit") == 0) {
		return EDIT;
	}
	if (strcmp(command, "mark_errors") == 0) {
		return MARK_ERRORS;
	}
	if (strcmp(command, "print_board") == 0) {
		return PRINT_BOARD;
	}
	if (strcmp(command, "set") == 0) {
		return SET;
	}
	if (strcmp(command,"validate") == 0) {
		return VALIDATE;
	}
	if (strcmp(command,"generate") == 0) {
		return GENERATE;
	}
	if (strcmp(command,"undo") == 0) {
		return UNDO;
	}
	if (strcmp(command,"redo") == 0) {
		return REDO;
	}
	if (strcmp(command,"save") == 0) {
		return SAVE;
	}
	if (strcmp(command,"hint") == 0) {
		return HINT;
	}
	if (strcmp(command,"num_solutions") == 0) {
		return NUM_SOLUTIONS;
	}
	if (strcmp(command,"autofill") == 0) {
		return AUTOFILL;
	}
	if (strcmp(command,"reset") == 0) {
		return RESET;
	}
	if (strcmp(command,"exit") == 0) {
		return EXIT;
	}
	return INVALID_LINE;
}
