#include "shell.h"

/**
 * my_exit - exit
 */
void my_exit(void)
{
	exit(EXIT_SUCCESS);
}
/**
 * my_exit_status - exit
 * @args: array of strings of arguments
 * Return: void
 */
void my_exit_status(char **args)
{
	int status = atoi(args[1]);
	free(args);
	exit(status);
}

/**
 * _cd - changes the current working directory
 * @args: An array of strings containing the destination directory
 * Return: void
 */
void _cd(char **args)
{
	char *home;

	if (!args[0])
		_perror("cd: missing argument\n");
	else if (!args[1])
	{
		home = getenv("HOME");
		if (chdir(home) != 0)
			_perror("cd: No such file or directory\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
			_perror("cd: No such file or directory\n");
	}
}

/**
 * env_shell - print the current environment
 * Return: Nothing
 */
void env_shell(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		_print(environ[i]);
		_print("\n");
		i++;
	}
}
