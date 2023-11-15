#include "patty.h"

/**
 * _strncpy - copies a string
 * @dest: destination string
 * @src: source string
 * @n: number of bytes to copy
 *
 * Return: pointer to the resulting string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int f = 0;

	while (src[f] != '\0' && f < n)
	{
		dest[f] = src[f];
		f++;
	}

	while (f < n)
	{
		dest[f] = '\0';
		f++;
	}

	return (dest);
}

/**
 * _strncat - concatenates n bytes from a string to another
 * @dest: destination string
 * @src: source string
 * @n: number of bytes of str to concatenate
 *
 * Return: a pointer to the resulting string dest
 */
char *_strncat(char *dest, char *src, int n)
{
	int f = 0, s = 0;

	while (dest[f] != '\0')
		f++;

	while (src[s] != '\0' && s < n)
	{
		dest[f] = src[s];
		f++;
		s++;
	}

	dest[f] = '\0';

	return (dest);
}

/**
 * *_strchr - locates a character in a string
 * @s: string to search
 * @c: char to find
 *
 * Return: a pointer to the first occurrence of the character
 * c in the string s, or NULL if the character is not found
 */

char *_strchr(char *s, char c)
{
		int a;

		while (1)
		{
			a = *s++;
			if (a == c)
			{
				return (s - 1);
			}
			if (a == '\0')
			{
				return (NULL);
			}
		}
}
