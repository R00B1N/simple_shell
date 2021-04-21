#include "shell.h"
/**
 * cdCUstomCmmd - Executes cd command
 * @found: Looks for previously found commands
 * @buffer: Holds the buffer
 * @arr: Holds the array of arguments
 * @argv: Holds the arguments to main
 * @statusOut: Holds the exit status
 * @counter: Holds the line counter
 * Return: 0 or 1, if found or not (or previously found)
 */
int cdCustomCmmd(int found, char *buffer, char **arr,
char **argv, unsigned int *statusOut, int counter)
{
	if (found == 0)
	{
		arr = command(buffer);
		if (_strcmpS(arr[0], "cd") == 0)
		{
			execCd(arr, counter, argv, statusOut, 2), blackster(arr);
			return (1);
		}
		blackster(arr);
		return (0);
	}
	return (1);
}
/**
 * execCd - Executes the cd command
 * @arr: Holds the arguments
 * @counter: Holds the line counter
 * @argv: Holds the arguments to main
 * @statusOut: Holds the exit status
 * @chRet: Just holds a variable so betty won't bother
 * Return: none
 */
void execCd(char **arr, int counter, char **argv, unsigned int *statusOut,
int chRet)
{
	char *toFree, *toSet;

	if (arr[1] == 0)
	{
		toFree = _getenv("HOME");
		if (toFree == 0)
		{
			*statusOut = 0;
			return;
		}
		chRet = chdir(toFree);
		if (chRet == 0)
		{
			toSet = _getenv("PWD"), _setenv("OLDPWD", toSet, 1), free(toSet);
			_setenv("PWD", toFree, 1), *statusOut = 0;
		}
		else if (chRet == -1)
			writeCdError(arr, counter, argv), *statusOut = 2;
		free(toFree);
	}
	else if (arr[1] != 0 && arr[1][0] != '-')
	{
		chRet = chdir(arr[1]);
		if (chRet == 0)
		{
			toSet = _getenv("PWD"), _setenv("OLDPWD", toSet, 1), free(toSet);
			_setenv("PWD", arr[1], 1), *statusOut = 0;
		}
		else if (chRet == -1)
			writeCdError(arr, counter, argv), *statusOut = 2;
	}
	else if (arr[1] != 0 && arr[1][0] == '-' && arr[1][1] == 0)
	{
		execCdPrev(arr, counter, argv, statusOut);
	}
	else if (arr[1] != 0 && arr[1][0] == '-' && arr[1][1] != 0)
		writeOptErr(arr, counter, argv), *statusOut = 2;

}
/**
 * writeCdError - Writes the errors associated with cd
 * @arr: Holds the arguments
 * @counter: Holds the line counter
 * @argv: Holds the arguments to main
 * Return: none
 */
void writeCdError(char **arr, int counter, char **argv)
{
	char *number;

	number = intToStr(counter);
	write(STDERR_FILENO, argv[0], _strlenS(argv[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, number, _strlenS(number));
	write(STDERR_FILENO, ": cd: can't cd to ", 18);
	write(STDERR_FILENO, arr[1], _strlenS(arr[1]));
	write(STDERR_FILENO, "\n", 1);
	free(number);
}
/**
 * writeOptErr - Writes the errors associated with cd
 * @arr: Holds the arguments
 * @counter: Holds the line counter
 * @argv: Holds the arguments to main
 * Return: none
 */
void writeOptErr(char **arr, int counter, char **argv)
{
	char *number;

	number = intToStr(counter);
	write(STDERR_FILENO, argv[0], _strlenS(argv[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, number, _strlenS(number));
	write(STDERR_FILENO, ": cd: Illegal option ", 21);
	write(STDERR_FILENO, arr[1], 2);
	write(STDERR_FILENO, "\n", 1);
	free(number);
}
/**
 * execCdPrev - Changes directory
 * @arr: Holds the arguments
 * @counter: Holds the line counter
 * @argv: Holds the arguments to main
 * @statusOut: Holds the exit status
 * Return: none
 */
void execCdPrev(char **arr, int counter, char **argv, unsigned int *statusOut)
{
	char *toFree, *toSet;
	int chRet;

	toFree = _getenv("OLDPWD");
	if (toFree == 0)
		toFree = _getenv("PWD");
	chRet = chdir(toFree);
	if (chRet == 0)
	{
		write(1, toFree, _strlenS(toFree));
		write(1, "\n", 1);
		toSet = _getenv("PWD"), _setenv("OLDPWD", toSet, 1), free(toSet);
		_setenv("PWD", toFree, 1), *statusOut = 0;
	}
	else if (chRet == -1)
		writeCdError(arr, counter, argv), *statusOut = 2;
	free(toFree);
}
