#include "shell.h"

/**
 * **strtow - splits the words from a string
 * @str: a string to inpul
 * @d: a delimeter of a string
 * Return: the pointer the string arrays, or NULL if failure
 */

char **strtow(char *str, char *d)
{
	int i, j, p, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		p = 0;
		while (!is_delim(str[i + p], d) && str[i + p])
			p++;
		s[j] = malloc((p + 1) * sizeof(char));
		if (!s[j])
		{
			for (p = 0; p < j; p++)
				free(s[p]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < p; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - splits the words from string
 * @str: a string to input
 * @d: a delimeter
 * Return: the pointer to the string of arrays, or NULL if failure
 */

char **strtow2(char *str, char d)
{
	int i, j, p, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		p = 0;
		while (str[i + p] != d && str[i + p] && str[i + p] != d)
			p++;
		s[j] = malloc((p + 1) * sizeof(char));
		if (!s[j])
		{
			for (p = 0; p < j; p++)
				free(s[p]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < p; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
