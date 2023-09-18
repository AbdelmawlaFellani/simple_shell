#include "main.h"
/**
 * _getenv - get the value of an env variable
 * @name: name of the env variable
 * Return: pointer to the value of the env variable, or NULL if not found
 */
char *_getenv(const char *name)
{
	size_t len, i;

	if (!name || !environ)
		return (NULL);

	len = _strlen((char *)name);

	for (i = 0; environ[i]; i++)
		/*check if string starts with the name of the env variable*/
		if (_strcmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (&environ[i][len + 1]);

	return (NULL);
}
