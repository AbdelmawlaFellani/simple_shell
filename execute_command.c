#include "main.h"

/**
 * find_full_cmd_path - Find the full path to a command in the PATH environment
 *
 * @command: The command to search for.
 * @path_env: The PATH environment variable.
 *
 * Return: The full path to the command if found, or NULL if not found.
 */
char *find_full_cmd_path(const char *command, const char *path_env)
{
	char *token, *full_path;

	if (path_env == NULL)
		return (NULL);

	token = strtok((char *)path_env, ":");
	while (token != NULL)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}
		/*
		else if (access(full_path, X_OK) == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
				exit(127);
		} 
		*/
		free(full_path);
		token = strtok(NULL, ":");
	}

	return (NULL); 
}

/**
 * execute_command - Execute a user command.
 *
 * @shell: The Shell
 *
 * This function takes a user command, an array of arguments, and an array of
 * environment variables. It attempts to execute the command using the execve
 * system call. If execution fails, an error message is printed.
 */
void execute_command(Shell *shell)
{
	char *full_path;

	if (shell->args[0][0] == '/' || shell->args[0][0] == '.')
	{
		full_path = strdup(shell->args[0]);
	}
	else
	{
		full_path = find_full_cmd_path(shell->args[0], __getenv("PATH"));
		if (full_path == NULL)
		{
			free(full_path);
			exit(127);
		}
	}
	if (execve(full_path, shell->args, shell->env_cpy) == -1)
	{
		fprintf(stderr, "%s: %d: %s: %s", shell->argv[0], 1,
				shell->args[0], "not found\n");
		exit(127);
	}
}
