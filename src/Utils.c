#include "Utils.h"

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
