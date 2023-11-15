#include "patty.h"

/**
 * get_fhistory_file - gets the history file
 * @finfo: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_fhistory_file(finfo_a *finfo)
{
	char *buf, *fdir;

	fdir = _fgetenv(finfo, "HOME=");
	if (!fdir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(fdir) + _strlen(FHIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, fdir);
	_strcat(buf, "/");
	_strcat(buf, FHIST_FILE);
	return (buf);
}

/**
 * write_fhistory - creates a file, or appends to an existing file
 * @finfo: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_fhistory(finfo_a *finfo)
{
	ssize_t fd;
	char *filename = get_fhistory_file(finfo);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = (*finfo).history; node; node = (*node).next)
	{
		_fputsfd((*node).fstr, fd);
		_fputfd('\n', fd);
	}
	_fputfd(FBUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_fhistory - reads history from file
 * @finfo: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_fhistory(finfo_a *finfo)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_fhistory_file(finfo);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_fhistory_list(finfo, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_fhistory_list(finfo, buf + last, linecount++);
	free(buf);
	(*finfo).histcount = linecount;
	while ((*finfo).histcount-- >= FHIST_MAX)
		fdelete_node_at_ind(&((*finfo).history), 0);
	renumber_history(finfo);
	return ((*finfo).histcount);
}

/**
 * build_fhistory_list - adds entry to a history linked list
 * @finfo: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_fhistory_list(finfo_a *finfo, char *buf, int linecount)
{
	list_t *node = NULL;

	if ((*finfo).history)
		node = (*finfo).history;
	fadd_node_end(&node, buf, linecount);

	if (!(*finfo).history)
		(*finfo).history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @finfo: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(finfo_a *finfo)
{
	list_t *node = (*finfo).history;
	int i = 0;

	while (node)
	{
		(*node).num = i++;
		node = (*node).next;
	}
	return ((*finfo).histcount = i);
}
