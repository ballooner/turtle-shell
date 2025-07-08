#include "Lexer.h"
#include "Utils.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

char* type_names[] =
{
		"STRING_LITERAL",
		"COMMAND_FLAG",
		"RDIR_OP"
};

int tokenize(const char* input, token_t* tokens[])
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
			rightIndex++;
			continue;
		} else if (leftIndex == rightIndex && input[rightIndex] == '"')
		{
			while (leftIndex != rightIndex && input[rightIndex] != '"')
			{
				rightIndex++;
			}

			token_t* newToken = createToken(STRING_LITERAL, substr(input, leftIndex, rightIndex));

			rightIndex++;
			leftIndex = rightIndex;
			tokens[currTokens] = newToken;
			currTokens++;
			continue;
		} else if (leftIndex < rightIndex && (isspace(input[rightIndex]) || input[rightIndex] == '\n'))
		{
			strcpy(currLiteral, substr(input, leftIndex, rightIndex - 1));
			token_t* newToken = createToken(getType(currLiteral), currLiteral);

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

token_t* createToken(enum TokenType type, const char value[])
{
	token_t* newToken = malloc(sizeof(token_t));
	if (!newToken)
	{
		fprintf(stderr, "[createToken] token malloc failed\n");
		exit(EXIT_FAILURE);
	}

	newToken->value = malloc((strlen(value) + 1) * sizeof(char));
	if (!(newToken->value))
	{
		fprintf(stderr, "[createToken] value malloc failed\n");
		free(newToken);
		exit(EXIT_FAILURE);
	}

	strcpy(newToken->value, value);

	newToken->type = type;

	return newToken;
}

void freeTokens(token_t* token[], int numTokens)
{
	for (int i = 0; i < numTokens; i++)
	{
		free(token[i]->value);
		free(token[i]);
	}
}

enum TokenType getType(const char* input)
{
	if (input[0] == '-')
	{
		return COMMAND_FLAG;
	}

	if (strcmp(input, ">") == 0 || strcmp(input, ">>") == 0 ||
		strcmp(input, "<") == 0)
	{
		return RDIR_OP;
	}

	return STRING_LITERAL;
}
