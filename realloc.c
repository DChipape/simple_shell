#include "shell.h"

/**
 **_memset - fills the memory with a byte
 *@s: a pointer that points to the loction of a memory
 *@b: a byte to fill up a memory with
 *@n: count of bytes to be filled
 *Return: A pointer to the area s of memory
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees the string array
 * @pp: the array of strings to free
 */

void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates the block of memory
 * @ptr: the pointer that points to the
 * previous malloc'ated block
 * @old_size: a size of bytes of a past block
 * @new_size: the size of byte of a new block
 *
 * Return: the pointer to a reallocated memory block
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
