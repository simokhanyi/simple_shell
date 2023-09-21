#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_PATH_LENGTH 256

/**
 * main - main entry
 *
 * Return: 0 if successfull or NULL if failed.
 */

int main(void)
{
	char input[MAX_COMMAND_LENGTH];
	int status, exit_status;
	pid_t pid = fork();

	while (1)
	{
		printf("simple_shell~$ ");
		fflush(stdout);

		if (fgets(input, sizeof(input), stdin) == NULL)
		{	printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		if (pid == -1)
		{	perror("fork");
			exit(EXIT_FAILURE);
		} else if (pid == 0)
		{
			if (execlp(input, input, NULL) == -1)
			{	perror("exec");
				exit(EXIT_FAILURE);
			}
		} else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
			{
				exit_status = WEXITSTATUS(status);
				if (exit_status != 0)
				{	fprintf(stderr, "Command '%s' status %d\n", input, exit_status);
				}
			} else if (WIFSIGNALED(status))
			{
				fprintf(stderr, "Command '%s' signal %d\n", input, WTERMSIG(status));
			}
		}
	}
	return (0);
}
