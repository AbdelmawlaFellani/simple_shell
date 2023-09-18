#include "main.h"

/**
 * get_builtins - Returns an array of builtin commands
 * Return: Pointer to the array of builtin commands
 */
command *get_builtins(void)
{
	static command builtins[] = {
		/**
		 * {"cd", cmd_cd},
		 * {"setenv", cmd_setenv},
		 * {"unsetenv", cmd_unsetenv},
		 * {"alias", cmd_alias},
		 */
		{"exit", cmd_exit},
		{"env", cmd_env},
		{NULL, NULL},
	};
	return (builtins);
}
/**
 * cmd_env - prints the current environment
 * @sh: Pointer to the shell structure
 */
void cmd_env(shell *sh)
{
	size_t len;
	unsigned int i;

	(void)(sh);
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

/**
 * cmd_exit - Exits the Shell
 * @sh: pointer to the shell structure
 */
void cmd_exit(shell *sh)
{
	if (sh->args[1])
	{
		if (!is_number(sh->args[1]) || sh->args[1][0] == '-')
		{
			fprintf(stderr, "%s: 1: exit: Illegal number: %s\n",
					 sh->argv[0], sh->args[1]);
			sh->status = 2;
			return;
		}

		if (sh->args[2])
		{
			fprintf(stderr, "exit: too many arguments\n");
			sh->status = 1;
			return;
		}

		if (is_number(sh->args[1]))
			sh->status = atoi(sh->args[1]);
	}
	sh->run = 0;
}
/**
 * is_number - Checks if a given string is a valid number
 * @str: The string to check
 * Return: 1 if the string is a number, otherwise 0
 */
int is_number(char *str)
{
	int i = 0;

	if (str[0] == '-' || str[0] == '+')
		i++;

	for (; str[i]; i++)
		if (str[i] >= '0' && str[i] <= '9')
			return (1);

	return (0);
}
