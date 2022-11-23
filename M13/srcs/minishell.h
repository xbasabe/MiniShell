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
# include <errno.h>

typedef struct s_pipe
{
    char    *input;
    int     p[2];
    char    **envi;
    char    *ext_path;
    char    *cmd;
    char    **arg;
    //pid_t   node_pid;
} t_pipe;

struct t_stack
{
    t_pipe          pipe;
    struct t_stack  *next;
    struct t_stack  *prev;
};
//builtin
int			echo(struct t_stack *stack);
void		env(char **envi, struct t_stack *node);
void	    pwd(char **envi, struct t_stack *node);
void		export(char *input, char **envi);
void	    unset(char *input, char **envi);
void        exit_kill(struct t_stack *node);
int         exec_built_in(char *input, char **envi, struct t_stack *node);

//cd
char    *active_dir(char **envi);
int     init_cd(char *input, char **envi, struct t_stack *node);
void    update_pwd(char **envi, struct t_stack *node);
void    expand_relative(char **envi, struct t_stack *node);
void    expand_relative2(char **envi, struct t_stack *node);
void    cd(char *input, char **envi, struct t_stack *node);

//execbash
void    exec_in_child(char *input, char **envi, struct t_stack *stack);
pid_t	child_launch(char *input, char **envi, struct t_stack *stack);
void    exec_stack(struct t_stack *stack);

//execv
int	    launch(char *intro, char **envi, struct t_stack *node);
const char	*search_cmd(char *txt, char **envi);
const char	*path_exe(char **envi, char *txt);
int	accesible(const char *path);

//in_out
int     is_built(char *input);
int     fd_putstr_out(char *str, struct t_stack *node);
void    redirect_pipes(struct t_stack *node);
int     read_pipe(int fd, char *str); //deshuso
int     write_pipe(int fd, char *str); //deshuso

//main
void	clear(char **intro);

//parse
int     expand(char **txt);
int     expand2(char *txt);
char	*literal(char *input);
int     inside_open_quotes(char *input);
    /*version 1*/
void    quote_in_or_out(char txt, int *count, int *flags);
void    quote_d_count(char *txt, int *count);
void	remove_quote(char *txt, int init);
char    *search_vble_env(char *txt, int init);
char	*parse(char *txt);
int	    OLD_quote_in_or_out(char *txt, int ini);
void    flag_check(int flag, int *flags);
char *expand_vble(char *txt, int *init);
char    *quote_in_or_out_loop(char *txt, int *count, int *flags);
char    *expand_loop(char *txt);
int     inside_simple(char *txt, int *flags, int *count, int *i);
int     inside_doble(char *txt, int *flags, int *count, int *i);

char	*new_quote_in_or_out_loop(char *txt, int *count, int *flags);
void	flip_flag(char *txt, int *flags, int *count, int i, int f);

    /*version 2*/
char	*parsing	(char *input);
char    *expand3(char *txt, int init, int end);
int inside_open_quotes2(char *input);
int outside_quotes(char *input);
char	**parse_split(char *input, char c);
int count_words(char *str);
void	fill(char *str, char **word, int index);
void	malloc_split(char *entry, char **splited, int index);



//lexer
void    create_cmds(struct t_stack *node);
void    cmd_path(struct t_stack *node);
void    relative_path(struct t_stack *node);
void    exp_act_path(struct t_stack *node);
void    exp_up_path(struct t_stack *node);

//stack
struct t_stack  *pipe_stack(char * input, char **envi);
struct t_stack  *create_node(char *txt, char **envi);
void            insert_f_pipe(struct t_stack *node, struct t_stack *stack);
void            insert_l_pipe(struct t_stack *node, struct t_stack *stack);
void            free_stack(struct t_stack *stack);
void            free_node(struct t_stack *node);
void            deleteAllNodes(struct t_stack *start);
void            free_node_content(struct t_stack *node);

int			str_cmp(char *str1, char *str2);

#endif
