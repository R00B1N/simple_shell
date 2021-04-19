#include "shell.h"
/**
 * command - Divides the string into commands
 * @buf: Holds the string
 * Return: array of strings
 */
char **command(char *buf)
{
	char *tmp1 = 0, *tmp2 = 0, *token = 0, **arr = 0;
	int i;

	tmp1 = _strdupS(buf);
	tmp2 = _strdupS(buf);
	for (i = 0, token = strtok(tmp1, " \n\t\v\f"); token; i++)
		token = strtok(NULL, " \n\t\v\f");
	free(tmp1);
	arr = malloc(sizeof(char *) * (i + 1));
	if (arr == 0)
		perror("command function couldn't allocate memory"), exit(1);
	for (i = 0, token = strtok(tmp2, " \n\t\v\f"); token; i++)
		arr[i] = _strdupS(token), token = strtok(NULL, " \n\t\v\f");
	arr[i] = NULL;
	free(tmp2);
	return (arr);
}
/**
 * writedol - Writes or not the prompt depending on if
 * input comes from an FD associated with terminal or not
 * Return: none
 */
void writedol(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}
/**
 * writeErr - Writes either error prompt depending on if
 * input comes from an FD associated with terminal or not
 * @name: Name of the program to print
 * @comm: Command given to print
 * @counter: Command counter
 * Return: none
 */
void writeErr(char *name, char *comm, int counter)
{
	char *number;

	number = intToStr(counter);
	write(STDERR_FILENO, name, _strlenS(name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, number, _strlenS(number));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, comm, _strlenS(comm));
	write(STDERR_FILENO, ": not found\n", 12);
	free(number);
}
/**
 * ctrlC - Handles SIGINT Ctrl+C
 * @signal: Recieves the signal
 * Return: none
 */
void ctrlC(int signal __attribute__((unused)))
{
	(void)signal;
	write(STDOUT_FILENO, "\n$ ", 3);
}
/**
 * main - Main
 * @ac: Argument count
 * @argv: arguments
 * Return: 0 if succeeds, something else if not
 */
int main(int ac __attribute__((unused)), char **argv)
{
	char *buffer = 0, **arr = 0, *neobuf = 0;
	unsigned long int len = 0, counter = 1;
	int getty = 1, found, chkVal = 2;
	unsigned int statusOut = 0;

	initializer();
	while (getty != -1)
	{
		writedol();
		signal(SIGINT, ctrlC);
		getty = getline(&buffer, &len, stdin);
		chkVal = valChecker(buffer, getty);
		chkVal = dotChecker(buffer, getty, chkVal, argv, counter, &statusOut);
		chkVal = slsChecker(buffer, getty, chkVal, argv, counter, &statusOut);
		neobuf = Commentator(getty, buffer);
		if (neobuf == 0)
			chkVal = 1;
		found =  customCmmExec(getty, neobuf, arr, chkVal, counter,
		argv, &statusOut);
		found = cdCustomCmmd(found, neobuf, arr, argv,
		&statusOut, counter);
		commandExec(getty, neobuf, arr, argv, found, counter, &statusOut);
		free(neobuf);
		neobuf = 0;
		buffer = 0;
		counter++;
	}
	WilliamWallace(environ);
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	return (statusOut);
}
