#include "Parser.h"
#include <string.h>

token_t* parseCommand(char commandBuffer[])
{
	char* currToken;

	int i = 0;
	size_t bytes = 0;
	while (commandBuffer[i] != '\n')
	{
		if (commandBuffer[i] == ' ')
		{
			strncpy(currToken, commandBuffer, bytes);
			bytes = 0;
		}

		i++;
	}
}
