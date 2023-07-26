#include "shell.h"

/**
 * custom_strncpy - Copies a string from source to destination.
 * @dest: The destination string where the copy will be stored.
 * @src: The source string to be copied.
 * @n: The number of characters to be copied.
 *
 * Return: A pointer to the destination string.
 */
char *custom_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * custom_strncat - Concatenates two strings with a specified maximum length.
 * @dest: The first string to which the second string will be concatenated.
 * @src: The second string to be concatenated.
 * @n: The maximum number of bytes to be used for the concatenation.
 *
 * Return: A pointer to the concatenated string.
 */
char *custom_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * custom_strchr - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the first occurrence of the character in the string.
 *         If the character is not found, returns NULL.
 */
char *custom_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

