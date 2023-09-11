#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_INPUT_SIZE 1024

/**
 * my_getline - shell getting a prompt command
 *
 *
 * Return: Line on success, NULL on error
 */

char *my_getline(void);
char input_buffer[MAX_INPUT_SIZE];

char *my_getline(void)
{
	static char buffer[MAX_INPUT_SIZE];
	static int buffer_pos;
	static int buffer_size;
	
	int line_size = 0;
	char *line = NULL, c = buffer[buffer_pos++], *new_line = realloc(line, line_size + 2);

	while (1)
	{
		if (buffer_pos == buffer_size)
		{
			buffer_size = read(STDIN_FILENO, buffer, MAX_INPUT_SIZE);
			if (buffer_size <= 0)
			{
				return (NULL);
			}
			buffer_pos = 0;
		}
		if (c == '\n' || c == '\0')
		{
			if (line_size > 0)
			{
				line = malloc(line_size + 1);
				strncpy(line, buffer + buffer_pos - line_size - 1, line_size);
				line[line_size] = '\0';
			}
			break;
		}
		if (line_size == 0)
		{
			line = malloc(1);
			line[0] = '\0';
		}
		if (new_line == NULL)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		line = new_line;
		line[line_size++] = c;
	}
	return (line);
}

/**
 * line - entry point
 *
 *
 * Return: 0 on success, 1 on error
 */

int line(void)
{
	char *input = my_getline(), *args[64], *token = strtok(input, " ");
	int arg_count = 0;

	my_getline();
	
	while (1)
	{
		printf("Shell 0.1 $ ");
		fflush(stdout);

		if (input == NULL)
		{
			break;
		}
		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;

		if (arg_count > 0)
		{
			pid_t child_pid = fork();

			if (child_pid == 0)
			{
				execvp(args[0], args);
				perror("execvp");
				exit(EXIT_FAILURE);
			} else if (child_pid > 0)
			{
				waitpid(child_pid, NULL, 0);
			} else
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
		}
		free(input);
	}
	return (0);
}
