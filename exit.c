#include"main.h"
/**
 * extrafunc - Execute a command using fork and execve.
 * @exe: An array of strings representing the command and its arguments.
 * @av: An array of strings representing the command-line arguments.
 */
void exit_comd(char **argv)
{
        if (strcmp(argv[0], "exit") == 0)
                  {
                         _printf("\n\n\n[Disconnected...]\n");
                         /*free(buffer);*/
                         exit(EXIT_SUCCESS);
                }
}
