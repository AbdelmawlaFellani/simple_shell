#include "main.h"
#define MAX_COMMAND_LENGTH 100

/**
 * main - Entry Point
 *
 * Return: 0 (Success)
 */
int main(void)
{
	char *command = NULL, *args[2];
	size_t command_size = 0;
	ssize_t nread;
	int status;
	pid_t pid;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		nread = getline(&command, &command_size, stdin);
		if (nread == -1)
		{
			perror("getline");
			break;
		}
		else if (nread == 1)
			continue;
		command[nread - 1] = '\0';
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}
		else if (pid == 0)
		{
			args[0] = command;
			args[1] = NULL;

			if (execve(command, args, NULL) == -1)
			{
				fprintf(stderr, "%s: command not found\n", command);
				exit(EXIT_FAILURE);
			}
		}
		else
			waitpid(pid, &status, 0);
	}
	free(command);
	return (0);
}
