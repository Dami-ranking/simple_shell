#include "patty.h"

/**
 * fget_env - returns the string array copy of our environ
 * @finfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **fget_env(finfo_a *finfo)
{
	if (!(*finfo).environ || (*finfo).env_changed)
	{
		(*finfo).environ = flist_to_strings((*finfo).env);
		(*finfo).env_changed = 0;
	}

	return ((*finfo).environ);
}

/**
 * f_unsetenv - Remove an environment variable
 * @finfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int f_unsetenv(finfo_a *finfo, char *var)
{
	list_t *node = (*finfo).env;
	size_t i = 0;
	char *f;

	if (!node || !var)
		return (0);

	while (node)
	{
		f = fstarts_with((*node).fstr, var);
		if (f && *f == '=')
		{
			(*finfo).env_changed = fdelete_node_at_ind(&((*finfo).env), i);
			i = 0;
			node = (*finfo).env;
			continue;
		}
		node = (*node).next;
		i++;
	}
	return ((*finfo).env_changed);
}

/**
 * _fsetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @finfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _fsetenv(finfo_a *finfo, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *f;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = (*finfo).env;
	while (node)
	{
		f = fstarts_with((*node).fstr, var);
		if (f && *f == '=')
		{
			free((*node).fstr);
			(*node).fstr = buf;
			(*finfo).env_changed = 1;
			return (0);
		}
		node = (*node).next;
	}
	fadd_node_end(&((*finfo).env), buf, 0);
	free(buf);
	(*finfo).env_changed = 1;
	return (0);
}
