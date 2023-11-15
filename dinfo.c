#include "patty.h"

/**
 * clear_finfo - initializes finfo_a struct
 * @finfo: struct address
 */
void clear_finfo(finfo_a *finfo)
{
	(*finfo).ag = NULL;
	(*finfo).agv = NULL;
	(*finfo).path = NULL;
	(*finfo).agc = 0;
}

/**
 * set_finfo - initializes finfo_a struct
 * @finfo: struct address
 * @av: argument vector
 */
void set_finfo(finfo_a *finfo, char **av)
{
	int i = 0;

	(*finfo).fname = av[0];
	if ((*finfo).ag)
	{
		(*finfo).agv = strtow((*finfo).ag, " \t");
		if (!(*finfo).agv)
		{

			(*finfo).agv = malloc(sizeof(char *) * 2);
			if ((*finfo).agv)
			{
				(*finfo).agv[0] = _strdup((*finfo).ag);
				(*finfo).agv[1] = NULL;
			}
		}
		for (i = 0; (*finfo).agv && (*finfo).agv[i]; i++)
			;
		(*finfo).agc = i;

		replace_falias(finfo);
		replace_fvars(finfo);
	}
}

/**
 * free_finfo - frees finfo_a struct fields
 * @finfo: struct address
 * @all: true if freeing all fields
 */
void free_finfo(finfo_a *finfo, int all)
{
	ffree((*finfo).agv);
	(*finfo).agv = NULL;
	(*finfo).path = NULL;
	if (all)
	{
		if (!(*finfo).cmd_buf)
			free((*finfo).ag);
		if ((*finfo).env)
			free_flist(&((*finfo).env));
		if ((*finfo).history)
			free_flist(&((*finfo).history));
		if ((*finfo).falias)
			free_flist(&((*finfo).falias));
		ffree((*finfo).environ);
			(*finfo).environ = NULL;
		bfree((void **)(*finfo).cmd_buf);
		if ((*finfo).readfd > 2)
			close((*finfo).readfd);
		_putchar(FBUF_FLUSH);
	}
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FBUF_FLUSH);
}
