#include "patty.h"

/**
 * _fenv - prints the current environment
 * @finfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _fenv(finfo_a *finfo)
{
	fprint_list_str((*finfo).env);
	return (0);
}

/**
 * _fgetenv - gets the value of an environ variable
 * @finfo: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_fgetenv(finfo_a *finfo, const char *name)
{
	list_t *node = (*finfo).env;
	char *f;

	while (node)
	{
		f = fstarts_with((*node).fstr, name);
		if (f && *f)
			return (f);
		node = (*node).next;
	}
	return (NULL);
}

/**
 * _fmsetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @finfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _fmsetenv(finfo_a *finfo)
{
	if ((*finfo).agc != 3)
	{
		_fputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_fsetenv(finfo, (*finfo).agv[1], (*finfo).agv[2]))
		return (0);
	return (1);
}

/**
 * _funsetenv - Remove an environment variable
 * @finfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _funsetenv(finfo_a *finfo)
{
	int i;

	if ((*finfo).agc == 1)
	{
		_fputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= (*finfo).agc; i++)
		f_unsetenv(finfo, (*finfo).agv[i]);

	return (0);
}

/**
 * fpop_env_list - populates env linked list
 * @finfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int fpop_env_list(finfo_a *finfo)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		fadd_node_end(&node, environ[i], 0);
	(*finfo).env = node;
	return (0);
}
