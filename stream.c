#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * read_stream - function to read stream.
 *
 *
 * Return: 0 if successful or NULL if failed.
 */

char *read_stream(void)
{
	char *line;
	int bufsize, i, character;

	bufsize = 1024;
	i = 0;
	line = malloc(sizeof(char) * bufsize);

	if (line == NULL)
	{	fprintf(stderr, "allocation error in read_stream");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		character = getchar();
		if (character == EOF)
		{	free(line);
			exit(EXIT_SUCCESS);
		}
		else if (character == '\n')
		{
			line[i] = '\0';
			return (line);
		}
		i++;
		if (i >= bufsize)
		{	bufsize += bufsize;
			line = (char *)realloc(line, bufsize);
			if (line == NULL)
			{	fprintf(stderr, "reallocation error in read_stream");
				exit(EXIT_FAILURE);
			}
		}
	}
}
