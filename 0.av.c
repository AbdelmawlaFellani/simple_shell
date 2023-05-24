#include <stdio.h>

/**
 * main - printing arguments
 *
 * @ac: argument counter
 * @av: argument vector
 *
 * Return: 0 (Success)
 */
int main(int ac, char **av)
{
	(void) ac;
	int i = 0;

	while (av[i])
	{
		printf("%s\n", av[i]);
		i++;
	}
	return (0);
}
