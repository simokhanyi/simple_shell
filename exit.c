#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * exit_builtins - shell exit
 *
 * Return: 0 on success, 1 on error
 */

int exit_builtins(void)
{
	char input[MAX_INPUT_LENGTH];

	while (1)
	{
		printf("~$ ");
		fgets(input, MAX_INPUT_LENGTH, stdin);

		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0)
		{
			printf("Exiting SimpleShell...\n");
			break;
		}
	}
	return (0);
}
