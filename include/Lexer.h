#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

typedef enum token_type
{
	STRING_LITERAL, // Command or parameter
	COMMAND_FLAG,	// -r, -rf, etc...
	CTRL_OP,		// |, ||, &, &&, ;
	RDIR_OP			// <, >, >>
} token_type_t;

extern char* type_names[];

typedef struct token
{
	token_type_t type;
	char         value[256];
} token_t;

// Tokenize the given input and put all the tokens into
// the given token array
int tokenize(const char* input, token_t tokens[]);
// Return a char* from input that is [startIndex, endIndex]
char* substr(const char* input, int startIndex, int endIndex);
bool isControlOperator(const char* input);
bool isRedirectionOperator(const char* input);
bool isCommandFlag(const char* input);

#endif
