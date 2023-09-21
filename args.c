#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * execute_args - function to read a line.
 * @args: arguments.
 *
 * Return: 0 if successful or NULL if failed.
 */

int execute_args(char **args)
{
	char *builtin_func_list[] = {
	"cd",
	"env",
	"help",
	"exit"
	};

	int (*builtin_func[])(char **) = {
	&own_cd,
	&own_env,
	&own_help,
	&own_exit
	};

	size_t i = 0;

	if (args[0] == NULL)
	{
		return (-1);
	}

	for (; i < sizeof(builtin_func_list) / sizeof(char *); i++)
	{
		if (strcmp(args[0], builtin_func_list[i]) == 0)
		{
			return ((*builtin_func[i])(args));
		}
	}
	return (new_process(args));
}
