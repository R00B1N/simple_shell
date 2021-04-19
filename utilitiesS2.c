#include "shell.h"
/**
 * WilliamWallace - Freedom for Scotland!
 * @liberty: FREEDOM!
 * Return: Only freedom
 */
void WilliamWallace(char **liberty)
{
	int i;

	for (i = 0; liberty[i]; i++)
		free(liberty[i]);
	free(liberty);
}
/**
 * Commentator - Terminates anything after a #
 * @getty: Checks if it should be executed or no
 * @buffer: Holds the buffer whose comments are to be termianted
 * Return: a pointer to the new, comment free, buffer-> neobufer
 */
char *Commentator(int getty, char *buffer)
{
	char *neobuf;
	int i, j;

	if (getty != -1 && buffer[0] != '#')
	{
		for (i = 0; buffer[i] != 0; i++)
		{
			if (buffer[i] == '#')
				if (buffer[i - 1] == ' ')
					break;
		}
		neobuf = malloc(sizeof(char) * (i + 1));
		if (neobuf == 0)
			exit(1);
		for (j = 0; j < i; j++)
			neobuf[j] = buffer[j];
		neobuf[j] = 0;
		free(buffer);
		return (neobuf);
	}
	free(buffer);
	return (0);
}
/**
 * intToStr - Integer to strings
 * @num: Holds the number
 * Return: pointer to a string
 */
char *intToStr(unsigned long int num)
{
	unsigned int i, k;
	unsigned long int num1;
	char *number;

	if (num <= 9)
	{
		number = malloc(sizeof(char) * 2);
		number[0] = num + '0';
		number[1] = 0;
		return (number);
	}
	num1 = num;
	for (i = 0; num1 != 0; i++)
		num1 /= 10;
	number = malloc((sizeof(char) * i) + 1);
	for (k = 0; num != 0; k++)
	{
		number[k] = (num % 10) + '0';
		num /= 10;
	}
	number[k] = 0;
	rev_string(number);
	return (number);
}
/**
 * rev_string - Reverses a string
 * @s: Holds such string
 * Return: none
 */
void rev_string(char *s)
{
	int a, b;
	char c = 0;

	for (a = 0; s[a] != 0; a++)
		;
	for (b = 0; b < a; b++)
	{
		c = s[a - 1];
		s[a - 1] = s[b];
		s[b] = c;
		a--;
	}
}
/**
 * writeErrPerm - Writes an error message when no permissions are granted
 * @name: Holds the name
 * @comm: Holds the command
 * @counter: Holds the command counter
 * Return: none
 */
void writeErrPerm(char *name, char *comm, int counter)
{
	char *number;

	number = intToStr(counter);
	write(STDERR_FILENO, name, _strlenS(name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, number, _strlenS(number));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, comm, _strlenS(comm));
	write(STDERR_FILENO, ": Permission denied\n", 21);
	free(number);
}
