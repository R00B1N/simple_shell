#include "shell.h"
/**
 * dotChecker - Handles special dot cases
 * @buffer: Recieves the buffer
 * @getty: Checks if getline worked
 * @valChecker: CHecks if the given values are valid
 * @argv: Holds thr arguments passed to main
 * @counter: Holds the command line
 * @statusOut: Holds the exit status
 * Return: 0 on no dot cases, 1 on dot cases.
 */
int dotChecker(char *buffer, int getty, int valChecker,
char **argv, int counter, unsigned int *statusOut)
{
	char **arr;

	if (getty != -1 && valChecker == 0)
	{
		arr = command(buffer);
		if (arr[0][0] == '.')
		{
			if (arr[0][1] == '.' && arr[0][2] == 0)
			{
				writeErrPerm(argv[0], arr[0], counter);
				blackster(arr);
				*statusOut = 127;
				return (1);
			}
			else if (arr[0][1] == 0 && arr[1] == 0)
			{
				blackster(arr);
				*statusOut = 0;
				return (1);
			}
			else if (arr[0][1] == 0 && arr[1] != 0)
			{
				writeCompoundError(argv[0], arr[0], arr[1], counter);
				blackster(arr);
				*statusOut = 2;
				return (1);
			}
		}
		blackster(arr);
		return (0);
	}
	return (1);
}
/**
 * commandExec - Executes the command if it is found
 * @getty: Tells whether getline worked or nah
 * @buffer: Holds the string retrieved by getline
 * @arr: Holds the array to put in the commands
 * @argv: Holds the arguments passed to main (only using the name)
 * @found: boolean to see if enters or not in the function
 * @counter: Holds command count
 * @statusOut: Holds the status of exit
 * Return: none
 */
void commandExec(int getty, char *buffer, char **arr, char **argv,
int found, int counter, unsigned int *statusOut)
{
	pid_t piddy = 0;
	struct stat buf;
	char *dupHold;
	int status;

	if (getty != -1 && found == 0)
	{
		arr = command(buffer);
		echoinator(arr, statusOut);
		dupHold = _strdupS(arr[0]);
		if (dupHold[0] != '/')
			checkPATH(&dupHold, &buf);
		if (dupHold[0] == '/' || (dupHold[0] == '.' && dupHold[1] == '/')
		|| (dupHold[0] == '.' && dupHold[1] == '.' && dupHold[2] == '/'))
		{
			if (stat(dupHold, &buf) == 0 && buf.st_mode & S_IXUSR)
			{
				piddy = fork();
				if (piddy == 0)
					execve(dupHold, arr, environ);
				else
					wait(&status), *statusOut = WEXITSTATUS(status);
			}
			else if (stat(dupHold, &buf) == 0 && !(buf.st_mode & S_IXUSR))
				writeErrPerm(argv[0], arr[0], counter), *statusOut = 126;
			else
				writeErr(argv[0], arr[0], counter), *statusOut = 127;
		}
		else
			writeErr(argv[0], arr[0], counter), *statusOut = 127;
		blackster(arr);
		free(dupHold);
	}
}
/**
 * customCmmExec - Executes the command if it is found
 * @getty: Tells whether getline worked or nah
 * @buffer: Holds the string retrieved by getline
 * @arr: Holds the array to put in the commands
 * @chkVal: Holds boolean to dertemine if the code must be executed or not
 * @counter: Holds command counter
 * @argv: Holds arguments to main
 * @statusOut: Hold exit status
 * Return: 1 if a built in or 0 if not
 */
int customCmmExec(int getty, char *buffer, char **arr, int chkVal, int counter,
char **argv, unsigned int *statusOut)
{
	if (chkVal == 0)
	{
		if (getty != -1 && buffer[0] != '\n')
		{
			arr = command(buffer);
			if (_strcmpS(arr[0], "exit") == 0)
			{
				execExit(buffer, arr, counter, argv, statusOut), blackster(arr);
				return (1);
			}
			else if (_strcmpS(arr[0], "env") == 0)
			{
				execEnv(), blackster(arr), *statusOut = 0;
				return (1);
			}
			else if (_strchrS(arr[0], '=') != 0 && arr[0][0] != '=')
			{
				variableinator(arr, statusOut, counter, argv), blackster(arr);
				return (1);
			}
			else if (_strcmpS(arr[0], "setenv") == 0)
			{
				Auxenv(arr, statusOut), blackster(arr);
				return (1);
			}
			else if (_strcmpS(arr[0], "unsetenv") == 0)
			{
				Auxunenv(arr, statusOut), blackster(arr);
				return (1);
			}
			blackster(arr);
		}
		return (0);
	}
	return (1);
}
/**
 * execExit - Executes exit
 * @buffer: Holds the string
 * @arr: Holds the array of strings
 * @counter: Holds command counter
 * @argv: Holds the arguments to main
 * @statusOut: Holds the exit status
 * Return: none
 */
void execExit(char *buffer, char **arr, int counter, char **argv,
unsigned int *statusOut)
{
	int i, j, status;
	char *number;

	for (i = 0; arr[i]; i++)
		;
	if (i == 1)
	{
		free(buffer);
		blackster(arr);
		blackster(environ);
		exit(*statusOut);
	}
	else if (i > 1)
	{
		for (j = 0; arr[1][j]; j++)
		{
			if (arr[1][j] < 48 || arr[1][j] > 57)
			{
				number = intToStr(counter);
				write(STDERR_FILENO, argv[0], _strlenS(argv[0]));
				write(STDERR_FILENO, ": ", 2);
				write(STDERR_FILENO, number, _strlenS(number));
				write(STDERR_FILENO, ": ", 2);
				write(STDERR_FILENO, arr[0], _strlenS(arr[0]));
				write(STDERR_FILENO, ": Illegal number: ", 18);
				write(STDERR_FILENO, arr[1], _strlenS(arr[1]));
				write(STDERR_FILENO, "\n", 1);
				free(number);
				*statusOut = 2;
				return;
			}
		}
		status = _atoiS(arr[1]);
		free(buffer);
		blackster(arr);
		blackster(environ);
		exit(status);
	}
}
/**
 * execEnv - Executes env
 * Return: none
 */
void execEnv(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlenS(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}
