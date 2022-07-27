/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:19:59 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/07/05 12:19:59 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <./readline/readline.h>
# include <./readline/history.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <stddef.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <dirent.h>
# include <sys/wait.h>

typedef struct s_pipe
{
    char    *input;
    int     p[2];
    char    **envi;
    char    *prev_arg;
    int     fd_out;
    int     fd;
} t_pipe;

struct t_stack
{
    t_pipe          pipe;
    struct t_stack  *next;
    struct t_stack  *prev;
};

int			echo(char *input, int n, struct t_stack *stack);
int			str_cmp(char *str1, char *str2);
int			is_cmd(char *str, char **envi);
char		*pipetoken(char *input, char *c);
int			cd(char **intro, char **envi);
int			expand(char **txt);
char		*literal(char *input);
int			expand2(char *txt);
int			path_exe(const char **intro, char **envi, char *txt);
void		env(char **envi, struct t_stack *node);
void		launch(char *intro, char **envi);
const char	*search_cmd(char *txt, char **envi);
pid_t		child_launch(char *input, char **envi, struct t_stack *stack);
void		clear(char **intro);
void		export(char *input, char **envi);
struct t_stack     *pipe_stack(char * input, char **envi);
struct t_stack     *create_node(char *txt, char **envi);
void        insert_f_pipe(struct t_stack *node, struct t_stack *stack);
void        insert_l_pipe(struct t_stack *node, struct t_stack *stack);
void        exec_stack(struct t_stack *stack);
void        free_stack(struct t_stack *stack);
int         exec_cmd(char *input, char **envi, struct t_stack *stack);
int         is_built_in(char *input, char **envi, struct t_stack *node);
int         is_cmd(char *input, char **envi);
pid_t	    child_launch_pipe(char *input, char **envi, struct t_stack *node);
int         built_in_out(char *input, char **envi, struct t_stack *node);
int         is_built(char *input);
void	    prev_cmd_out(char *input, char **envi, struct t_stack *node);
void	    clear_file(char *file);

#endif
