#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <./readline/readline.h>
#include <./readline/history.h>
#include </usr/include/stdlib.h>
#include "../libft/libft.h"
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>

int     echo(char *input, int n);
int     str_cmp(char *str1, char *str2);
int     is_cmd(char *str, char **envi);
char    *pipetoken(char *input, char *c);
int     cd(char **intro, char **envi);
int     expand(char **txt);
char    *literal(char *input);
int     expand2(char *txt);
int     path_exe(const char **intro, char **envi, char *txt);
void    env(char **envi);
void    launch(char *intro, char **envi);
const char *search_cmd(char *txt, char **envi);
pid_t child_launch(char *input, char **envi);
void    clear(char **intro);


#endif
