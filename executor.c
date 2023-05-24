#include "shell.h"
/**
 * exec_mngr - directs execution flow
 * @argv: cmd table
 * Return: 0 , -1 on Failure
 */
int exec_mngr(char *const *argv)
{
	int r_val;

	r_val = exec_builtin(argv);
	if (r_val == 0)
		return (0);

	if (err_msg == 2)
	{
		r_val = (exec_external(argv));
		if (r_val == 0)
			return (0);
	}

	return (-1);
}
/**
 * exec_builtin - identify commands
 * @argv: cmd table (i.e. list of user args)
 *
 * Return: 0 , -1 on Failure
 */
int exec_builtin(char *const *argv)
{
	built_in fps[] = {
		{"exit", builtin_exit},
		{"env", builtin_env},
		{"cd", builtin_cd},
		{NULL, NULL}
	};

	int i;
	int (*built_in_fp)(char *const *argv);

	for (i = 0; fps[i].cmd; i++)
		if ((_strcmp(argv[0], fps[i].cmd)) == 0)
		{
			built_in_fp = fps[i].fp;

			if ((built_in_fp(argv)) == 0)
				return (0);

			err_msg = 3;
			return (-1);
		}
	err_msg = 2;
	return (-1);
}
/**
 * exec_external - identify commands
 * @argv: cmd table
 * Return: 0 , -1 on Failure
 */
int exec_external(char *const *argv)
{
	char **path = NULL;
	pid_t pid;
	int status, i;

	if (path_check(argv))
	{

		path = (char **)alloc_mngr((char *)path, (sizeof(char *) * 2));

		path[0] = alloc_mngr(path[0], (sizeof(char) * (_strlen(argv[0]) + 1)));
		_strncpy(path[0], argv[0], _strlen(argv[0]));
		path[1] = NULL;
	}
	else
		path = get_path(argv);

	for (i = 0; path[i]; i++)
		if (access(path[i], (R_OK | X_OK)) == 0)
		{
			switch ((pid = fork()))
			{
				case -1:
					return (-1);
				case 0:
					execve(path[i], argv, environ);
					err_msg = 1;

					exit(EXIT_FAILURE);
				default:
					if ((waitpid(pid, &status, 0)) == -1)
						return (-1);
					else
						return (0);
			}
		}

	err_msg = 2;
	return (-1);
}
