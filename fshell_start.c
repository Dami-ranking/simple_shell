#include "patty.h"

/**
 * fmain - main fmain loop
 * @finfo: the parameter & return finfo struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int fmain(finfo_a *finfo, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_finfo(finfo);
		if (interact(finfo))
			_puts("$ ");
		_fputchar(FBUF_FLUSH);
		r = get_input(finfo);
		if (r != -1)
		{
			set_finfo(finfo, av);
			builtin_ret = find_builtin(finfo);
			if (builtin_ret == -1)
				find_cmd(finfo);
		}
		else if (interact(finfo))
			_putchar('\n');
		free_finfo(finfo, 0);
	}
	write_fhistory(finfo);
	free_finfo(finfo, 1);
	if (!interact(finfo) && (*finfo).status)
		exit((*finfo).status);
	if (builtin_ret == -2)
	{
		if ((*finfo).err_num == -1)
			exit((*finfo).status);
		exit((*finfo).err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @finfo: the parameter & return finfo struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(finfo_a *finfo)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _fexit},
		{"env", _fenv},
		{"help", _fhelp},
		{"history", _fhistory},
		{"setenv", _fmsetenv},
		{"unsetenv", _funsetenv},
		{"cd", _fcd},
		{"alias", _myfalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp((*finfo).agv[0], builtintbl[i].type) == 0)
		{
			(*finfo).line_count++;
			built_in_ret = builtintbl[i].func(finfo);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @finfo: the parameter & return finfo struct
 *
 * Return: void
 */
void find_cmd(finfo_a *finfo)
{
	char *path = NULL;
	int i, k;

	(*finfo).path = (*finfo).agv[0];
	if ((*finfo).fline == 1)
	{
		(*finfo).line_count++;
		(*finfo).fline = 0;
	}
	for (i = 0, k = 0; (*finfo).ag[i]; i++)
		if (!fdelim((*finfo).ag[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_fpath(finfo, _fgetenv(finfo, "PATH="), finfo->agv[0]);
	if (path)
	{
		finfo->path = path;
		fork_cmd(finfo);
	}
	else
	{
		if ((interact(finfo) || _fgetenv(finfo, "PATH=")
			|| finfo->agv[0][0] == '/') && fcmd(finfo, finfo->agv[0]))
			fork_cmd(finfo);
		else if (*(finfo->ag) != '\n' && _strcmp(finfo->agv[0], "/") != 0)
		{
			finfo->status = 127;
			print_error(finfo, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @finfo: the parameter & return finfo struct
 *
 * Return: void
 */
void fork_cmd(finfo_a *finfo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve((*finfo).path, (*finfo).agv, fget_env(finfo)) == -1)
		{
			free_finfo(finfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&((*finfo).status));
		if (WIFEXITED((*finfo).status))
		{
			(*finfo).status = WEXITSTATUS((*finfo).status);
			if ((*finfo).status == 126)
				print_error(finfo, "Permission denied\n");
		}
	}
}
