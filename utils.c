#include "main.h"

/**
 * free_double - Frees a double pointer
 * @ptr: The double pointer to be freed
 */
void free_string_array(char ***ptr)
{
	int i;

	for (i = 0; (*ptr)[i]; i++)
		free((*ptr)[i]);
	free(*ptr);
	*ptr = NULL;
}
