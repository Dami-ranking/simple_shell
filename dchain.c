#include "patty.h"

/**
 * fchain - test if current char in buffer is a chain delimeter
 * @finfo: the parameter struct
 * @buf: the char buffer
 * @f: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int fchain(finfo_a *finfo, char *buf, size_t *f)
{
	size_t j = *f;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		(*finfo).cmd_buf_type = FMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		(*finfo).cmd_buf_type = FMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		(*finfo).cmd_buf_type = FMD_CHAIN;
	}
	else
		return (0);
	*f = j;
	return (1);
}

/**
 * check_fchain - checks we should continue chaining based on last status
 * @finfo: the parameter struct
 * @buf: the char buffer
 * @f: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_fchain(finfo_a *finfo, char *buf, size_t *f, size_t i, size_t len)
{
	size_t j = *f;

	if ((*finfo).cmd_buf_type == FMD_AND)
	{
		if ((*finfo).status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if ((*finfo).cmd_buf_type == FMD_OR)
	{
		if (!(*finfo).status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*f = j;
}

/**
 * replace_falias - replaces an faliases in the tokenized string
 * @finfo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_falias(finfo_a *finfo)
{
	int i;
	list_t *node;
	char *f;

	for (i = 0; i < 10; i++)
	{
		node = fnode_starts_with((*finfo).falias, (*finfo).agv[0], '=');
		if (!node)
			return (0);
		free((*finfo).agv[0]);
		f = _strchr((*node).fstr, '=');
		if (!f)
			return (0);
		f = _strdup(f + 1);
		if (!f)
			return (0);
		(*finfo).agv[0] = f;
	}
	return (1);
}

/**
 * replace_fvars - replaces vars in the tokenized string
 * @finfo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_fvars(finfo_a *finfo)
{
	int i = 0;
	list_t *node;

	for (i = 0; (*finfo).agv[i]; i++)
	{
		if ((*finfo).agv[i][0] != '$' || !(*finfo).agv[i][1])
			continue;

		if (!_strcmp((*finfo).agv[i], "$?"))
		{
			replace_fstring(&((*finfo).agv[i]),
				_strdup(convert_number((*finfo).status, 10, 0)));
			continue;
		}
		if (!_strcmp((*finfo).agv[i], "$$"))
		{
			replace_fstring(&((*finfo).agv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = fnode_starts_with((*finfo).env, &(*finfo).agv[i][1], '=');
		if (node)
		{
			replace_fstring(&((*finfo).agv[i]),
				_strdup(_strchr((*node).fstr, '=') + 1));
			continue;
		}
		replace_fstring(&(*finfo).agv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_fstring - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_fstring(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
