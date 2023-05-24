#include "shell.h"

int check_buffer(char *buffer);
void shift_buffer(char *buffer, ssize_t offset);
ssize_t copy_buffer(char **line, char *buffer, ssize_t *offset);

/**
 * _getline - retrieve command line
 * @line: buffer to store command line
 *
 * Return: -1 on fail
 */
ssize_t _getline(char **line)
{
	ssize_t read_cnt = 0, copied = 0;
	static ssize_t read_total;
	ssize_t offset = 0;
	static char buffer[1024];

	if ((check_buffer(buffer)) == 0)
	{
		while ((read_cnt = read(STDIN_FILENO, buffer, 1023)) > 0)
		{
			if (read_cnt == -1)
				return (-1);

			read_total += read_cnt;

			buffer[read_cnt] = '\0';

			copied = copy_buffer(&(*line), buffer, &offset);


			if (copied < read_cnt)
			{
				offset = 0;
				return (read_total);
			}
		}
		read_total = 0;
	}
	else
	{
		copied = (copy_buffer(&(*line), buffer, &offset) + 1);
	}
	return (read_total);
}

/**
 * check_buffer - check if buffer
 * @buffer: buffer
 * Return: number of bytes written in buffer
 */
int check_buffer(char *buffer)
{
	int bytes = 0;

	while (buffer[bytes])
		bytes++;

	return (bytes);
}

/**
 * copy_buffer - copy from buffer
 * @line: copy dest
 * @buffer: copy src
 * @offset: line
 *
 * Return: bytes copied
 */
ssize_t copy_buffer(char **line, char *buffer, ssize_t *offset)
{
	size_t i = 0, cpy_cnt = 0;

	for (; buffer[i] != '\n' && buffer[i] != '\0'; i++)
		cpy_cnt++;

	if (buffer[i] == '\n')
	{
		*line = alloc_mngr(*line, (sizeof(char) * (cpy_cnt + *offset + 1)));
		if (!(*line))
			return (-1);

		_strncpy((*line + *offset), buffer, cpy_cnt);
		shift_buffer(buffer, (cpy_cnt + 1));

		return (cpy_cnt);
	}
	if (buffer[i] == '\0')
	{
		*line = alloc_mngr(*line, (sizeof(char) * (cpy_cnt + *offset + 1)));
		if (!(*line))
			return (-1);

		_strncpy((*line + *offset), buffer, (cpy_cnt));

		*offset += cpy_cnt;

		return (cpy_cnt);
	}

	return (cpy_cnt);
}
/**
 * shift_buffer - shift buffer
 * @buffer: buffer
 * @n: number of bytes
 */
void shift_buffer(char *buffer, ssize_t n)
{
	ssize_t i = 0;

	while (buffer[n] != '\0')
	{
		buffer[i] = buffer[n];
		i++;
		n++;
	}

	_memset(&buffer[i], 0, (1024 - n));
}
