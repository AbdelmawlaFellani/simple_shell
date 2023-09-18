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
