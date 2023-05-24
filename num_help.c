#include "shell.h"

/**
* _itoa - Function that  to string
* @number: value to be to a string
* @buffer: array that stated string result
* @base: value of
*
* Return: converted string
*/
char *_itoa(size_t number, char *buffer, int base)
{
	int sign = 1, i = 0;
	size_t remainder = 0;


	if (number == 0)
	{
		buffer[i++] = '0';
		buffer[i] = '\0';
	}

	while (number)
	{
		remainder = number % base;
		buffer[i++] = '0' + remainder;
		number /= base;
	}

	if (sign < 0)
		buffer[i++] = '-';


	if (number)
		buffer[i] = '\0';
	return (_revstr(buffer));
}

/**
 * count_digit - Returns how
 * @num: The number
 * Return: Always a size_t
 */
size_t count_digit(size_t num)
{
	size_t count = 0;

	while (num != 0)
	{
		num /= 10;
		count++;
	}

	return (count);
}
