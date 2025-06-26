#include "Lexer.h"
#include <string.h>
#include <ctype.h>

char* type_names[] =
{
		"STRING_LITERAL",
		"COMMAND_FLAG",
		"CTRL_OP",
		"RDIR_OP"
};

int tokenize(const char* input, token_t tokens[])
{
	int leftIndex = 0;
	int rightIndex = 0;
	int currTokens = 0;
	char currLiteral[256];

	while (rightIndex < (int)strlen(input))
	{
		// Skip any white space
		if (leftIndex == rightIndex && isspace(input[rightIndex]))
		{
			leftIndex++;
		} else if (leftIndex == rightIndex && input[rightIndex] == '"')
		{
			rightIndex++;
			while (input[rightIndex] != '"')
			{
				rightIndex++;
			}

			token_t newToken;
			newToken.type = STRING_LITERAL;
			strcpy(newToken.value, substr(input, leftIndex, rightIndex));
			rightIndex++;
			leftIndex = rightIndex;
			tokens[currTokens] = newToken;
			currTokens++;
		} else if (leftIndex < rightIndex && (isspace(input[rightIndex]) || input[rightIndex] == '\n'))
		{
			strcpy(currLiteral, substr(input, leftIndex, rightIndex - 1));
			token_t newToken;

			if (isControlOperator(currLiteral))
			{
				newToken.type = CTRL_OP;
			} else if (isRedirectionOperator(currLiteral))
			{
				newToken.type = RDIR_OP;
			} else if (isCommandFlag(currLiteral))
			{
				newToken.type = COMMAND_FLAG;
			} else // It is either a command or a parameter
			{	   // the parser can figure out which
				newToken.type = STRING_LITERAL;
			}
			strcpy(newToken.value, currLiteral);

			tokens[currTokens] = newToken;
			currTokens++;
			// Since we increment right every iteration we have to go forward to
			// right's next value or left will be one behind
			leftIndex = rightIndex + 1;
		}

		rightIndex++;
	}

	return currTokens;
}

// Return a char* from input that is [startIndex, endIndex]
char* substr(const char* input, int startIndex, int endIndex)
{
	char str[1024];
	int currChar = 0;
	while (input[startIndex] != '\0'
			&& startIndex <= endIndex && currChar < 1023)
	{
		str[currChar] = input[startIndex];

		startIndex++;
		currChar++;
	}

	str[currChar] = '\0';
	char* returnStr = str;

	return returnStr;
}

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

bool isRedirectionOperator(const char* input)
{
	if (strcmp(input, ">") == 0 || strcmp(input, ">>") == 0 ||
		strcmp(input, "<") == 0)
	{
		return true;
	}

	return false;

}

bool isCommandFlag(const char* input)
{
	if (input[0] == '-')
		return true;

	return false;
}
