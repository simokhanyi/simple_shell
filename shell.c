#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_INPUT_LENGTH 100
#define MAX_PATH_LENGTH 256
#define MAX_ARGS 10

/**
 * my_exit - exit shell.
 *
 * Return: exits with a given exit status
 */

void my_exit(void)
{
	exit(0);
}

/**
 * my_env - function that prints current environment.
 * @environ: environment
 *
 * Return: exits with a given exit status
 */

void my_env(char **environ)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}

/**
 * execute_command - command execution.
 * @command: command input.
 * @environ: environment.
 *
 * Return: exits with a given exit status
 */

void execute_command(char *command, char **environ)
{
	pid_t pid = fork();

	char *arg_list[MAX_ARGS];

	arg_list[0] = command;
	arg_list[1] = NULL;
	if (pid < 0)
	{
		perror("Fork failed");
		exit(1);
	} else if (pid == 0)
	{
		if (execve(command, arg_list, environ) == -1)
		{
			perror("Execution error");
			exit(1);
		}
	} else
	{
		wait(NULL);
	}
}

/**
 * main - entry point.
 *
 *
 * Return: with 0 or NULL if failed.
 */

int main(void)
{
	char input[MAX_INPUT_LENGTH], command_path[MAX_PATH_LENGTH];
	char *path, *token, *argv[10];

	while (1)
	{
		printf("simple_shell~$ ");
		if (fgets(input, sizeof(input), stdin) == NULL)
		{	printf("\n");
			my_exit();
		}
		input[strcspn(input, "\n")] = '\0';
		if (strcmp(input, "exit") == 0)
		{	my_exit();
		}
		else if (strcmp(input, "env") == 0)
		{
			my_env(argv);
		} else
		{
			path = getenv("PATH");
			token = strtok(path, ":");
			while (token != NULL)
			{
				snprintf(command_path, sizeof(command_path), "%s/%s", token, input);
				if (access(command_path, X_OK) == 0)
				{	execute_command(command_path, argv);
					break;
				}
				token = strtok(NULL, ":");
			}
			if (token == NULL)
			{	printf("Command not found: %s\n", input);
			}
		}
	}
	return (0);
}
