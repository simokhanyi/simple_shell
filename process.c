#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * new_process - function for a new process.
 * @args: arguments.
 *
 * Return: 0 if successful or NULL if failed.
 */


int new_process(char **args)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("error in new_process: child process");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0)
	{
		perror("error in new_process: forking");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (-1);
}
