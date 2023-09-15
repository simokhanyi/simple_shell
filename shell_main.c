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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100
#define MAX_PATH_LENGTH 100

/**
 * run_command - call for command.
 * @command: command input.
 *
 * Return: path copy or 1 if failed.
 */
void run_command(char *command)
{
	char full_path[MAX_PATH_LENGTH], *path, *path_copy, *path_token;
	int status;

	path = getenv("PATH");
	path_copy = strdup(path);
	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		snprintf(full_path, MAX_PATH_LENGTH, "%s/%s", path_token, command);

		if (access(full_path, X_OK) == 0)
		{
			if (fork() == 0)
			{
				execl(full_path, command, NULL);
				perror("execl");
				exit(1);
			} else
			{
				wait(&status);
				break;
			}
		}
		path_token = strtok(NULL, ":");
	}
	free(path_copy);
}

/**
 * main - entry point.
 *
 *
 * Return: 0 on success, 1 on error.
 */

int main(void)
{
	char input[MAX_INPUT_LENGTH], *envp;
	int i;

	envp[] = {NULL};
	for (i = 0; environ[i] != NULL; i++)
	{
		envp[i] = strdup(environ[i]);
	}

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
		if (strcmp(input, "exit") == 0)
		{
			printf("Exiting the shell...\n");
			exit(0);
		} else if (strcmp(input, "env") == 0)
		{
			for (i = 0; envp[i] != NULL; i++)
			{
				printf("%s\n", envp[i]);
			}
		} else
		{
			run_command(input, envp);
		}
	}
	for (i = 0; envp[i] != NULL; i++)
	{
		free(envp[i]);
	}
	return (0);
}
