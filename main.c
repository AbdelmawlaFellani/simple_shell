#include "main.h"
#define CAPACITY 1024
/**
 * main - Entry Point
 *
 * Return: 0 (Success)
 */
int main(void)
{
	char *buff = NULL, *token, **arr_tokens;
	size_t buff_size = 0;
	int nread, status, i = 0;
	pid_t pid;
	char delim[] = " \t\n";

	while (1)
	{
		write(1, "$ ", 2);
		nread = getline(&buff, &buff_size, stdin);
		if (nread == EOF)
		{
			perror("getline");
			break;
		}
		if (buff[0] == '\n')
			continue;
		arr_tokens = malloc(sizeof(char *) * (i + 1));
		if (arr_tokens == NULL)
			perror("malloc"), exit(EXIT_FAILURE);
		token = strtok(buff, delim);
		while (token)
		{
			arr_tokens[i] = token;
			token = strtok(NULL, delim);
			i++;
		}
		arr_tokens[i] = NULL, pid = fork();
		if (pid == 0)
		{
			if (execve(arr_tokens[0], arr_tokens, NULL) == -1)
				perror("execve"), exit(EXIT_FAILURE);
		}
		else
			wait(&status);
		i = 0;
		free(arr_tokens);
	}
	free(buff);
	return (0);
}
