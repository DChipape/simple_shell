#include "shell.h"

/**
 * custom_strcpy - Copies a string from the source to a destination
 * @dest: a destination buffer to be copied to
 * @src: a source string to copy
 *
 * Return: Pointer that points to a destination buffer
 */

char *custom_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * custom_strdup - Duplicates the string
 * @str: a string to be duplicated
 *
 * Return: Pointer that points to the duplicated string or NULL on failure
 */

char *custom_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * custom_puts - Prints a string to the stdout
 * @str: an input string to print
 *
 * Return: Nothing
 */

void custom_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * custom_putchar - note the character c to stdout
 * @c: a character to print
 *
 * Return: On success, 1. On error, -1 is returned,
 * and errno is set accordingly
 */

int custom_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
