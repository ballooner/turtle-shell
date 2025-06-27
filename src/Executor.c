#include "Executor.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

static int basicExec(const char* command);
static int argExec(const char* command, const char* args[]);

int turtleExec(const token_t input[], size_t num_tokens)
{
	int returnCode = 0;

	if (num_tokens == 1)
	{
		returnCode = basicExec(input[0].value);
	}

	return returnCode;
}

static int basicExec(const char* command)
{
	int returnCode;
	pid_t child = fork();

	if (child == 0)
	{
		child = execlp(command, command, (char*) NULL);

		if (child == -1)
		{
			printf("Command not found\n");
		}
	} else
	{
		waitpid(child, &returnCode, 0);

		if (WIFEXITED(returnCode) != 0)
		{
			return WEXITSTATUS(returnCode);
		}
	}

	return -1;
}


