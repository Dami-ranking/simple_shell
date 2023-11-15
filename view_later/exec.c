#include "main.h"
/**
 * exec - execution of program
 * @path: path to the program to be executed
 * @argv: array of arguments, including the program name
 * Return: return the exit status of the child process
 */
int exec(char *path, char *argv[])
{
	pid_t child;

	child = fork();
	if (child == -1)
	{
		return (-1);
	}
	else if (child == 0)
	{
		int val =  execve(path, argv, NULL);

		if (val == -1)
			perror("error");
	}
	else
	{
		wait(NULL);
	}
	return (0);
}
