#include "shell.h"

/*The developers: Dimakatso Chipape and Tebogo Lehong */
/**
 * count_linked_list - Determines the length of a linked list.
 * @h: Pointer to the first node of the linked list.
 *
 * Return: Size of the linked list.
 */
size_t count_linked_list(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * linked_list_to_string_array - Return array of strings from list->str values.
 * @head: Pointer to the first node of the linked list.
 *
 * Return: Array of strings.
 */
char **linked_list_to_string_array(list_t *head)
{
	list_t *node = head;
	size_t count = count_linked_list(head), i;
	char **str_array;
	char *str;

	if (!head || !count)
		return (NULL);
	str_array = malloc(sizeof(char *) * (count + 1));
	if (!str_array)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (size_t j = 0; j < i; j++)
				free(str_array[j]);
			free(str_array);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		str_array[i] = str;
	}
	str_array[i] = NULL;
	return (str_array);
}


/**
 * print_linked_list - Prints all elements of a list_t linked list.
 * @h: Pointer to the first node of the linked list.
 *
 * Return: Size of the linked list.
 */
size_t print_linked_list(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * find_node_starts_with - Returns the node whose string starts with a prefix.
 * @node: Pointer to the head of the linked list.
 * @prefix: The prefix to compare.
 * @c: The upcoming character after the prefix to match.
 *
 * Return: Matched node or NULL if not found.
 */
list_t *find_node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * find_node_index - Gets the index of a node in a linked list.
 * @head: Pointer to the head of the linked list.
 * @node: Pointer to the node whose index is to be found.
 *
 * Return: Index of the node or -1 if the node is not found.
 */
ssize_t find_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}

