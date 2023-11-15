#include"main.h"
/**
 * main - then entrying point
 * Return: 0
 */
int main(void)
{
	char *buffer = NULL, *delim = " \n", *token, *path, *argv[50];
	size_t size = 0;
	ssize_t num;
	int i;

	while (true)
	{
		_printf("simpleshell$ ");
		num = getline(&buffer, &size, stdin);
		if (num == -1)
			exit(EXIT_FAILURE);
		if (strspn(buffer, " \t\n"))
			continue;
		token = strtok(buffer, delim);
		i = 0;
		while (token != NULL && i < 50)
		{
			argv[i] = malloc(sizeof(char *) * (strlen(token) + 1));
			strcpy(argv[i], token);
			i++;
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
		path = get_path(argv[0]);
		exit_comd(argv);
		if (path != NULL)
			exec(path, argv);
		else if (access(argv[0], X_OK) == 0)
			exec(path, argv);
	}
	free(buffer);
	return (0);
}
