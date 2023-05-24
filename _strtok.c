#include "shell.h"

size_t count_tokens(char *line);
size_t token_length(char *line, size_t tok_need);

/**
 * **_strtok - Sets up a 2D
 * @line: The string
 *
 * Return: 2D array
 */
char **_strtok(char *line)
{
	size_t alloc_size;
	size_t tok_amnt;
	size_t tok_len = 0, tok_curr = 1;
	size_t line_it = 0, tok_it = 0, i = 0;
	char **tok_array = NULL;

	tok_amnt = count_tokens(line);
	if (tok_amnt == 0)
		return (NULL);

	alloc_size = (tok_amnt + 1) * (sizeof(char *));
	tok_array = (char **)alloc_mngr((char *)tok_array, alloc_size);
	if (tok_array == NULL)
		return (NULL);

	for (i = 0; tok_curr <= tok_amnt; tok_curr++, i++)
	{
		tok_len = token_length(line, tok_curr);

		alloc_size = (tok_len + 1) * (sizeof(char));
		tok_array[i] = alloc_mngr(tok_array[i], alloc_size);
		if (tok_array[i] == NULL)
			return (NULL);

		while (line[line_it] == ' ' || line[line_it] == '\t')
			line_it++;

		for (tok_it = 0; tok_it < tok_len; tok_it++, line_it++)
			tok_array[i][tok_it] = line[line_it];

		tok_array[i][tok_it] = '\0';
	}

	tok_array[i] = NULL;

	return (tok_array);
}

/**
 * count_tokens - Counts tokens
 * @line: The string
 * Return: tokens
 */
size_t count_tokens(char *line)
{
	size_t it = 0, tok_amnt = 0;

	while (line[it] != '\0')
	{
		if ((line[it + 1] == ' ' || line[it + 1] == '\t') || line[it + 1] == '\0')
			if (line[it] != ' ' && line[it] != '\t')
				tok_amnt++;
		it++;
	}
	return (tok_amnt);
}

/**
 * token_length - Count how long
 * @line: The string token
 * @tok_need: Specifys needed7
 * Return: tspecified
 */
size_t token_length(char *line, size_t tok_need)
{
	size_t it = 0, tok_len = 0, tok_curr = 0;

	while (tok_curr < tok_need)
	{
		while (line[it] == ' ' || line[it] == '\t')
			it++;

		if (line[it] != '\0' && line[it] != ' ' && line[it] != '\t')
		{
			tok_curr++;
			while (line[it] != '\0' && line[it] != ' ' && line[it] != '\t')
			{
				if (tok_curr == tok_need)
					tok_len++;
				it++;
			}
		}
	}
	return (tok_len);
}
