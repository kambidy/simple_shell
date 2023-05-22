#ifndef _SHELL_H_
#define _SHELL_H_

#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_OR		1
#define CMD_CHAIN	3
#define CMD_AND		2
#define CMD_NORM	0
#define USE_STRTOK 0

#define CONVERT_LOWERCASE	1



#define USE_GETLINE 0
#define CONVERT_UNSIGNED	2
#define HIST_MAX	4096

#define HIST_FILE	".simple_shell_history"

extern char **environ;


/**
 * struct liststr - singly
 * @num: the
 * @str: string
 * @next: points node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to p
 * allowing uniform prototype for fun
 * @arg: a string generated from getline c
 * @argv:an array of string
 * @path: a string path for
 * @argc: the arg
 * @line_count: the
 * @err_num: the error code
 * @linecount_flag: if on count this
 * @fname: the progr
 * @env: linked list local copy
 * @environ: custom modified copy of environ
 * @history: the h
 * @alias: the
 * @env_changed: on if environ
 * @status: the return status of the last exe
 * @cmd_buf: address of pointer to cmd_buf, on
 * @cmd_buf_type: CMD_typ
 * @readfd: the fd from which to read
 * @histcount: the history line n
 */
typedef struct passinfo
{
	char **environ;
	int argc;
	unsigned int line_count;
	int err_num;
	char **cmd_buf;
	int cmd_buf_type;
	char *arg;
	char **argv;
	char *path;
	list_t *env;
	list_t *history;
	list_t *alias;
	int env_changed;
	int status;
	int linecount_flag;
	char *fname;

	;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a function
 * @type: the flag
 * @func: the func
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);




int loophsh(char **);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
void _eputs(char *);
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int _strlen(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);


char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);

void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_memset(char *, char, unsigned int);



int bfree(void **);


int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int _myhistory(info_t *);
int _myalias(info_t *);
int _erratoi(char *);


int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);






void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
char *_getenv(info_t *, const char *);


char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
list_t *add_node(list_t **, const char *, int);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);


int replace_string(char **, char *);

#endif

