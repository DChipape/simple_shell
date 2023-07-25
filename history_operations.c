#include "shell.h"

/*The developers: Dimakatso Chipape and Tebogo Lehong */
/**
 * get_history_file_path - Gets the path to the history file.
 * @info: The parameter struct containing shell information.
 *
 * Return: Allocated string carrying the history file path.
 */
char *get_history_file_path(info_t *info)
{
	char *buf, *home_dir;

	home_dir = _getenv(info, "HOME=");
	if (!home_dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	_strcpy(buf, home_dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history_to_file - Writes the shell's history to a file.
 * @info: The parameter struct containing shell information.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history_to_file(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file_path(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history_from_file - Reads the shell's history from a file.
 * @info: The parameter struct containing shell information.
 *
 * Return: Number of lines read from history file, 0 on failure.
 */
int read_history_from_file(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file_path(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = '\0';
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * add_history_entry - Adds an entry to the shell's history linked list.
 * @info: The parameter struct containing shell information.
 * @buf: The buffer containing the history entry to add.
 * @linecount: The history line count.
 *
 * Return: Always 0.
 */
int add_history_entry(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history_entries - Renumbers the history linked list after changes.
 * @info: The parameter struct containing shell information.
 *
 * Return: The new histcount.
 */
int renumber_history_entries(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

