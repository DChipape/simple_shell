#include "shell.h"

/**
 * _custom_realloc - Reallocates a block of the memory
 * @ptr: the pointer that points to the
 * previous malloc'ated block
 * @old_size: a size of bytes of a past block
 * @new_size: s size of bytes of latest block
 *
 * Return: the pointer to a reallocated memory block
 */

void *_custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
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

/**
 * _custom_memset - Fills a memory to a byte
 * @s: a pointer that points to the loction of a memory
 * @b: a byte to fill up a memory with
 * @n: number of bytes to be filled
 *
 * Return: A pointer to the area s of memory
 */

char *_custom_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * _custom_ffree - Frees a string array
 * @str_array: the array of strings to free
 */

void _custom_ffree(char **str_array)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
