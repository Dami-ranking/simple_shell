#include "main.h"
/**
 * get_path - Get the path to the executable based on the argument
 * @arg: The argument to search for
 * Return: The path to the executable or NULL if not found
 */
char *get_path(char *arg)
{
	char *path = getenv("PATH");

	if (path)
	{
		return (loca(path, arg));
	}
	return (NULL);
}

/**
 * loca - Search for the executable in the directories specified in PATH
 * @path: The PATH environment variable
 * @arg: The argument to search for
 * Return: The path to the executable or NULL if not found
 */
char *loca(char *path, char *arg)
{
	char *path_cp, *path_tok, *path_hold;
	const char *delim = ":";

	path_cp = strdup(path);
	if (path_cp == NULL)
	{
		perror("Memory allocation error!");
		exit(EXIT_FAILURE);
	}
	path_tok = strtok(path_cp, delim);
	while (path_tok != NULL)
	{
		path_hold = (char *)malloc(strlen(path_tok) + strlen(arg) + 2);
		if (path_hold == NULL)
		{
			perror("memory error");
			exit(EXIT_FAILURE);
		}
		strcpy(path_hold, path_tok);
		strcat(path_hold, "/");
		strcat(path_hold, arg);

		if (access(path_hold, X_OK) == 0)
		{
			free(path_cp);
			return (path_hold);
		}
		free(path_hold);
		path_tok = strtok(NULL, delim);

	}
	free(path_cp);
	return (NULL);
}
