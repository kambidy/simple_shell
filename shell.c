#include "shell.h"

void recieve_sig(int signal);

/**
 * main - loop  tasks
 * @argc: Counts array
 * @argv: An  command line
 *
 * Return: 0  Failure
 */
int main(int argc __attribute__((unused)),  char **argv)
{
	char *line = NULL;
	char **tok_array = NULL;
	size_t loop_cnt = 1;

	do {
		line = NULL;
		tok_array = NULL;


		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);


		signal(SIGINT, recieve_sig);


		if ((_getline(&line)) == 0)
		{
			free_mem_list(&mem_head);
			free_static_mem_list(&static_mem_head);
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_SUCCESS);
		}

		/* set pointer array to parsed command line */
		if (line)
			tok_array = _strtok(line);

		if (tok_array) /* if token present */
			if ((exec_mngr(tok_array)) == -1) /* pass args to executor */
				print_err(loop_cnt, argv[0], tok_array);

		free_mem_list(&mem_head); /* free all allocated memory */

		loop_cnt++; /* increment loop count */

	} while (1);

	free_static_mem_list(&static_mem_head); /* free all persevering memory */
	return (0);
}

/**
 * recieve_sig - Prints the command line again when [CTRL + c]
 * @signal: Unusued attribute
 */
void recieve_sig(int signal __attribute__((unused)))
{
	/* prints the command line prompt */
	write(STDOUT_FILENO, "\n$ ", 3);
}
