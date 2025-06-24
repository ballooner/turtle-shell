#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

typedef enum token_type
{
	COMMAND,		// cd, ls, etc...
	COMMAND_FLAG,	// -r, -rf, etc...
	PARAMETER,		// self explanatory
	CTRL_OP,		// |, ||, &, &&, ;
	RDIR_OP			// <, >, >>
} token_type_t;

typedef struct token
{
	token_type_t type;
	char         value[];
} token_t;

bool isControlOperator(const char* input);
bool isRedirectionOperator(const char* input);
bool isCommand(const char* input);
bool isCommandFlag(const char* input);
bool isParameter(const char* input);

#endif
