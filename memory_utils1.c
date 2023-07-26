#include "shell.h"

/**
 * bfree - release a memory pointed by the pointer
 * and sets the address to NULL
 * @ptr: a pointer address to be freed
 *
 * Return: 1 for freed memory, 0 if not
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
