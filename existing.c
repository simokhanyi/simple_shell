#include "shell.h"

/**
 * command_exists - check existing commands.
 * @command: input command.
 *
 * Return: 0 if successful or NULL if failed.
 */


int command_exists(const char *command)
{
	char *path_env, *path, *full_path;

	path_env = getenv("PATH");
	path = strtok(path_env, ":");

	while (path != NULL)
	{
		full_path = (char *)malloc(strlen(path) + strlen(command) + 2);
		if (full_path != NULL)
		{
			strcpy(full_path, path);
			strcat(full_path, "/");
			strcat(full_path, command);

			if (access(full_path, X_OK) == 0)
			{
				free(full_path);
				return (1);
			}
		free(full_path);
		}
	path = strtok(NULL, ":");
	}
	return (0);
}
