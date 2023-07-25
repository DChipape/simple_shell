#include "shell.h"

/*The developers: Dimakatso Chipape and Tebogo Lehong */
/**
 * main_loop - The main shell loop that reads and executes commands.
 * @info: Pointer to the info structure.
 * @av: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or an error code.
 */
int main_loop(info_t *info, char **av)
{
	ssize_t read_result = 0;
	int builtin_ret = 0;

	while (read_result != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (is_interactive(info))
			_puts("$ ");
		_flush_stderr();
		read_result = read_input(info);
		if (read_result != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin_command(info);
			if (builtin_ret == -1)
				find_external_command(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin_command - Finds and executes a built-in command.
 * @info: Pointer to the info structure.
 *
 * Return: -1 if the built-in command was not found,
 *         0 if the built-in command executed successfully,
 *         1 if the built-in command was found but not successful,
 *         -2 if the built-in command signals exit().
 */
int find_builtin_command(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", execute_exit},
		{"env", execute_env},
		{"help", execute_help},
		{"history", execute_history},
		{"setenv", execute_setenv},
		{"unsetenv", execute_unsetenv},
		{"cd", execute_cd},
		{"alias", execute_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].cmd; i++)
	{
		if (_strcmp(info->argv[0], builtintbl[i].cmd) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	}
	return (built_in_ret);
}

/**
 * find_external_command - Finds and executes an external command in the PATH.
 * @info: Pointer to the info structure.
 *
 * Return: void.
 */
void find_external_command(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
	{
		if (!is_delimiter(info->arg[i], " \t\n"))
			k++;
	}
	if (!k)
		return;

	path = find_command_in_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_and_execute_command(info);
	}
	else
	{
		if ((is_interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_executable_command(info, info->argv[0]))
		{
			fork_and_execute_command(info);
		}
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "Command not found\n");
		}
	}
}

/**
 * fork_and_execute_command - Forks a child process and executes a command.
 * @info: Pointer to the info structure.
 *
 * Return: void.
 */
void fork_and_execute_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
		/* TODO: HANDLE OTHER EXIT STATUS CODES */
	}
}

