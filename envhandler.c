#include "shell.h"
/**
 * initializer - initializes own copy of environ
 * Return: none
 */
void initializer(void)
{
	int i;
	char **primer;

	for (i = 0; environ[i]; i++)
		;
	primer = malloc(sizeof(char *) * (i + 1));
	for (i = 0; environ[i]; i++)
		primer[i] = _strdupS(environ[i]);
	primer[i] = 0;
	environ = primer;
}
/**
 * _setenv - Sets a variable in a pirate way
 * @key: The variable to set
 * @value: The value to be set with
 * @overwrite: Whether overwrite or not such variable
 * Return: 0 on success, -1 on failure
 */
int _setenv(char *key, char *value, int overwrite)
{
	char *toFree, **toHold, *toUnite;
	int i;

	if (key == 0 || _strlenS(key) == 0 || value == 0)
	{
		write(STDERR_FILENO, "Name is invalid\n", 16);
		return (-1);
	}
	for (i = 0; key[i]; i++)
		if (key[i] == '=')
		{
			write(STDERR_FILENO, "Name is invalid\n", 16);
			return (-1);
		}
	toFree = _getenv(key);
	if (toFree == 0)
	{
		for (i = 0; environ[i]; i++)
			;
		toHold = malloc(sizeof(char *) * (i + 2));
		if (toHold == 0)
			exit(1);
		for (i = 0; environ[i]; i++)
			toHold[i] = _strdupS(environ[i]);
		toUnite = str_concatS(key, "="), toHold[i] = str_concatS(toUnite, value);
		toHold[i + 1] = 0, free(toUnite), blackster(environ);
		environ = toHold;
		return (0);
	}
	else if (toFree != 0 && overwrite == 1)
		for (i = 0; environ[i]; i++)
			if (_strcmpS(key, environ[i]) == 0)
			{
				free(environ[i]);
				toUnite = str_concatS(key, "="), environ[i] =  str_concatS(toUnite, value);
				free(toFree), free(toUnite);
				return (0);
			}
	free(toFree);
	return (0);
}
/**
 * _unsetenv - Unsets a variable
 * @key:Key to the value to be unset
 * Return: Zero on success, -1 on failure
 */
int _unsetenv(char *key)
{
	int i, j, unsettler = 0;
	char **toHold;

	if (key == 0 || _strlenS(key) == 0)
	{
		write(STDERR_FILENO, "Name is invalid\n", 16);
		return (-1);
	}
	for (i = 0; environ[i]; i++)
		if (_strcmpS(key, environ[i]) == 0)
			unsettler = 1;
	if (unsettler != 0)
	{
		for (i = 0; environ[i]; i++)
			;
		toHold = malloc(sizeof(char *) * i);
		if (toHold == 0)
			exit(1);
		for (i = 0, j = 0; environ[i]; i++)
			if (_strcmpS(key, environ[i]) != 0)
				toHold[j] = _strdupS(environ[i]), j++;
		toHold[j] = 0;
		blackster(environ);
		environ = toHold;
		return (0);
	}
	return (0);
}
/**
 * Auxenv - Saves space to call setenv
 * @arr: Holds the array of arguments
 * @statusOut: Holds the exit status
 * Return: none
 */
void Auxenv(char **arr, unsigned int *statusOut)
{
	int a;

	if (arr[1] == 0)
	{
		*statusOut = 2;
		write(STDERR_FILENO, "Name is invalid\n", 16);
		return;
	}
	a = _setenv(arr[1], arr[2], 1);
	if (a == 0)
	{
		*statusOut = 0;
	}
	else
	{
		*statusOut = 2;
	}
}
/**
 * Auxunenv - Saves space to call setenv
 * @arr: Holds the array of arguments
 * @statusOut: Holds the exit status
 * Return: none
 */
void Auxunenv(char **arr, unsigned int *statusOut)
{
	int a;

	if (arr[1] == 0)
	{
		*statusOut = 2;
		write(STDERR_FILENO, "Name is invalid\n", 16);
		return;
	}
	a = _unsetenv(arr[1]);
	if (a == 0)
	{
		*statusOut = 0;
	}
	else
	{
		*statusOut = 2;
	}
}
