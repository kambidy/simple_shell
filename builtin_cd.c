#include "shell.h"
/**
 * builtin_cd - ch directory
 * @argv: command table
 *
 * Return: 0, -1 on Failure
 */
int builtin_cd(char *const *argv)
{
	if (argv[1] == NULL || !(_strcmp(argv[1], "~")))
	{
		if (cd_HOME())
			return (-1);
	}
	else if (!(_strcmp(argv[1], ".")))
	{
		if (cd_current())
			return (-1);
	}
	else if (!(_strcmp(argv[1], "-")))
	{
		if (cd_prev())
			return (-1);
	}
	else if (!(_strcmp(argv[1], "..")))
	{
		if (cd_parent())
			return (-1);
	}
	else if ((!(_strncmp(argv[1], "~", 1)) && (argv[1][1] != '\0')))
	{
		if (cd_user(argv[1]))
			return (-1);
	}
	else
	{
		if (cd_arg(argv[1]))
			return (-1);
	}
	return (0);
}
/**
 * cd_parent - move to directory
 * Return: 0 on Success, 1 on Failure
 */
int cd_parent(void)
{
	char *target_dir = NULL;
	size_t i;

	target_dir = get_target("PWD=");
	if (target_dir)
	{
		for (i = _strlen(target_dir); target_dir[i] != '/';)
			i--;
		for (; target_dir[i]; i++)
			target_dir[i] = '\0';

		if (chdir(target_dir) == 0)
		{
			set_OLDPWD();
			set_PWD(target_dir);
			return (0);
		}
	}

	return (-1);
}
/**
 * cd_prev - move to directory
 * Return: 0 , 1 on Failure
 */
int cd_prev(void)
{
	char *target_dir = NULL;

	target_dir = get_target("OLDPWD=");
	if (target_dir)
	{
		if (chdir(target_dir) == 0)
		{
			set_OLDPWD();
			set_PWD(target_dir);
			write(STDOUT_FILENO, target_dir, (_strlen(target_dir)));
			write(STDOUT_FILENO, "\n", 1);
			return (0);
		}
		else
			return (-1);
	}

	return (-1);
}
/**
 * cd_HOME - change directory
 * Return: 0, -1 on Failure
 */
int cd_HOME(void)
{
	char *target_dir = NULL;


	target_dir = get_target("HOME=");
	if (target_dir)
	{
		if (chdir(target_dir) == 0)
		{
			set_OLDPWD();
			set_PWD(target_dir);
			return (0);
		}
		else
			return (-1);
	}

	return (-1);
}
/**
 * cd_current - move to directory
 * Return: 0, 1 on Failure
 */
int cd_current(void)
{
	char *target_dir = NULL;

	target_dir = get_target("PWD=");
	if (target_dir)
	{
		if (chdir(target_dir) == 0)
		{
			set_OLDPWD();
			set_PWD(target_dir);
			return (0);
		}
		else
			return (-1);
	}

	return (-1);
}
