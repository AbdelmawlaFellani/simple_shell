#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define CAPACITY 1024
int main()
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
		arr_tokens = malloc(sizeof(char *) * CAPACITY);
		token = strtok(buff, delim);
		while (token)
		{
			arr_tokens[i] = token;
			token = strtok(NULL, delim);
			i++;
		}
		arr_tokens[i] = NULL;
		pid = fork();
		if (pid == 0)
		{
			if (execve(arr_tokens[0], arr_tokens, NULL) == -1)
				perror("exceve");
		}
		else
			wait(&status);
		i = 0;
		free(arr_tokens);
	}
}
