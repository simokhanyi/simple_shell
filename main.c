#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "shell.h"

#define MAX_INPUT_LENGTH 100
#define MAX_PATH_LENGTH 256

/**
 * main - main entry
 *
 * Return: 0 if successfull or NULL if failed.
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
		{
			printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';

		if (access(input, X_OK) == 0)
		{
			if (fork() == 0)
			{
				execv(input, argv);
				perror("execve");
				exit(1);
			} else
			{
				wait(&status);
			}
		} else
		{
			printf("Command not found: %s\n", input);
		}
	}
	return (0);
}
