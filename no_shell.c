#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * shell_no_interactive - function for no interaction.
 *
 * Return: 0 if successful or NULL if failed.
 */

void shell_no_interactive(void)
{
	char *line, **args;
	int status;

	status = -1;

	do {
		line = read_line();
		args = split_line(line);
		status = execute_args(args);
		free(line);
		free(args);

		if (status >= 0)
		{
			exit(status);
		}
	} while (status == -1);
}
