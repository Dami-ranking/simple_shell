#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include<sys/wait.h>
#include <sys/types.h>

void _printf(const char *mess);
int exec(char *path, char *argv[]);
char *get_path(char *arg);
char *loca(char *path, char *arg);
void exit_comd(char **argv);
void _printf(const char *mess);
char **token_check(char *buffer);
void free_argv(char **argv);

#endif
