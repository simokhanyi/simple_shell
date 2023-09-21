#include "shell.h"

/**
 * own_setenv - check existing commands.
 * @args: arguments.
 *
 * Return: 0 if successful or NULL if failed.
 */

int own_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (-1);
	}
	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
		return (-1);
	}
	return (0);
}

/**
 * own_unsetenv - check existing commands.
 * @args: arguments.
 *
 * Return: 0 if successful or NULL if failed.
 */

int own_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (-1);
	}

	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
		return (-1);
	}
	return (0);
}
