#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <Lexer.h>

#define BUFFER_SIZE 4095

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

void input_loop(void)
{
	char buffer[BUFFER_SIZE];

	while (1)
	{
		printf("turtle> ");
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
			exit(1);

		printf("isCtrlOperator: %d\n", isControlOperator(substr(buffer, 0, 0)));

		if (buffer[0] == 'q')
			exit(0);
	}
}

int main(void)
{
	input_loop();

	return 0;
}
