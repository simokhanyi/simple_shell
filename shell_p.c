#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_INPUT_LENGTH 100
#define MAX_PATH_LENGTH 100

/**
 * display_prompt - shell greetings
 *
 * Return: 0 on success, 1 on error
 */

void dispaly_prompt(void);

void display_prompt(void)
{
	printf("simple_shell\n ");
	printf("   ------\n");
	printf("     ---\n");
}

/**
 * * main - entry point.
 *
 * Return: 0 on success, 1 on error.
 */

int main(void)
{
	char input[MAX_INPUT_LENGTH], *argv[2];
	int status;

	while (1)
	{
		printf("~$ ");
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
