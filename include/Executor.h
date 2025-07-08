#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stdio.h>
#include "Lexer.h"

typedef struct Command
{
	char* name;
	token_t* redir_op;
	char* input;
	char* output;
	int return_code;
	size_t argc;
	char* argv[256];
} command_t;

extern command_t commandList[];
extern size_t numCommands;

// Controls all command execution and redirects to correct static functions
void executeCommands();
void basicExecute(command_t command);
void redirExecute(command_t command);
void ctrlExecute(command_t command);
void initCommandList(token_t* tokens[], size_t numTokens);
void clearCommandList();

#endif
