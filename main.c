#include "main.h"

/**
 * init_shell - Initialize the shell struct
 *
 * @argc: argument counter.
 * @argv: An array of command arguments.
 * @shell: A pointer to the Shell struct to be initialized
 * @env: An array of environment variables.
 *
 * Return: void
 */
void init_shell(Shell *shell, int argc, char **argv, char **env)
{
	shell->run = 1;
	shell->argc = argc;
	shell->argv = argv;
	shell->command = NULL;
	shell->command_size = 0;
	shell->status = 0;
	shell->input = NULL;
	shell->env_cpy = env;

	sh->interactive = isatty(STDIN_FILENO) && argc == 1;
}

/**
 * run_shell - Run the main shell loop
 *
 * @shell: A pointer to the Shell struct representing the shell.]
 * @argv: An array of command arguments.
 * @env: An array of environment variables.
 *
 * Return: void
 */
void run_shell(Shell *shell)
{
	ssize_t nread;
	pid_t pid;

	while (shell->run)
	{
		print_prompt(shell);;
		nread = read_command(shell);
		if (nread == -1)
			break;

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			continue;
		}
		else if (pid == 0)
		{
			shell->argv[0] = shell->command;
			execute_command(shell);
		}
		else
		{
			waitpid(pid, &(shell->status), 0);
		}
	}
}

/**
 * free_shell - Free memory associated with a Shell struct.
 *
 * @shell: A pointer to the Shell struct to be freed.
 */
void free_shell(Shell *shell)
{
	free(shell->command);
}
/**
 * main - entry point
 *
 * @argc: argument counter
 * @argv: argument vector
 * @env: environement
 *
 * Return: Always (0)
 */
int main(int argc, char *argv[], char **env)
{
	Shell sh;

	init_shell(&sh, argc, argv, env);

	run_shell(&sh);

	free_shell(&sh);

	return (sh.status);
}
