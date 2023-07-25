#include "shell.h"

/*The developers: Dimakatso Chipape and Tebogo Lehong */
/**
 * add_environment_vars - Occupy the linked list with environment variables
 * @info: Structure that hold the potential arguments
 * for maintaining function prototype
 *
 * Return: Always 0
 */

int add_environment_vars(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * display_environment - Prints the present environment variables
 * @info: Structure that holds the potential
 * arguments for maintaining the prototype
 *
 * Return: Always 0
 */

int display_environment(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_environment_var - fetch the value of an environment variable
 * @info: Structure that holds the arguments
 * for maintaining a function prototype
 * @name: a name for the environment variable
 *
 * Return: The value of the environment variable or NULL if not found
 */

char *get_environment_var(info_t *info, const char *name)
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
 * remove_environment_var - Removes the environment variable
 * @info: Structure that holds the arguments
 * for maintaining a function prototype
 *
 * Return: Always 0
 */

int remove_environment_var(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * set_environment_var - Initializes the new environment
 * variable or modifies the existing one
 * @info: Structure holding the arguments for maintaining a function prototype
 *
 * Return: Always 0
 */

int set_environment_var(info_t *info)
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
