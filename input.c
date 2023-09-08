#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	ssize_t nread;

	nread =	getline(&shell->command, &(shell->command_size), stdin);
	if (nread == -1)
	{
		perror("read_command");
		return (-1);
	}
	else if (nread > 1)
	{
		if (shell->command[nread - 1] == '\n')
		{
			shell->command[nread - 1] = '\0';
		}
	}
	return (nread);
}

/**
 * print_prompt - Display the shell prompt.
 *
 * This function displays a shell prompt, typically "$ ", to indicate that
 * the shell is ready to accept a user command.
 */
void print_prompt(Shell *shell)
{
	if (shell.interactive)
		write(STDOUT_FILENO, "$ ", 2);
}
