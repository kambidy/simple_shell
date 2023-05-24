#include "shell.h"
/**
 * free_static_mem_list - free listand sety head to NULL
 * @head: pointer to
 */
void free_static_mem_list(mem_list **head)
{
	mem_list *temp;

	if (head)
	{
		while (*head)
		{
			temp = *head;
			*head = (*head)->next;
			if (temp->mem_ptr)
				free(temp->mem_ptr);
			free(temp);
		}
		*head = NULL;
	}
}
