#include "shell.h"
/**
 * _atoiS - prints digits of a string
 * @s: Holds the string
 * Return: returns the value of the integer
 */
int _atoiS(char *s)
{
	int i, sign, digit, logic;

	logic = 0;
	digit = 0;
	sign = 1;
	for (i = 0; s[i] != 0;)
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			digit *= 10;
			digit -= (s[i] - '0');
			logic = 1;
		}
		else if (logic == 1)
		{
			break;
		}
		i++;

	}
	digit *= -sign;
	return (digit);
}
/**
 * checkPATH - checks for the PATH
 * @arr: Holds the array on position 0z
 * @buf: Holds the struct for stat
 * Return: none
 */
void checkPATH(char **arr, struct stat *buf)
{
	int i;
	char *conpollo, **lemon, *pathonized, *testy;

	conpollo = _strdupS(arr[0]), free(arr[0]);
	pathonized = _getenv("PATH");
	if (pathonized != 0 && _strlenS(pathonized) != 0)
	{
		if (pathonized[0] == ':' &&
		stat(conpollo, buf) == 0 && buf->st_mode & S_IXUSR)
		{
			arr[0] = str_concatS("./", conpollo);
			free(pathonized), free(conpollo);
			return;
		}
		lemon = pathonizer(pathonized);
		free(pathonized);
		for (i = 0; lemon[i]; i++)
		{
			testy = str_concatS(lemon[i], "/");
			arr[0] = str_concatS(testy, conpollo);
			if (stat(arr[0], buf) == 0)
			{
				free(conpollo), free(testy), blackster(lemon);
				return;
			}
			free(arr[0]), free(testy), arr[0] = 0, testy = 0;
		}
		blackster(lemon), lemon = 0;
		arr[0] = _strdupS(conpollo), free(conpollo), free(testy);
	}
	else if (pathonized != 0)
	{
		arr[0] = _strdupS(conpollo);
		free(conpollo), free(pathonized);
	}
	else
	{
		arr[0] = _strdupS(conpollo);
		free(conpollo);
	}
}
/**
 * _getenv - Gets the dir of a environ thingie
 * @name: The name to search for
 * Return: the value of the thingie
 */
char *_getenv(const char *name)
{
	int i;
	char *copy, *val, *name_env, *sender;

	for (i = 0; environ[i]; i++)
	{
		copy = _strdupS(environ[i]);
		name_env = strtok(copy, "=");

		if (_strcmpS(name_env, (char *)name) == 0)
		{
			val = strtok(NULL, "=");
			sender = _strdupS(val);
			free(copy);
			return (sender);
		}
		free(copy);
	}
	return (NULL);
}
/**
 * pathonizer - Divides the string into separated paths
 * @buf: Holds the string
 * Return: array of strings
 */
char **pathonizer(char *buf)
{
	char *tmp1 = 0, *tmp2 = 0, *token = 0, **arr = 0;
	int i;

	tmp1 = _strdupS(buf);
	tmp2 = _strdupS(buf);
	for (i = 0, token = strtok(tmp1, ":"); token; i++)
		token = strtok(NULL, ":");
	free(tmp1);
	arr = malloc(sizeof(char *) * (i + 1));
	if (arr == 0)
		perror("pathonizer function couldn't allocate memory"), exit(2);
	for (i = 0, token = strtok(tmp2, ":"); token; i++)
		arr[i] = _strdupS(token), token = strtok(NULL, ":");
	arr[i] = NULL;
	free(tmp2);
	return (arr);
}
/**
 * valChecker - Checks if the buffer contains at least one valid value
 * @buffer: Holds the buffer
 * @getty: Tells if getline worked or not
 * Return: 0 if it does, 1 if it doesn't
 */
int valChecker(char *buffer, int getty)
{
	int i;

	if (getty != -1)
		for (i = 0; buffer[i]; i++)
			if (buffer[i] >= 33 && buffer[i] <= 126)
				return (0);
	return (1);
}
