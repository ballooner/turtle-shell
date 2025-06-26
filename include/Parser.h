#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

typedef struct Command 
{
	char* name;
	char** flags;
	char** args;
	bool output_redir;
	bool input_redir;
} command_t;

#endif
