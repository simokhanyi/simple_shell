#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * split_line - function to read a line.
 * @line: read line.
 *
 * Return: 0 if successful or NULL if failed.
 */

char **split_line(char *line)
{
	int bufsize, i;
	char **tokens, *token;

	bufsize = 64;
	i = 0;
	tokens = malloc(bufsize * sizeof(char *));
	token = strtok(line, TOK_DELIM);

	if (!tokens)
	{
		fprintf(stderr, "allocation error in split_line: tokens\n");
		exit(EXIT_FAILURE);
	}
	while (token != NULL)
	{
		if (token[0] == '#')
		{
			break;
		}
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += bufsize;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "reallocation error in split_line: tokens");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[i] = NULL;
	return (tokens);
}
