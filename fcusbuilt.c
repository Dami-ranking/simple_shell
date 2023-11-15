#include "patty.h"

/**
 * _myfalias - mimics the falias builtin (man falias)
 * @finfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myfalias(finfo_a *finfo)
{
	int i = 0;
	char *f = NULL;
	list_t *node = NULL;

	if ((*finfo).agc == 1)
	{
		node = (*finfo).falias;
		while (node)
		{
			print_falias(node);
			node = (*node).next;
		}
		return (0);
	}
	for (i = 1; (*finfo).agv[i]; i++)
	{
		f = _strchr((*finfo).agv[i], '=');
		if (f)
			set_falias(finfo, (*finfo).agv[i]);
		else
			print_falias(fnode_starts_with((*finfo).falias, (*finfo).agv[i], '='));
	}

	return (0);
}

/**
 * _fexit - exits the fmain
 * @finfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if finfo.agv[0] != "exit"
 */
int _fexit(finfo_a *finfo)
{
	int fexitcheck;

	if ((*finfo).agv[1])  /* If there is an exit arguement */
	{
		fexitcheck = _ferratoi((*finfo).agv[1]);
		if (fexitcheck == -1)
		{
			(*finfo).status = 2;
			print_error(finfo, "Illegal number: ");
			_fputs((*finfo).agv[1]);
			_fputchar('\n');
			return (1);
		}
		(*finfo).err_num = _ferratoi((*finfo).agv[1]);
		return (-2);
	}
	(*finfo).err_num = -1;
	return (-2);
}

/**
 * _fcd - changes the current directory of the process
 * @finfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _fcd(finfo_a *finfo)
{
	char *s, *fdir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!(*finfo).agv[1])
	{
		fdir = _fgetenv(finfo, "HOME=");
		if (!fdir)
			chdir_ret = /* TODO: what should this be? */
				chdir((fdir = _fgetenv(finfo, "PWD=")) ? fdir : "/");
		else
			chdir_ret = chdir(fdir);
	}
	else if (_strcmp((*finfo).agv[1], "-") == 0)
	{
		if (!_fgetenv(finfo, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_fgetenv(finfo, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((fdir = _fgetenv(finfo, "OLDPWD=")) ? fdir : "/");
	}
	else
		chdir_ret = chdir((*finfo).agv[1]);
	if (chdir_ret == -1)
	{
		print_error(finfo, "can't cd to ");
		_fputs((*finfo).agv[1]), _fputchar('\n');
	}
	else
	{
		_fsetenv(finfo, "OLDPWD", _fgetenv(finfo, "PWD="));
		_fsetenv(finfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _fhelp - changes the current directory of the process
 * @finfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _fhelp(finfo_a *finfo)
{
	char **arg_array;

	arg_array = (*finfo).agv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
