#include "shell.h"

/*The developers: Dimakatso Chipape and Tebogo Lehong */
/**
 * check_executable_command - Checks if a file is an executable command.
 * @info: Pointer to the info structure.
 * @path: The path to the file.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int check_executable_command(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars_in_path - Duplicates characters from string constitute PATH.
 * @pathstr: The PATH string.
 * @start: The starting index of the characters to duplicate.
 * @stop: The stopping index of the characters to duplicate.
 *
 * Return: Pointer to the new buffer containing duplicated characters.
 */
char *duplicate_chars_in_path(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_command_in_pathstr - Finds full path of a command in the PATH string.
 * @info: Pointer to the info structure.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Return: Full path of the command if found, or NULL otherwise.
 */
char *find_command_in_pathstr(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (check_executable_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_chars_in_path(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (check_executable_command(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

