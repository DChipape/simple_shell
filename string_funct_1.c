#include "shell.h"

/*The developers: Dimakatso Chipape and Tebogo Lehong */
/**
 * string_length - Calculates the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */

int string_length(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;
	return (length);
}

/**
 * string_compare - Compares two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: negative s1 < s2, positive s1 > s2, zero s1 == s2
 */

int string_compare(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with_prefix - Checks if a string starts with a specific prefix.
 * @str: The input string to search in.
 * @prefix: The prefix to look for.
 *
 * Return: A pointer to the next character after the prefix in str, or NULL.
 */

char *starts_with_prefix(const char *str, const char *prefix)
{
	while (*prefix)
		if (*prefix++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * string_concatenate - Concatenates two strings.
 * @dest: The destination buffer for the concatenation.
 * @src: The source buffer to be concatenated.
 *
 * Return: A pointer to the destination buffer location.
 */

char *string_concatenate(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

