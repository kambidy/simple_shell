#include "shell.h"
/**
 * get_path - locate, array
 * @argv: command tab
 *
 * Return: pointer t
 */
char **get_path(char *const *argv)
{
	char *path_ptr = NULL;
	char *ref = "PATH=";
	char **path = NULL;
	size_t path_cnt, env_i = 0, p_i;
	size_t path_cat_size;

	while (environ[env_i])
	{
		if (_strncmp(ref, environ[env_i], 5) == 0)
		{
			path_ptr = &environ[env_i][5];
			path_cnt = path_count(path_ptr);

			path = (char **)alloc_mngr((char *)path, (sizeof(char *) * (path_cnt + 1)));

			for (p_i = 0; p_i < path_cnt; p_i++)
			{

				path_cat_size = (path_len(path_ptr) + _strlen(argv[0]) + 2);

				path[p_i] = alloc_mngr(path[p_i], (sizeof(char) * path_cat_size));

				_strncpy(path[p_i], path_ptr, path_len(path_ptr));
				_strcat(path[p_i], "/");
				_strcat(path[p_i], argv[0]);


				path_ptr = (path_ptr + (path_len(path_ptr) + 1));
			}
			path[p_i] = NULL;
			return (path);
		}
		env_i++;
	}
	return (NULL);
}

/**
 * path_check - determinepath
 * @argv: command
 *
 * Return: 1 , 0 if not path
 */
size_t path_check(char *const *argv)
{
	size_t i = 0, is_path = 0;

	while (argv[0][i])
	{
		if (argv[0][i] == '/')
		{
			is_path = 1;
			break;
		}
		i++;
	}

	return (is_path);
}
/**
 * path_count - count
 * @paths: PATH environ
 *
 * Return: 0 if paths NULL
 */
size_t path_count(char *paths)
{
	size_t i, path_cnt = 0;

	if (!paths)
		return (0);

	for (i = 0; paths[i]; i++)
		if ((paths[i + 1] == ':' || paths[i + 1] == '\0'))
			path_cnt++;

	return (path_cnt);
}
/**
* path_len - take path
* @path_ptr: pointer  path
*
* Return: length of path
*/
size_t path_len(char *path_ptr)
{
	size_t i = 0;
 /* if not NULL */
		while (path_ptr[i] != ':' && path_ptr[i] != '\0')
			i++;

	return (i);
}
