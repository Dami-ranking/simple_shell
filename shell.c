#include"main.h"
/**
 * _printf - Function to print a message
 * @mess: The message to be printed
 */
void _printf(const char *mess)
{
	write(1, mess, strlen(mess));
}

/**
 * main - then entrying point
 * Return: 0
 */
int main(void)
{
	char *buffer = NULL;
	size_t size = 0;
	char *token, *path;
	char *delim = " \n";
	ssize_t num;
	int i;
	char *argv[50];

	while (true)
	{
		_printf("simpleshell$ ");
		num = getline(&buffer, &size, stdin);
		if (num == -1)
		{
				printf("\n\n\n[Disconnected....]\n");
				free(buffer);
				exit(EXIT_FAILURE);
		}
		if (strspn(buffer, " \t\n"))
		{
			continue;
		}
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
		if (i > 0 && strcmp(argv[0], "exit") == 0)
		{
			_printf("\n\n\n[Disconnected....]\n");
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		if (path != NULL)
			exec(path, argv);
		else if (access(argv[0], X_OK) == 0)
		{
			exec(path, argv);
		}
	}
	free(buffer);
	return (0);
}
