#include "main.h"
/**
 * _strcmp - compares two strings
 * @s1: first string to compare
 * @s2: second string to compare
 * @n: index of characters to compare
 * Return: difference between the two strings
 */
int _strcmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);

	while (n && *s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}

	if (n == 0)
		return (0);

	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}
/**
 * _strlen - length of a given string
 * @s: the string
 * Return: the length of given string
 */
unsigned int _strlen(char *s)
{
	unsigned int len = 0;

	while (s[len])
		len++;

	return (len);
}
/**
 * _strdup - Duplicates a string
 * @s: The string to duplicate
 * Return: Pointer to the duplicated string, or NULL if fails
 */
char *_strdup(const char *s)
{
	int i;
	char *result;

	result = malloc(sizeof(char) * (_strlen((char *)s) + 1));
	if (result == NULL)
		return (NULL);

	for (i = 0; s[i]; i++)
		result[i] = s[i];

	result[i] = '\0';

	return (result);
}
/**
 * free_2d - Frees an array of strings
 * @ptr: The double pointer to be freed
 */
void free_2d(char ***ptr)
{
	int i;

	for (i = 0; (*ptr)[i]; i++)
		free((*ptr)[i]);
	free(*ptr);
	*ptr = NULL;
}
