#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <limits.h>
#include <signal.h>

/* STRUCTS */
/**
 * struct allocation_history - tracks and stores allocations
 * @mem_ptr: pointer to al
 * @next: pointer to n
 *
 * Description: stores a pointer to
 * greater organiza
 */
typedef struct allocation_history
{
	char *mem_ptr;
	struct allocation_history *next;

} mem_list;

/**
 * struct built_ins - catalogue
 * @cmd : does
 * @fp: pointer to
 */
typedef struct built_ins
{
	char *cmd;
	int (*fp)(char * const*);
} built_in;

extern mem_list *mem_head;
mem_list *mem_head;
extern mem_list *static_mem_head;
mem_list *static_mem_head;
extern char **environ;
extern size_t err_msg;
size_t err_msg;

char **_strtok(char *line);
ssize_t _getline(char **line);
char **get_path(char * const *argv);

int exec_mngr(char *const *argv);
int exec_builtin(char *const *argv);
int exec_external(char *const *argv);

char *alloc_mngr(char *ptr, size_t size);
mem_list *add_mem_node(mem_list **head, char *ptr);
void free_mem_list(mem_list **head);
void free_static_mem_list(mem_list **head);
char *_realloc(char *ptr, size_t new_size);
char *_memset(char *s, char b, unsigned int n);
void free_my_env(void);

size_t _strlen(char *s);
char *_strncpy(char *dest, const char *src, size_t n);
int _strncmp(char *s1, char *s2, size_t n);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_revstr(char *s);

char *_itoa(size_t number, char *buffer, int base);
size_t count_digit(size_t num);

size_t path_len(char *path_ptr);
size_t path_count(char *paths);
size_t path_check(char *const *argv);

int builtin_exit(char *const *argv);
int builtin_env(char *const *argv);
int builtin_cd(char *const *argv);

int cd_HOME(void);
int cd_current(void);
int cd_prev(void);
int cd_parent(void);
int cd_arg(char *arg);
int cd_user(char *argv);
int set_PWD(char *value);
int set_OLDPWD(void);
char *get_target(char *var_name);

void print_err(size_t loop_cnt, char *argv, char **tok_array);

#endif
