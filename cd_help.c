#include "shell.h"

/**
 * cd_arg - move path
 * @arg: The directory to go
 * Return: 0
 */
int cd_arg(char *arg)
{
	char *target_dir = NULL;
	char *path = NULL;
	size_t len = 0;

	if (chdir(arg) == 0)

{
		if (path_check(&arg))
		{
			set_OLDPWD();
			set_PWD(arg);
			return (0);
		}
		else
		{
			target_dir = get_target("PWD=");

			len = (_strlen(target_dir) + _strlen(arg));

			path = alloc_mngr(path, (sizeof(char) * (len + 2)));
			if (!path)
				return (-1);

			_strncpy(path, target_dir, _strlen(target_dir));

			_strcat(path, "/");
			_strcat(path, arg);

			set_OLDPWD();
			set_PWD(path);

			return (0);
		}
	}
	errno = ENOENT;
	return (-1);
}

/**
 * cd_user - user home
 * @argv: User id
 *
 * Return: 0 , 1 on Failure
 */
int cd_user(char *argv)
{
	char *userdir = NULL;
	size_t user_len = _strlen(argv);

	userdir = alloc_mngr(userdir, (sizeof(char) * (6 + user_len)));
	if (!userdir)
		return (-1);

	_strncpy(userdir, "/home/", 6);
	_strcat(userdir, &argv[1]);

	if (chdir(userdir) == 0)
	{
		set_OLDPWD();
		set_PWD(userdir);
		return (0);
	}

	errno = ENOENT;
	return (-1);
}

/**
 * get_target - copy target environ
 * @var_name: name of tarvariable
 *
 * Return: NULL on Failure
 */
char *get_target(char *var_name)
{
	char *path = NULL;
	size_t i = 0;
	size_t path_len = 0;
	size_t name_len = _strlen(var_name);

	for (; environ[i]; i++)
	{
		if ((_strncmp(var_name, environ[i], name_len)) == 0)
		{
			path_len = (_strlen(environ[i]) - name_len);


			path = alloc_mngr(path, (sizeof(char) * (path_len + 1)));
			if (!path)
				return (NULL);


			_strncpy(path, &environ[i][name_len], path_len);

			return (path);
		}
	}
	errno = ENOENT;
	return (NULL);
}

/**
 * set_PWD - set  var PWD
 * @value: desired variable
 *
 * Return: 0 , 1 on Failure
 */
int set_PWD(char *value)
{
	char *update = NULL;
	char *name = "PWD=";
	size_t i = 0;
	size_t val_len;
	size_t name_len = 4;

	val_len = _strlen(value);

	for (; environ[i]; i++)
	{

		if ((_strncmp(name, environ[i], name_len)) == 0)
		{

			environ[i] = _realloc(update, (sizeof(char) * (name_len + val_len + 1)));
			if (!environ[i])
				return (-1);

			add_mem_node(&static_mem_head, environ[i]);

			_strncpy(environ[i], name, name_len);
			_strcat(environ[i], value);

			if (environ[i][name_len + val_len - 1] == '/')
				environ[i][name_len + val_len - 1] = '\0';

			return (0);
		}
	}

	errno = ENOENT;
	return (-1);
}

/**
 * set_OLDPWD - set
 *
 * Return: 0 , 1 on Failure
 */
int set_OLDPWD(void)
{
	char *update = NULL;
	char *pwd = NULL;
	char *owd_ref = "OLDPWD=";
	char *pwd_ref = "PWD=";
	size_t i;
	size_t pwd_len = 0;

	for (i = 0; environ[i]; i++)
		if ((_strncmp(pwd_ref, environ[i], 4)) == 0)
			pwd = &environ[i][4];
	if (!pwd)
		return (-1);

	pwd_len = _strlen(pwd);

	for (i = 0; environ[i]; i++)
	{
		if ((_strncmp(owd_ref, environ[i], 7)) == 0)
		{

			environ[i] = _realloc(update, (sizeof(char) * (7 + pwd_len + 1)));
			if (!environ[i])
				return (-1);

			add_mem_node(&static_mem_head, environ[i]);

			_strncpy(environ[i], owd_ref, 7);
			_strcat(environ[i], pwd);
			return (0);
		}
	}

	errno = ENOENT;
	return (-1);
}
