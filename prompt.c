#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define INIT_CAPACITY 10
#define INCRE_CAPACITY 10
/**
 * _splitstr - splits the string provided into array of strings
 *
 * @str: the string provided
 *
 * Return: array of strings
 */
char **_splitstr(char *str)
{
	char *token, **arr_tokens = NULL, delim[] = " \t\n";
	int token_count = 0, capacity = 0, i;

	token = strtok(str, delim);
	while (token != NULL)
	{
		if (token_count >= capacity)
		{
			capacity += INCRE_CAPACITY;
			arr_tokens = realloc(arr_tokens, capacity * sizeof(char *));
			if (arr_tokens == NULL)
			{
				printf("Memory allocation error.\n");
				exit(EXIT_FAILURE);
			}
		}
		arr_tokens[token_count] = malloc(sizeof(char) * (strlen(token) + 1));
		if (arr_tokens[token_count] == NULL)
		{
			printf("Memory Allocation error.\n");
			exit(EXIT_FAILURE);
		}
		strcpy(arr_tokens[token_count], token);
		token_count++;
		token = strtok(NULL, delim);
	}
	for (int i = 0; i < token_count; i++)
	{
		printf("Token %d: %s\n", i + 1, arr_tokens[i]);
	}
	for (int i = 0; i < token_count; i++)
	{
		free(arr_tokens[i]);
	}
	free(arr_tokens);
	return (arr_tokens);
}
/**
 * main - Reading a line and printing it
 *
 * @ac: argument counter
 * @av: argument vector
 *
 * Return: 0 (Success)
 */
int main(int ac, char **av)
{
	char *buffer = NULL, **tokens;
	size_t size_buffer = 0;
	size_t nread = 0;

	write(1, "$ ", 2);
	nread = getline(&buffer, &size_buffer, stdin);

	if (nread == -1)
		perror("getline");
	printf("%s", buffer);

	tokens = _splitstr(buffer);
	return (0);
}
