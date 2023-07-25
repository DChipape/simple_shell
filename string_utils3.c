#include "shell.h"

/**
 * split_string_by_delimiters - splits the words from string.
 * @str: The input string to be split.
 * @delimiters: The delimiters used for splitting the string.
 *
 * Return: A pointer to the array of strings, or NULL on failure.
 */
char **split_string_by_delimiters(char *str, char *delimiters)
{
	int i, j, p, m, num_words = 0;
	char **result;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	if (!delimiters)
		delimiters = " ";

	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimiter(str[i], delimiters) &&
		    (is_delimiter(str[i + 1], delimiters) || !str[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);

	result = malloc((1 + num_words) * sizeof(char *));
	if (!result)
		return (NULL);

	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delimiter(str[i], delimiters))
			i++;

		p = 0;
		while (!is_delimiter(str[i + p], delimiters) && str[i + p])
			p++;

		result[j] = malloc((p + 1) * sizeof(char));
		if (!result[j])
		{
			for (p = 0; p < j; p++)
				free(result[p]);
			free(result);
			return (NULL);
		}

		for (m = 0; m < p; m++)
			result[j][m] = str[i++];

		result[j][m] = '\0';
	}

	result[j] = NULL;
	return (result);
}

/**
 * split_string_by_delimiter - splits the words from string.
 * @str: The input string to be split.
 * @delimiter: The delimiter used for splitting the string.
 *
 * Return: A pointer to the array of strings, or NULL on failure.
 */
char **split_string_by_delimiter(char *str, char delimiter)
{
	int i, j, p, m, num_words = 0;
	char **result;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delimiter && str[i + 1] == delimiter) ||
		    (str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
			num_words++;

	if (num_words == 0)
		return (NULL);

	result = malloc((1 + num_words) * sizeof(char *));
	if (!result)
		return (NULL);

	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == delimiter && str[i] != delimiter)
			i++;

		p = 0;
		while (str[i + p] != delimiter && str[i + p] && str[i + p] != delimiter)
			p++;

		result[j] = malloc((p + 1) * sizeof(char));
		if (!result[j])
		{
			for (p = 0; p < j; p++)
				free(result[p]);
			free(result);
			return (NULL);
		}

		for (m = 0; m < p; m++)
			result[j][m] = str[i++];

		result[j][m] = '\0';
	}

	result[j] = NULL;
	return (result);
}

