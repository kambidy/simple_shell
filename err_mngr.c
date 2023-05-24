#include "shell.h"

char *case_three(char *err_cus, char **tok_array);

/**
 * print_err - Print error
 * @loop_cnt: Current i
 * @argv: Contains the
 * @tok_array: Contains
 */
void print_err(size_t loop_cnt, char *argv, char **tok_array)
{
	char *err_tag = NULL, *loop_num = NULL, *err_cus = NULL;
	size_t err_cus_len, err_tag_len;
	size_t digit_amnt = count_digit(loop_cnt);
	size_t argv_len = _strlen(argv);
	size_t tok1_len = _strlen(tok_array[0]), tok2_len = _strlen(tok_array[1]);
	size_t total_alloc = argv_len + digit_amnt + tok1_len + tok2_len + 6;

	switch (err_msg)
	{
		case (2):
			err_cus = alloc_mngr(err_cus, (sizeof(char) * 12));
			err_cus = ": not found\0";
			break;
		case (3):
			err_cus = case_three(err_cus, tok_array);
			if (err_cus == NULL)
				return;
			break;
		default:
			perror(argv);
			return;
	}

	loop_num = alloc_mngr(loop_num, (sizeof(char) * (digit_amnt + 1)));
	_itoa(loop_cnt, loop_num, 10);

	err_cus_len = _strlen(err_cus);
	total_alloc += err_cus_len;

	err_tag = alloc_mngr(err_tag, sizeof(char) * total_alloc);

	_strncpy(err_tag, argv, argv_len);
	_strcat(err_tag, ": ");
	_strcat(err_tag, loop_num);
	_strcat(err_tag, ": ");
	_strcat(err_tag, tok_array[0]);
	_strcat(err_tag, err_cus);
	if (err_msg == 3)
		_strcat(err_tag, tok_array[1]);
	_strcat(err_tag, "\n");

	err_tag_len = _strlen(err_tag);

	write(STDERR_FILENO, err_tag, err_tag_len);
}

/**
 * case_three - Creates or pmessage
 * @err_cus: Where the custom  is saved to
 * @tok_array: Contains needed
 * Return: Either NULL or pointer error message
 */
char *case_three(char *err_cus, char **tok_array)
{
	size_t tok1_len = _strlen(tok_array[0]);
	size_t tok2_len = _strlen(tok_array[1]);

	if (tok1_len == 4)
	{
		err_cus = alloc_mngr(err_cus, (sizeof(char) * 19));
		err_cus = ": Illegal number: \0";
		return (err_cus);
	}
	else if (tok1_len == 2)
	{
		err_cus = alloc_mngr(err_cus, (sizeof(char) * 15));
		err_cus = ": can't cd to \0";
		return (err_cus);
	}

	err_cus = alloc_mngr(err_cus, sizeof(char) * tok1_len + tok2_len + 5);
	_strncpy(err_cus, tok_array[0], tok1_len);
	_strcat(err_cus, ": '");
	_strcat(err_cus, tok_array[1]);
	_strcat(err_cus, "'");

	errno = ENOENT;
	perror(err_cus);

	return (NULL);
}
