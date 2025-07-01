#include "Executor.h"
#include <string.h>
#include <stdlib.h>

command_t commandList[128];
size_t numCommands = 0;

void initCommandList(token_t* tokens[], size_t numTokens)
{
	// Initialize values to their defaults
	command_t command = { 0 };
	size_t processedArgs = 0;

	for (int i = 0; i < (int)numTokens; i++)
	{
		// Handle string literals
		if (command.name == NULL 
			&& processedArgs == 0 
			&& tokens[i]->type == STRING_LITERAL)	
		{
			command.name = strdup(tokens[i]->value);
			command.argv[processedArgs++] = command.name;
			command.argc++;
		} else if (tokens[i]->type == STRING_LITERAL)
		{
			command.argv[processedArgs++] = strdup(tokens[i]->value);
			command.argc++;
		}

		// Handle command flags
		if (tokens[i]->type == COMMAND_FLAG)
		{
			command.argv[processedArgs++] = strdup(tokens[i]->value);
			command.argc++;
		}
	}

	commandList[numCommands++] = command;
}

void clearCommandList()
{
	for (int i = 0; i < (int)numCommands; i++)
	{
		command_t currCommand = commandList[i];
		// We don't have to free currCommand.name directly since argv[0] points to it
		for (int j = 0; j < (int)commandList[i].argc; j++)
		{
			free(currCommand.argv[j]);
		}
	}

	numCommands = 0;
}
