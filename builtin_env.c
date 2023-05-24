#include "shell.h"
/**
 * builtin_env - print environment
 * @argv: command table
 *
 * Return: 0 , -1 on Failure
 */
int builtin_env(char *const *argv)
{
	size_t row, len;

	if (!argv[1])
		for (row = 0; environ[row]; row++)
		{
			len = _strlen(environ[row]);

			if ((write(STDOUT_FILENO, environ[row], len)) == -1)
				return (-1);

			if ((write(STDOUT_FILENO, "\n", 1)) == -1)
				return (-1);
		}
	else
	{
		errno = ENOENT;
		return (-1);
	}

	return (0);
}
