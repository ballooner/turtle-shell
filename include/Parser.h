#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

typedef enum token_type
{
	COMMAND,
	COMMAND_FLAG,
	PARAMETER,
	OPERATOR
} token_type_t;

typedef struct token
{
	token_type_t type;
	char         value[];
} token_t;

token_t getCommand(char* input);
token_t getCFlags(char* input);

#endif
