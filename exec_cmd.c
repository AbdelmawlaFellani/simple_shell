#include "main.h"

int builtin_command(shell *sh)
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
void external_command(shell *sh, int *curr_line)
{
	pid_t pid;
	int ret, wstatus;
	char *full_path = NULL;

	/* Check if the command is an absolute or relative path */
	if (sh->args[0][0] == '/' || sh->args[0][0] == '.')
		full_path = sh->args[0];
	/* OR find the full path of the command */
	else
		full_path = find_command(sh->args[0]);

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
			/* Get the exit status of the child */
			if (WIFEXITED(wstatus))
				sh->status = WEXITSTATUS(wstatus);
		}
		if (full_path != sh->args[0])
			free(full_path);
	}
	else
	{
		if (sh->interactive)
			fprintf(STDERR_FILENO, "%s: command not found\n", sh->args[0]);
		else
			fprintf(STDERR_FILENO, "%s: %d: %s: not found\n",
					 SH_NAME, *curr_line, sh->args[0]);
		sh->status = 127;
	}
}
void process_command(shell *sh)
{
	int i, curr_line = 1;
	char *oprs = ";|&", *saveptr, *cmd;

	read_input(sh);
	if (!sh->input)
		return;

	for (i = 0; i < sh->cmd_count; i++)
	{
		cmd = _strtok_r(sh->input[i], oprs, &saveptr);
		while (cmd != NULL)
		{

			parse_command(sh, cmd);
		
			if (sh->args[0] && sh->args[0][0])
				execute_command(sh, &curr_line);

			if (saveptr[0] == '|' && sh->status == 0)
				break;
			
			if (saveptr[0] == '&' && sh->status != 0)
				break;

			cmd = _strtok_r(NULL, oprs, &saveptr);
		}
	}

	sh->cmd_count = 0;

	if (sh->input)
		free_double(&sh->input);
}
