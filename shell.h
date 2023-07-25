#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUF_FLUSH (-2) /* Buffer Flush Constant */
#define WRITE_BUF_SIZE 1024 /* Buffer Size for Writing */
#define READ_BUF_SIZE 1024 /* Buffer Size for Reading */

/**
 * enum cmd_buf_type - Represents the type of command buffer
 * @CMD_NORM: Normal command
 * @CMD_OR: Command with "||" chain delimiter
 * @CMD_AND: Command with "&&" chain delimiter
 * @CMD_CHAIN: Command with ";" chain delimiter
 */
enum cmd_buf_type
{
	CMD_NORM,
	CMD_OR,
	CMD_AND,
	CMD_CHAIN
};

/**
 * struct list_s - singly linked list
 * @str: string (malloc'ed string)
 * @next: points to the next node
 */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

/**
 * struct info_s - Structure to hold shell information
 * @readfd: File descriptor for reading input
 * @argv: Array of arguments
 * @env: Environment variables
 * @alias: Aliases for command replacement
 * @status: Exit status of the last command
 * @cmd_buf_type: Type of command buffer (enum cmd_buf_type)
 */
typedef struct info_s
{
	int readfd;
	char **argv;
	list_t *env;
	list_t *alias;
	int status;
	enum cmd_buf_type cmd_buf_type;
} info_t;

#define INFO_INIT { 0, NULL, NULL, NULL, 0, CMD_NORM }

/* Prototypes for input processing functions */
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused)) int sig_num);

/* Prototypes for linked list functions */
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
void free_list(list_t **head_ptr);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);

/* Prototypes for memory functions */
void *_custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_custom_memset(char *s, char b, unsigned int n);
void _custom_ffree(char **str_array);

/* Prototypes for string functions */
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new);

/* Prototypes for utility functions */
int is_interactive(info_t *info);
int _custom_isalpha(int c);
int is_delimiter(char c, char *delim);
int _custom_atoi(char *s);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);

/* Additional Prototypes for Shell Operations */
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);

#endif /* SHELL_H */

