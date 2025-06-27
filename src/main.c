#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "Lexer.h"
#include "Executor.h"

#define BUFFER_SIZE 4095

void input_loop(void)
{
	char buffer[BUFFER_SIZE];

	while (1)
	{
		printf("turtle> ");
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
			exit(1);

		token_t tokens[BUFFER_SIZE];
		int numTokens = tokenize(buffer, tokens);

		if (buffer[0] == 'q')
		{
			exit(0);
		} else
		{
			turtleExec(tokens, numTokens);
		}
	}
}

int main(void)
{
	input_loop();

	return 0;
}
