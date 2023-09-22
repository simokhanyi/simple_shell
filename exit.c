#include "shell.h"

/**
 * own_exit - exit function.
 * @args: arguments.
 *
 * Return: 0 if successful or NULL if failed.
 */

int own_exit(char **args)
{
	UNUSED(args);
	exit(0);
	return (-1);
}
