#include "Executor.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

command_t commandList[128];
size_t numCommands = 0;

void executeCommands()
{
	command_t currCommand;
	for (int i = 0; i < (int)numCommands; i++)
	{
		currCommand = commandList[0];

		if (!currCommand.input && !currCommand.output)
	  	{
			basicExecute(currCommand);
		} else if (currCommand.redir_op)
		{
			redirExecute(currCommand);
		}
	}

	numCommands = 0;
}

void basicExecute(command_t command)
{
	int child = fork();

	if (child == -1)
	{
		fprintf(stderr, "basicExecute fork failed\n");
		exit(-1);
	}

	if (child == 0)
	{
		execvp(command.name, command.argv);
	} else
	{
		wait(NULL);
	}
}

void redirExecute(command_t command)
{
	int child = fork();

	if (child == -1)
	{
		fprintf(stderr, "redirExecute fork failed\n");
		exit(-1);
	}

	if (child == 0)
	{
		if (strcmp(command.redir_op->value, ">"))
		{
			freopen(command.output, "w", stdout);
			execvp(command.name, command.argv);
		} else if (strcmp(command.redir_op->value, ">>"))
		{
			freopen(command.output, "a", stdout);
			execvp(command.name, command.argv);
		} else
		{
			freopen(command.input, "r", stdin);
			execvp(command.name, command.argv);
		}
	} else
	{
		wait(NULL);
	}
}

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

		// Handle redirection operator
		if (tokens[i]->type == RDIR_OP && tokens[i + 1])
		{
			command.redir_op = tokens[i];
			if (strcmp(tokens[i]->value, ">") == 0 || strcmp(tokens[i]->value, ">>") == 0)
			{
				command.output = tokens[i + 1]->value;
			} else if (strcmp(tokens[i]->value, "<") == 0)
			{
				command.input = tokens[i + 1]->value;
			}
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
