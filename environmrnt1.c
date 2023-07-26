#include "shell.h"

/*The developers: Dimakatso Chipape and Tebogo Lehong */
/**
 * populate_env_list - Occupy the linked list with environment variables
 * @info: Structure that hold the potential arguments for
 * maintaining function prototype
 *
 * Return: Always 0
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}

/**
 * _myenv - Prints the present environment variables
 * @info: Structure that holds the potential arguments for
*	maintaining a prototype
 *
 * Return: Always 0
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - fetch the value of an environment variable
 * @info: Structure that holds the arguments for
 * maintaining a function prototype
 * @name: a name for the environment variable
 *
 * Return: the value or null if not
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _myunsetenv - Removes the environment variable
 * @info: Structure that holds the arguments for
* maintaining a function prototype
 *  Return: Always 0
 */

int _myunsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}

/**
 * _mysetenv - Initializes the new environment variable
 *		or modifies the existing one
 * @info: Structure holding the arguments for
 * maintaining a function prototype
 *
 *  Return: Always 0
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
