#include "Executor.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int execBasic(const char* command)
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
