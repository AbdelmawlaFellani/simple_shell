#include "main.h"

/**
 * get_builtins - Returns an array of builtin commands
 * Return: Pointer to the array of builtin commands
 */
command *get_builtins(void)
{
	static command builtins[] = {
		/**
		 * {"exit", cmd_exit},
		 * {"cd", cmd_cd},
		 * {"setenv", cmd_setenv},
		 * {"unsetenv", cmd_unsetenv},
		 * {"alias", cmd_alias},
		 */
		{"env", cmd_env},
		{NULL, NULL},
	};
	return (builtins);
}
/**
 * cmd_env - prints the current environment
 * @sh: Pointer to the shell structure
 */
static void cmd_env(shell *sh)
{
	unsigned int i;
	(void)(sh);
	size_t len;

	if (!environ)
	{
		fprintf(stderr, "env: environ is NULL\n");
		return;
	}
	for (i = 0; environ[i]; i++)
	{
		len = _strlen(environ[i]);
		write(STDOUT_FILENO, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}
	sh->status = 0;
}
