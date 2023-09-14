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
#define MAX_PATH_LENGTH 100

/**
 * main - entry point.
 *
 *
 * Return: 0 on success, 1 on error.
 */

int main(void)
{
	char input[MAX_INPUT_LENGTH], *argv[2];
	int status;

	while (1)
	{
		printf("simple_shell~$ ");
		fflush(stdout);

		if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
		{	printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		if (strcmp(input, "exit") == 0)
		{	printf("Exiting the shell...\n");
			exit(0);
		}
		if (access(input, X_OK) == 0)
		{
			if (fork() == 0)
			{	execv(input, argv);
				perror("execve");
				exit(1);
			} else
			{	wait(&status);
			}
		} else
		{
			printf("Command not found: %s\n", input);
		}
	}
	return (0);
}
