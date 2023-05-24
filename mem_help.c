#include "shell.h"
/**
 * alloc_mngr - allocate allocations
 * @ptr: pointer to
 * @size: size
  *
 * Return: pointer to allocat
 */
char *alloc_mngr(char *ptr, size_t size)
{

	ptr = _realloc(ptr, size);
	if (!(ptr))
	{
		perror("hsh");
		free_mem_list(&mem_head);
		return (NULL);
	}


	mem_head = add_mem_node(&mem_head, ptr);


	return (ptr);
}

/**
 * add_mem_node - li of list
 * @head: current new node
 *
 * @ptr: pointer to store in
 * Return: pointer to new list head
 */
mem_list *add_mem_node(mem_list **head, char *ptr)
{
	mem_list *new;


	new = malloc(sizeof(mem_list));
	if (!new)
		return (NULL);


	new->mem_ptr = ptr;
	new->next = *head;


	*head = new;

	return (*head);
}
/**
 * free_mem_list - free  to NULL
 * @head: pointer  free
 */
void free_mem_list(mem_list **head)
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
/**
 * _realloc - reallocate
 * @ptr: old
 * @new_size: size
 * Return: newly a
 */
char *_realloc(char *ptr, size_t new_size)
{
	char *re_ptr;
	size_t old_size = _strlen(ptr);
	size_t i = 0;


	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	re_ptr = malloc(new_size);
	if (!re_ptr)
		return (NULL);


	if (ptr)
	{
		for (i = 0; i < old_size && i < new_size; i++)
			*(re_ptr + i) = *(ptr + i);


	}


	_memset((re_ptr + old_size), 0, (new_size - old_size));


	return (re_ptr);
}
/**
 * _memset - fill  byte
 * @s: memory fill
 * @b: cons
 * @n: bytes
 *
 * Return: pointer t
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		s[i] = b;
		i++;
	}

	return (s);
}
