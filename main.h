#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include<sys/wait.h>
#include <sys/types.h>


int exec(char *path, char *argv[]);
char *get_path(char *arg);
char *loca(char *path, char *arg);

#endif
