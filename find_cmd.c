#include "main.h"

/**
 * find_cmd - Finds the full path of a command in the PATH environment
 * @command: The command to search for
 * Return: A pointer to the full path of the command, or NULL if not found
 */
char *find_cmd(char *command)
{
	char *path = NULL, *path_copy = NULL;
	char *dir = NULL, *full_path = NULL;

	path = _getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = _strdup(path);
	dir = strtok(path_copy, ":");
	full_path = malloc(_strlen(command) + _strlen(path) + 2);

	while (dir != NULL)
	{
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	free(full_path);

	return (NULL);
}
