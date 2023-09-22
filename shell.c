#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * shell_interactive - function for prompt interaction.
 *
 * Return: 0 if successful or NULL if failed.
 */

void shell_interactive(void)
{
	int status;
	char *line, **args;

	status = -1;

	do {
		printf("simple_shell~$ ");
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
