#include "main.h"

/**
 * init_shell - Initialize the shell struct
 * @sh: A pointer to the Shell struct to be initialized
 * @argc: argument counter.
 * @argv: An array of command arguments.
 * Return: void
 */
void init_shell(shell *sh, int argc, char **argv)
{
	command *builtins = get_builtins();

	sh->builtins = builtins;
	sh->run = 1;
	sh->argc = argc;
	sh->argv = argv;

	while (builtins[sh->num_builtins].name)
		sh->num_builtins++;

	sh->interactive = isatty(STDIN_FILENO) && argc == 1;
}

/**
 * run_shell - Run the main shell loop
 * @sh: A pointer to the Shell struct representing the shell.
 * Return: void
 */
void run_shell(shell *sh)
{
	while (sh->run)
	{
		if (sh->interactive)
		{
			write(STDOUT_FILENO, "$ ", 2);
		}
		process_cmd(sh);
	}
}

/**
 * free_shell - Free memory associated with a Shell struct.
 * @sh: A pointer to the Shell struct to be freed.
 * Return: void
 */
void free_shell(shell *sh)
{

	if (sh->input)
		free_2d(&sh->input);

	if (sh->args)
		free(sh->args);

	if (sh->env_cpy)
		free_2d(&sh->env_cpy);
}

/**
 * main - Entry point
 * @argc: The number of arguments passed to the program
 * @argv: An array[string] of the arguments passed to the program
 * Return: The status code of the last command executed
 */
int main(int argc, char **argv)
{
	shell sh = {0};

	init_shell(&sh, argc, argv);

	run_shell(&sh);

	free_shell(&sh);

	return (sh.status);
}
