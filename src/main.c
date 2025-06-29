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

		if (buffer[0] == 'q')
		{
			exit(0);
		}

		token_t* tokens[BUFFER_SIZE];
		size_t numTokens = tokenize(buffer, tokens);
		initCommandList(tokens, numTokens);

		printf("Command name: %s\n", commandList[0].name);
		printf("Command flags: %s\n", commandList[0].argv[1]);
		printf("Command args: %s\n", commandList[0].argv[2]);


		// Free tokens
		freeTokens(tokens, numTokens);
		clearCommandList();

	}
}

int main(void)
{
	input_loop();

	return 0;
}
