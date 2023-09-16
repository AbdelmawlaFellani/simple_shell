#include "main.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

/**
 * read_command - Read a user command from standard input.
 *
 * @shell: A pointer to a Shell struct for storing the command.
 *
 * This function reads a user command from standard input and stores it in
 * the provided command buffer within the Shell struct.
 *
 * Return: The number of characters read, or -1 on failure.
 */
ssize_t read_command(Shell *shell)
{
	size_t cmd_len = 0;
	ssize_t nread;

	nread = getline(&shell->command, &cmd_len, stdin);
	if (nread == -1)
	{
		shell->run = 0;
		return (-1);
	}
	else if (nread > 1)
	{
		if (shell->command[nread - 1] == '\n')
		{
			shell->command[nread - 1] = '\0';
			shell->args = _splitstr(shell->command);
			if (shell->args == NULL)
			{
				perror("splitstr");
				return (-1);
			}
		}
	}
	return (nread);
}
/**
 * print_prompt - Display the shell prompt.
 *
 * @shell: A pointer to a Shell struct for storing the command.
 *
 * This function displays a shell prompt, typically "$ ", to indicate that
 * the shell is ready to accept a user command.
 */
void print_prompt(Shell *shell)
{
	if (shell->interactive)
		write(STDOUT_FILENO, "$ ", 2);
}
