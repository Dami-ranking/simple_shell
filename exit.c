#include"main.h"
/**
 * exit_comd - Execute a command using fork and execve.
 * @ergv: An array of string
 */
void exit_comd(char **argv)
{
	if (strcmp(argv[0], "exit") == 0)
	{
		_printf("\n\n\n[Disconnected...]\n");
		exit(EXIT_SUCCESS);
	}
}
