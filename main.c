#include "main.h"
#define MAX_COMMAND_LENGTH 100

/**
 * main - Entry Point
 *
 * Return: 0 (Success)
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH], *args[MAX_COMMAND_LENGTH];
	int status;
	pid_t pid;

	while (1)
	{
		printf("$ "), fflush(stdout);
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			if (!feof(stdin))
			{
				perror("fgets");
				continue;
			}
			else
				break;
		}
		command[strcspn(command, "\n")] = '\0';
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			continue;
		}
		else if (pid == 0)
		{
			args[0] = command;
			args[1] = NULL;
			if (execvp(args[0], args) == -1)
			{
				fprintf(stderr, "%s: command not found\n", command);
				exit(EXIT_FAILURE);
			}
		}
		else
			waitpid(pid, &status, 0);
	}
	return (0);
}
