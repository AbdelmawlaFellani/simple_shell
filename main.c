#include "main.h"

/**
 * main - Entry point for the shell program
 * @argc: The number of arguments passed to the program
 * @argv: An array[string] of the arguments passed to the program
 * Return: The status code of the last command executed
 */
int main(int argc, char **argv)
{
	Shell hsh = {0};

	init_shell(&hsh, argc, argv);

	run_shell(&hsh);

	free_shell(&hsh);
	return (hsh.status);
}
/**
 * run_shell - Run the main shell loop
 * @shell: A pointer to the Shell struct representing the shell.]
 * Return: void
 */
void run_shell(Shell *sh)
{
	while (sh->run)
	{
		if (sh->interactive)
		{
			write(STDOUT_FILENO, "$ ", 2);
		}
		process_command(&sh);
	}
}
/**
 * init_shell - Initialize the shell struct
 * @argc: argument counter.
 * @argv: An array of command arguments.
 * @shell: A pointer to the Shell struct to be initialized
 * @env: An array of environment variables.
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
 * free_shell - Free memory associated with a Shell struct.
 * @shell: A pointer to the Shell struct to be freed.
 * Return: void
 */
void free_shell(shell *sh)
{
	int i;

	if (sh->input)
		free_double(&sh->input);

	if (sh->args)
		free(sh->args);

	if (sh->environ_copy)
		free_double(&sh->environ_copy);
	/*
	   for (i = 0; sh->aliases[i].name; i++)
	   {
	   if (sh->aliases[i].name)
	   free(sh->aliases[i].name);
	   if (sh->aliases[i].value)
	   free(sh->aliases[i].value);
	   }
	   */
}
