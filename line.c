#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * read_line - function to read a line.
 *
 * Return: 0 if successful or NULL if failed.
 */

char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(line);
			exit(EXIT_SUCCESS);
		} else
		{
			free(line);
			perror("error while reading the line from stdin");
			exit(EXIT_FAILURE);
		}
	}
	return (line);
}
