#include "main.h"

void process_variables(Shell *shell, char **args)
{
    int i = 0;
    char *arg_value;
    char status_str[12], pid_str[12];

    for (; args[i]; i++)
    {
        if (args[i][0] != '$')
            continue;

        if (strcmp(args[i], "$?", -1) == 0)
        {
            snprintf(status_str, sizeof(status_str), "%d", shell->status);
            args[i] = strdup(status_str);
        }
        else if (strcmp(args[i], "$$", 2) == 0)
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
            arg_value = _getenv(args[i] + 1);
            if (arg_value)
                args[i] = strdup(arg_value); 
            else
                args[i] = strdup("");
        }
    }
}

/**
 * read_line - reads a line from stdin
 * @fd: File descriptor to read from
 * @sh: Pointer to the shell structure
 * Return: pointer to the line read, or NULL if EOF is reached
 */
char *read_line(shell *sh, int fd)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, fd);

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

void read_input(shell *sh)
{
	char *cmd;
	size_t old_size, new_size;
	int fd = STDIN_FILENO;

	if (sh->argc > 1)
	{
		fd = open(sh->argv[1], O_RDONLY);
		if (fd == -1)
		{
			fprintf(STDERR_FILENO, "%s: 0: Can't open %s\n",
					 SH_NAME, sh->argv[1]);
			sh->status = 127;
			sh->run = 0;
			return;
		}
	}

	while ((cmd = read_line(sh, fd)))
	{
		old_size = sizeof(char *) * (sh->cmd_count + 1);
		new_size = sizeof(char *) * (sh->cmd_count + 2);
		
		sh->input = realloc(sh->input, old_size, new_size);
		sh->input[sh->cmd_count] = cmd;
		sh->input[sh->cmd_count + 1] = NULL;
		sh->cmd_count++;

		if (sh->interactive)
			break;
	}

	if (fd != STDIN_FILENO)
		close(fd);
}
/**
 * parse_command - Parses a command string into an array of arguments
 * @sh: Pointer to the shell structure
 * @cmd: The command string to be parsed
 * Return: Pointer to the array of arguments, or NULL if command is empty
 */
void parse_command(Shell *sh, char *cmd)
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
		sh->args = args;
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
	sh->args = args;
	process_variables(sh, args);
}

