#include"main.h"
/*char **token_check(char *buffer)
{
	int i;
	char *delim = " ";
	char *token;
	char **argv;

	token = strtok(buffer, delim);
	i = 0;
	while (token != NULL)
	{
		argv = malloc(sizeof(char *) * (strlen(token) + 1));
		strcpy(argv[i], token);
		++i;
		token = strtok(NULL, delim);
	}
	argv[i] = NULL;
	return (argv);
}*/


char **token_check(char *buffer)
{
    int i = 0;
    char *delim = " ";
    char *token;
    char **argv = malloc(sizeof(char *)+ 50); // Adjust MAX_TOKENS as needed

    if (argv == NULL)
    {
        // Handle memory allocation failure
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(buffer, delim);

    while (token != NULL)
    {
        argv[i] = malloc(strlen(token) + 1);
        
        if (argv[i] == NULL)
        {
            // Handle memory allocation failure
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        strcpy(argv[i], token);
        ++i;
        token = strtok(NULL, delim);
    }

    argv[i] = NULL; // Null-terminate the array

    return argv;
}
/*void free_argv(char **argv)
{
    for (int i = 0; argv[i] != NULL; ++i)
    {
        free(argv[i]);
    }
    free(argv);
}
*/
