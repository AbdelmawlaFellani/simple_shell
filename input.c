#include "main.h"

/**
 * process_variables - Processes variables in the shell
 * @sh: Pointer to the shell structure
 * @args: Array of arguments
 */
void process_variables(Shell *shell, char **args)
{
	int i;
	char *arg_value;
	char status_str[12], pid_str[12];

	for (i = 0; args[i]; i++)
	{
		if (args[i][0] != '$')
			continue;

		if (_strcmp(args[i], "$?", -1) == 0)
		{
			snprintf(status_str, sizeof(status_str), "%d", shell->status);
			args[i] = strdup(status_str);
		}
		else if (_strcmp(args[i], "$$", 2) == 0)
		{
			snprintf(pid_str, sizeof(pid_str), "%d", getpid());
			args[i] = strdup(pid_str); 
		}
		else if (args[i][1] == '\0' || args[i][1] == ' ')
		{
			args[i] = strdup("$"); 
		}
		else
		{
			arg_value = __getenv(args[i] + 1);
			if (arg_value)
				args[i] = strdup(arg_value); 
			args[i] = strdup(""); 
		}
	}
}
/**
 * parse_command - Parses a command string into an array of arguments
 * @sh: Pointer to the shell structure
 * @cmd: The command string to be parsed
 * Return: Pointer to the array of arguments, or NULL if command is empty
 */
void parse_command(Shell *shell, char *cmd)
{
	int i = 0;
	char **args = malloc(MAX_ARGS * sizeof(char *));
	char *arg;

	if (!args)
	{
		perror("Error: memory allocation failed");
		exit(EXIT_FAILURE);
	}

	if (!cmd || !*cmd)
	{
		shell->args = args;
		return;
	}

	arg = strtok(cmd, " \t\n\r");
	while (arg)
	{
		if (arg[0] == '#')
			break;

		if (arg[0] == '"' && arg[strlen(arg) - 1] == '"')
		{
			arg[strlen(arg) - 1] = '\0';
			arg++;
		}

		args[i] = arg;

		if (++i >= MAX_ARGS)
		{
			fprintf(stderr, "Error: too many arguments\n");
			exit(EXIT_FAILURE);
		}

		arg = strtok(NULL, " \t\n\r");
	}

	args[i] = NULL;
	shell->args = args;
	process_variables(shell, args);
}

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
size_t read_command(Shell *shell)
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

char *read_line(shell *sh, int fd)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = _getline(&line, &len, fd);

	if (nread == -1)
	{
		sh->run = 0;
		free(line);
		return (NULL);
	}

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
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
