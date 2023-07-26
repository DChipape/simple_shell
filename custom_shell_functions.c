#include "shell.h"

/*The developers: Dimakatso Chipape and Tebogo Lehong */
/**
 * display_history - Displays the command history list with line numbers.
 * @info: Pointer to structure containing possible arguments and history list.
 * Return: Always 0
 */
int display_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * remove_alias - Removes an alias from the alias list.
 * @info: Pointer to a structure containing the alias list.
 * @str: The alias to be removed.
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias_value - Sets or updates an alias with the given string.
 * @info: Pointer to a structure containing the alias list.
 * @str: The string containing the alias name and value.
 * Return: Always 0 on success, 1 on error
 */
int set_alias_value(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (remove_alias(info, str));

	remove_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_single_alias - Prints the alias name and value from a node.
 * @node: Pointer to an alias node.
 * Return: Always 0 on success, 1 on error
 */
int print_single_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_builtin - Displays or sets aliases based on arguments provided.
 * @info: Pointer to a structure containing possible arguments and alias list.
 * Return: Always 0
 */
int alias_builtin(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_single_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias_value(info, info->argv[i]);
		else
			print_single_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

