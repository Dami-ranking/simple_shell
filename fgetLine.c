#include "patty.h"

/**
 * input_buf - buffers chained commands
 * @finfo: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(finfo_a *finfo, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)(*finfo).cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		r = getline(buf, &len_p, stdin);

		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			(*finfo).fline = 1;
			remove_comments(*buf);
			build_fhistory_list(finfo, *buf, (*finfo).histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				(*finfo).cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @finfo: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(finfo_a *finfo)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &((*finfo).ag), *f;

	_putchar(FBUF_FLUSH);
	r = input_buf(finfo, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		f = buf + i; /* get pointer for return */

		check_fchain(finfo, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (fchain(finfo, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			(*finfo).cmd_buf_type = FMD_N;
		}

		*buf_p = f; /* pass back pointer to current command position */
		return (_strlen(f)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _fgetline() */
	return (r); /* return length of buffer from _fgetline() */
}