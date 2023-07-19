#include "shell.h"

/**
 * bfree - frees the pointer and address null
 * @ptr: a pointer address to be freed
 *
 * Return: 1 for freed, 0 otherwise
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
