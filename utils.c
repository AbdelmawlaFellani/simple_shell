#include "main.h"

/**
 * free_2d_array - Frees a double pointer
 * @ptr: The double pointer to be freed
 */
void free_2d_array(char **ptr)
{
	int i;

	if (!ptr)
		return;

	for (i = 0; ptr[i]; i++)
	{
		free(ptr[i]);
		ptr[i] = NULL;
	}
	free(*ptr);
	*ptr = NULL;
}
