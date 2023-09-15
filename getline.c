#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include "shell.h"

#define MAX_INPUT_LENGTH 100
#define BUFFER_SIZE 1024

/**
 * my_getline - getline function.
 * @line: Pointer to a buffer where the line will be stored.
 * @max_len: Maximum length of the line to read.
 * @fd: File descriptor to read from (usually STDIN).
 *
 * Return: Number of characters read, 0 on EOF, or -1 on error.
 */

ssize_t my_getline(char **line, size_t max_len, int fd)
{
	char current_char, *new_line;
	ssize_t read_result, chars_read, buffer_size, buffer_index;

	if (max_len == 0 || line == NULL)
	{
		return (-1);
	}
	chars_read = 0;
	buffer_size = BUFFER_SIZE;
	buffer_index = 0;
	*line = (char *)malloc(buffer_size);
	if (*line == NULL)
	{	return (-1);
	}

	while (1)
	{
		if ((ssize_t)chars_read >= (ssize_t)(max_len - 1))
		{
			break;
		}
		if (buffer_index == 0)
		{	read_result = read(fd, *line + chars_read, buffer_size);

			if (read_result <= 0)
			{
				if (chars_read == 0)
				{	free(*line);
					*line = NULL;
					return (0);
				}
			}
			buffer_index = read_result;
		}
		current_char = (*line)[chars_read + buffer_index - 1];
		if (current_char == '\n')
		{	(*line)[chars_read + buffer_index] = '\0';
			return (chars_read + buffer_index);
		}
		chars_read++;
		if (chars_read + buffer_index >= buffer_size)
		{	buffer_size *= 2;
			new_line = (char *)realloc(*line, buffer_size);
			if (new_line == NULL)
			{	free(*line);
				*line = NULL;
				return (-1);
			}
			*line = new_line;
		}
	}
	return (-1);
}

/**
 * my_line - entry point.
 *
 *
 * Return: 0 on success, 1 on error.
 */


int my_line(void)
{
	char *input = NULL;
	ssize_t read_result;

	while (1)
	{
		printf("simple_shell~$ ");
		fflush(stdout);

		read_result = my_getline(&input, MAX_INPUT_LENGTH, STDIN_FILENO);

		if (read_result == 0)
		{
			printf("\n");
			free(input);
			break;
		} else if (read_result > 0)
		{
			printf("You entered: %s\n", input);
		} else
		{
			perror("custom_getline");
			free(input);
			exit(1);
		}
	}
	return (0);
}
