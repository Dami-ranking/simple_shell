#include "patty.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * *_strdup - copies the string given as parameter
 * @str: string to duplicate
 * Return: pointer to the copied string (Success), NULL (Error)
 */

char *_strdup(const char *str)
{
	unsigned int i = 0, len = 0;
	char *d;

	if (str == NULL)
		return (NULL);

	while (str[len])
		len++;

	d = malloc(sizeof(char) * (len + 1));

	if (d == NULL)
		return (NULL);

	while ((d[i] = str[i]) != 0)
		i++;

	return (d);
}

/**
 *_puts - prints an input string
 *@fstr: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *fstr)
{
	int i = 0;

	if (!fstr)
		return;
	while (fstr[i] != '\0')
	{
		_putchar(fstr[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[FBUF_SIZE];

	if (c == FBUF_FLUSH || i >= FBUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != FBUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @fstr: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *fstr, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (fstr == NULL || fstr[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; fstr[i] != '\0'; i++)
		if (!fdelim(fstr[i], d) && (fdelim(fstr[i + 1], d) || !fstr[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (fdelim(fstr[i], d))
			i++;
		k = 0;
		while (!fdelim(fstr[i + k], d) && fstr[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = fstr[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
