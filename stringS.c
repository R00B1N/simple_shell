#include "shell.h"
/**
 * _strdupS - Returns a pointer to a newly allocated space in memory
 * @str: Holds the string to be copied
 * Return: a pointer to a char
 */
char *_strdupS(char *str)
{
	char *strc;
	int i;

	if (str == 0)
		return (0);
	for (i = 0; str[i] != 0; i++)
		;
	strc = malloc((sizeof(char) * 1) + i);
	if (strc == 0)
		return (0);
	for (i = 0; str[i] != 0; i++)
		strc[i] = str[i];
	strc[i] = 0;
	return (strc);
}
/**
 * str_concatS - Concatenates 2 strings
 * @s1: Holds string 1
 * @s2: Holds string 2
 * Return: a pointer to a char
 */
char *str_concatS(char *s1, char *s2)
{
	char *conc;
	int lens1, lens2, i;

	if (s1 == 0)
		s1 = "";
	if (s2 == 0)
		s2 = "";
	for (lens1 = 0; s1[lens1] != 0; lens1++)
		;
	for (lens2 = 0; s2[lens2] != 0; lens2++)
		;
	conc = malloc((sizeof(char) * (lens1 + lens2)) + 1);
	if (conc == 0)
		return (0);
	for (i = 0; i < lens1; i++)
		conc[i] = s1[i];
	lens1 = i;
	for (i = 0; i < lens2; i++, lens1++)
		conc[lens1] = s2[i];
	conc[lens1] = 0;
	return (conc);
}
/**
 * _strlenS - It returns the lenght of a string
 * @s: Holds the string
 * Return: none
 */
int _strlenS(char *s)
{
	int a;

	for (a = 0; s[a] != 0; a++)
		;
	return (a);
}
/**
 * _strcmpS - compares strings
 * @s1: String 1
 * @s2: String 2
 * Return: 0 if same, different if not
 */
int _strcmpS(char *s1, char *s2)
{
	int a;

	for (a = 0; s1[a] != 0; a++)
		if (s1[a] < s2[a] || s1[a] > s2[a])
			return (1);
	return (0);
}
/**
 * _strchrS - Finds a character in a string
 * @s: Holds the string
 * @c: Holds the test character
 * Return: Returns a char pointer
 */
char *_strchrS(char *s, char c)
{
	for (; *s != 0; s++)
	{
		if (*s == c)
			return (s);
		else if (*(s + 1) == c)
			return (s + 1);
	}
	return (0);
}
