#include "main.h"

/**
 * _getenv - Get the value of an environment variable.
 *
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getenv(const char *name)
{
	char **env;
	size_t name_len = strlen(name);

	if (name == NULL || environ == NULL)
		return (NULL);

	for (env = environ; env != NULL; env++)
	{
		if (strncmp(name, *env, name_len) == 0 && (*env)[name_len] == '=')
		{
			return (&(*env)[name_len + 1]);
		}
	}
	return (NULL);
}
