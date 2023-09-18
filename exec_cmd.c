#include "main.h"

/**
 * builtin_cmd - Executes a built-in cmd if it is found
 * @sh: Pointer to the shell structure
 * Return: Index of the built-in cmd that was executed, or 0 if none was found
 */
int builtin_cmd(shell *sh)
{
	int i;

	for (i = 0; i < sh->num_builtins; i++)
	{
		if (sh->args[0] && _strcmp(sh->args[0], sh->builtins[i].name, -1) == 0)
		{
			sh->builtins[i].func(sh);
			break;
		}
	}
	return (i);
}
/**
 * external_cmd - Self explain
 * @sh: Pointer to the shell structure
 * @curr_line: Pointer to the current line number
 */
void external_cmd(shell *sh, int *curr_line)
{
	pid_t pid;
	int ret, wstatus;
	char *full_path = NULL;

	if (sh->args[0][0] == '/' || sh->args[0][0] == '.')
		full_path = sh->args[0];
	else
		full_path = find_cmd(sh->args[0]);

	if (full_path)
	{
		pid = fork();
		if (pid == 0)
		{
			ret = execve(full_path, sh->args, environ);
			if (ret == -1)
				perror(sh->args[0]);
			_exit(ret);
		}
		else
		{
			wait(&wstatus);
			if (WIFEXITED(wstatus))
				sh->status = WEXITSTATUS(wstatus);
		}
		if (full_path != sh->args[0])
			free(full_path);
	}
	else
	{
		if (sh->interactive)
			fprintf(stderr, "%s: command not found\n", sh->args[0]);
		else
			fprintf(stderr, "%s: %d: %s: not found\n",
					SH_NAME, *curr_line, sh->args[0]);
		sh->status = 127;
	}
}
/**
 * execute_cmd - Executes a command
 * @sh: Pointer to the shell structure
 * @curr_line: Pointer to the current line number
 */
void execute_cmd(shell *sh, int *curr_line)
{
	int j;
	/* char *alias_value; */

	j = builtin_cmd(sh);
	if (j == sh->num_builtins)
	{
		/**
		 * alias_value = get_alias_value(sh, sh->args[0]);
		 * if (alias_value)
		 * sh->args[0] = alias_value;
		 */

		external_cmd(sh, curr_line);
	}
	(*curr_line)++;

	free(sh->args);
	sh->args = NULL;
}
/**
 * process_cmd - Reads input, parses it, and executes the cmd
 * @sh: Pointer to the shell structure
 * NOTE: '&&' still doesn't handle failed cmd
 */
void process_cmd(shell *sh)
{
	int i, curr_line = 1;
	char *oprs = ";|&", *saveptr, *cmd;

	read_input(sh);
	if (!sh->input)
		return;

	for (i = 0; i < sh->cmd_count; i++)
	{
		cmd = strtok_r(sh->input[i], oprs, &saveptr);
		while (cmd != NULL)
		{

			parse_cmd(sh, cmd);

			if (sh->args[0] && sh->args[0][0])
				execute_cmd(sh, &curr_line);

			if (saveptr[0] == '|' && sh->status == 0)
				break;

			if (saveptr[0] == '&' && sh->status != 0)
				break;

			cmd = strtok_r(NULL, oprs, &saveptr);
		}
	}

	sh->cmd_count = 0;

	if (sh->input)
		free_2d(&sh->input);
}
