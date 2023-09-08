#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/**
 * execute_command - Execute a user command.
 *
 * @shell: The Shell
 * @argv: An array of command arguments.
 * @env: An array of environment variables.
 *
 * This function takes a user command, an array of arguments, and an array of
 * environment variables. It attempts to execute the command using the execve
 * system call. If execution fails, an error message is printed.
 */
void execute_command(Shell *shell)
{
	if (execve(shell->command, shell->argv, shell->env_cpy) == -1)
	{
		perror("execve");
		fprintf(stderr, "%s: not found\n", shell->command);
		exit(EXIT_FAILURE);
	}
}
