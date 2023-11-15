#include "patty.h"

/**
 * interact - returns true if fmain is interact mode
 * @finfo: struct address
 *
 * Return: 1 if interact mode, 0 otherwise
 */
int interact(finfo_a *finfo)
{
	return (isatty(STDIN_FILENO) && (*finfo).readfd <= 2);
}

/**
 * fdelim - checks if character is a delimeter
 * @c: the char to check
 * @fisdelim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int fdelim(char c, char *fisdelim)
{
	while (*fisdelim)
		if (*fisdelim++ == c)
			return (1);
	return (0);
}

/**
 * *_memset - fills memory with a constant byte
 * @s: memory area to be filled
 * @b: char to copy
 * @n: number of times to copy b
 *
 * Return: pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int mem = 0;

	while (mem < n)
	{
		s[mem] = b;
		mem++;
	}

	return (s);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * *_realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previsouly allocated by malloc
 * @old_size: size of the allocated memory for ptr
 * @new_size: new size of the new memory block
 * Return: pointer to the newly allocated memory block
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *f, *of;
	unsigned int i = 0;

	if (old_size == new_size)
		return (ptr);
	if (ptr && new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));

	f = malloc(new_size);
	if (f == NULL)
		return (NULL);
	of = ptr;

	if (new_size < old_size)
	{
		while (i < new_size)
		{
			f[i] = of[i];
			i++;
		}
	}
	if (old_size < new_size)
	{
		i = 0;
		while (i < old_size)
		{
			f[i] = of[i];
			i++;
		}
	}
	free(ptr);
	return (f);
}
