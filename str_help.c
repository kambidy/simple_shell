#include "shell.h"

/**
* _strlen - Function that fi
* @s: string that
*
* Return: length o
*/
size_t _strlen(char *s)
{
	size_t len = 0;

	if (s)
		while (s[len] != '\0')
			len++;

	return (len);
}

/**
 * *_strncpy - copiest string
 * @dest: string
 * @src: string from
 * @n: number to copy
 *
 * Return: string to i.e dest
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t i = 0;

	while (i < n)
	{
		if (src[i] == '\0')
			break;
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

/**
 * _strcmp - Compares two
 * @s1: string to
 * @s2: string to compar
 *
 * Return: num < 0
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0')
	{
		if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s2[i] != '\0')
		return (s1[i] - s2[i]);
	return (0);
}

/**
 * _strncmp - compare sn bytes
 * @s1: string compare
 * @s2: string compare against
 * @n: bytes ompare
 *
 * Return: n < 0
 */
int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i = 0;

	while (i < n && s1[i] != '\0')
	{
		if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i < n && s2[i] != '\0')
		return (s1[i] - s2[i]);

	return (0);
}

/**
 * *_strcat - concatenates strings
 * @dest: string to  to
 * @src: sring to append
 *
 * Return: pointer  string
 */
char *_strcat(char *dest, char *src)
{
	int src_i = 0, dest_i = 0;

	for (; dest[dest_i] != '\0';)
		dest_i++;

	for (; src[src_i] != '\0';)
	{
		dest[dest_i] = src[src_i];
		src_i++;
		dest_i++;
	}

	dest[dest_i] = '\0';

	return (dest);
}
