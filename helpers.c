#include "main.h"

#define INIT_CAPACITY 10
#define INCRE_CAPACITY 10
/**
 * _splitstr - Splits the string provided into an array of strings.
 *
 * @str: The string to be split.
 * @delim: The delimiter used for splitting the string.
 *
 * Return: An array of strings.
 */
char **_splitstr(char *str, char delim[])
{
	char *token, **arr_tokens = NULL;
	int token_count = 0, capacity = 0;

	token = strtok(str, delim);
	while (token != NULL)
	{
		if (token_count >= capacity)
		{
			capacity += INCRE_CAPACITY;
			arr_tokens = realloc(arr_tokens, capacity * sizeof(char *));
			if (arr_tokens == NULL)
			{
				printf("Memory allocation error.\n");
				exit(EXIT_FAILURE);
			}
		}
		arr_tokens[token_count] = malloc(sizeof(char) * (strlen(token) + 1));
		if (arr_tokens[token_count] == NULL)
		{
			printf("Memory Allocation error.\n");
			exit(EXIT_FAILURE);
		}
		strcpy(arr_tokens[token_count], token);
		token_count++;
		token = strtok(NULL, delim);
	}
	return (arr_tokens);
}
/**
 * _getenv - Gets the value of an environment variable.
 *
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getenv(const char *name)
{
	int idx = 0;
	char *key;

	while (environ[idx])
	{
		key = strtok(environ[idx], "=");
		if (strcmp(key, name) == 0)
			return (strtok(NULL, "="));
		idx++;
	}
	return (NULL);
}
/**
 * _cmdcheck - Checks if a command exists in the system's path.
 *
 * @command: The command to check.
 *
 * Return: void
 */
void _cmdcheck(char *command)
{
	if (access(command, F_OK) == 0)
		printf("%s: Found\n", command);
	else
		printf("%s: Not Found\n", command);
}
/**
 * _getcmd - Gets the full path of a command in the system's path.
 *
 * @cmd: The command to find.
 *
 * Return: The full path of the command if found, or NULL if not found.
 */
char *_getcmd(char *cmd)
{
	char *path = _getenv("PATH");
	char *token, *command;
	struct stat st;

	token = strtok(path, ":");
	while (token)
	{
		command =  malloc(strlen(token) + strlen(cmd) + 2);
		strcpy(command, token);
		strcat(command, "/");
		strcat(command, cmd);
		if (stat(command, &st) == 0)
			return (command);
		free(command);
		token = strtok(NULL, ":");
	}
	return (NULL);
}
