int prompt(char **argv, char **envp)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int status = 1;
	int execute_status = 0;

	while (status)
	{
		line = NULL;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (line != NULL)
				free(line);
			break;
		}
		if (line[0] == '\n')
		{
			free(line);
			continue;
		}
		if (_token(line, argv, envp, &execute_status) == 1)
			break;
	}
	return (execute_status);
}
int _token(char *line, char **argv, char **envp, int *ex)
{
	char **tokens;

	tokens = split(line);
	if (tokens == NULL)
	{
		free(line);
		return (0);
	}
	if (_strcmp(tokens[0], "exit") == 0)
	{
		free(line);
		free(tokens);
		return (1);
	}
	*ex = execute(tokens[0], tokens, argv, envp);
	free(line);
	free(tokens);
	if (*ex == -1)
		return (1);
	return (0);

}
