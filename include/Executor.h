#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stdio.h>
#include "Lexer.h"

typedef struct Command
{
	char* name;
	char** flags;
	char** args;
	int arg_count;
	char ctrl_op;
	char redir_op;
	FILE* input;
	FILE* output;
	int return_code;
} command_t;

extern command_t commandList[128];
extern size_t numCommands;

// Controls all command execution and redirects to correct static functions
void executeCommands(token_t* tokens[], int numTokens);
void clearCommandList();

#endif
