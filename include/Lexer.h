#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

enum TokenType
{
	STRING_LITERAL, // Command or parameter
	COMMAND_FLAG,	// -r, -rf, etc...
	RDIR_OP			// <, >, >>
};

extern char* type_names[];

typedef struct Token
{
	enum TokenType type;
	char*          value;
} token_t;

// Tokenize the given input and put all the tokens into
// the given token array
int tokenize(const char* input, token_t* tokens[]);
// Create a new token
token_t* createToken(enum TokenType type, const char* value);
// Free token
void freeTokens(token_t* token[], int numTokens);
enum TokenType getType(const char* input);

#endif
