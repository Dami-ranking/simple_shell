#include "patty.h"

/**
 * main - entry point
 * @ac: ag count
 * @av: ag vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	finfo_a finfo[] = { INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_fputs(av[0]);
				_fputs(": 0: Can't open ");
				_fputs(av[1]);
				_fputchar('\n');
				_fputchar(FBUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		(*finfo).readfd = fd;
	}
	fpop_env_list(finfo);
	read_fhistory(finfo);
	fmain(finfo, av);
	return (EXIT_SUCCESS);
}
