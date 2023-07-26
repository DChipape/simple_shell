#include "shell.h"

/**
 * interactive - tests if a simple shell is running in the interactive mode
 * @info: a pointer that points to the struct holding
 *
 * Return: 1 if the shell is in interactive mode, 0 if not
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 *_isalpha - Checks for the alphabetic character
 *@c: character to be checked
*
 *Return: 1 if the character is an alphabetic character, 0 if not
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_delim - checks for a delimeter character
 * @c: character to be checked
 * @delim: a string of delimiters to check against
*
 * Return: 1 for the delimiter of a character, 0 if not
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_atoi - Change a string to an integer
 *@s: a string to convert
*
 *Return: The converted integer for the numeric string, 0 if not
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

