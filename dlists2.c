#include "patty.h"

/**
 * flist_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t flist_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = (*h).next;
		i++;
	}
	return (i);
}

/**
 * flist_to_strings - returns an array of strings of the list fstr
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **flist_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = flist_len(head), j;
	char **strs;
	char *fstr;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = (*node).next, i++)
	{
		fstr = malloc(_strlen((*node).fstr) + 1);
		if (!fstr)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		fstr = _strcpy(fstr, (*node).fstr);
		strs[i] = fstr;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * _fprintlist - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t _fprintlist(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number((*h).num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts((*h).fstr ? (*h).fstr : "(nil)");
		_puts("\n");
		h = (*h).next;
		i++;
	}
	return (i);
}

/**
 * fnode_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *fnode_starts_with(list_t *node, char *prefix, char c)
{
	char *f = NULL;

	while (node)
	{
		f = fstarts_with((*node).fstr, prefix);
		if (f && ((c == -1) || (*f == c)))
			return (node);
		node = (*node).next;
	}
	return (NULL);
}

/**
 * get_node_ind - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_ind(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
