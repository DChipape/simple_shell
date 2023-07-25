#include "shell.h"

/**
 * free_and_null - release a memory pointed by the pointer
 * and sets the address to NULL
 * @ptr: the pointer address to free
 *
 * Return: 1 if the memory was freed, 0 if not
 */

int free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

