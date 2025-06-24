#include "Lexer.h"
#include <string.h>

bool isControlOperator(const char* input)
{
	
	if (strcmp(input, "|") == 0 || strcmp(input, "||") == 0 ||
	   	strcmp(input, "&") == 0 || strcmp(input, "&&") == 0 ||
		strcmp(input, ";") == 0)
	{
		return true;
	}


	return false;
}

bool isRedirectionOperator(const char* input);
bool isCommand(const char* input);
bool isCommandFlag(const char* input);
bool isParameter(const char* input);

