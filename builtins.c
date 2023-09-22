#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * own_cd - change directory builtin.
 * @args: arguments.
 *
 * Return: 0 if successful or NULL if failed.
 */

int own_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "cd: missing argument\n");
	} else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
		}
	}
	return (1);
}


/**
 * own_env - environment function.
 * @args: arguments.
 *
 * Return: 0 if successful or NULL if failed.
 */

int own_env(char **args)
{
	char **env = environ;

	UNUSED(args);

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}

/**
 * own_help - help builtin function.
 * @args: arguments.
 *
 * Return: 0 if successful or NULL if failed.
 */

int own_help(char **args)
{
	UNUSED(args);

	printf("Simple Shell Help\n");
	printf("Availsable commands:\n");
	printf("1. cd <directory>: Change the current directory.\n");
	printf("2. env: Display the environment variables.\n");
	printf("3. help: Display this help message.\n");
	printf("4. exit: Exit the shell.\n");

	return (1);
}

/**
 * own_exit - exit function.
 * @args: arguments.
 *
 * Return: 0 if successful or NULL if failed.
 */

int own_exit(char **args)
{
	int status;

	if (args[1] != NULL)
	{
		status = atoi(args[1]);
		exit(status);
	} else
	{
		exit(0);
	}
}
