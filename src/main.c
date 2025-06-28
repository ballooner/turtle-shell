#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "Lexer.h"

#define BUFFER_SIZE 4095

void input_loop(void)
{
	char buffer[BUFFER_SIZE];

	while (1)
	{
		printf("turtle> ");
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
			exit(1);

		token_t* tokens[BUFFER_SIZE];
		int numTokens = tokenize(buffer, tokens);

		for (int i = 0; i < numTokens; i++)
		{
			printf("Index: %d, Type: %s, Value: %s\n", i, type_names[tokens[i]->type], tokens[i]->value);
		}

		// Free tokens
		freeTokens(tokens, numTokens);

		if (buffer[0] == 'q')
		{
			exit(0);
		}
	}
}

int main(void)
{
	input_loop();

	return 0;
}
