#include "patty.h"

/**
 *_fputs - prints an input string
 * @fstr: the string to be printed
 *
 * Return: Nothing
 */
void _fputs(char *fstr)
{
	int i = 0;

	if (!fstr)
		return;
	while (fstr[i] != '\0')
	{
		_fputchar(fstr[i]);
		i++;
	}
}

/**
 * _fputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _fputchar(char c)
{
	static int i;
	static char buf[FBUF_SIZE];

	if (c == FBUF_FLUSH || i >= FBUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != FBUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _fputfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _fputfd(char c, int fd)
{
	static int i;
	static char buf[FBUF_SIZE];

	if (c == FBUF_FLUSH || i >= FBUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != FBUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_fputsfd - prints an input string
 * @fstr: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _fputsfd(char *fstr, int fd)
{
	int i = 0;

	if (!fstr)
		return (0);
	while (*fstr)
	{
		i += _fputfd(*fstr++, fd);
	}
	return (i);
}

/**
 * _ferratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _ferratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
