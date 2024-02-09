/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:19:59 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/09 00:04:54 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
//# include <stdbool.h>
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
# include <signal.h>

typedef struct s_env
{
	char			*name;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_pipe
{
	char	*input;
	char	*parsed_input;
	int		p[2];
	char	**envi; //esto hay que quitar. trasladar todo a struct
	char	*ext_path;
	char	*cmd;
	char	**arg;
	char	redir;
}	t_pipe;

typedef struct s_stack
{
	t_pipe			pipe;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

typedef struct s_token
{
	char*			content;
	struct s_token*	next;
	char			quotes; // s simples, d dobles, n nada
	char			direction;  // si lo siguiente es pipe p, redirección r o final f
} t_token;

typedef struct s_shell
{
	int				num_quit;
	int				pid;
	struct s_env	*env;
}	t_shell;

t_shell	g_shell;

//pre-parse. choped line

t_token  *create_token(char *txt);
void    insert_token(t_token *token, t_token *choped_line);


//builtin
int			echo(t_stack *stack, char *input);
void		env(t_stack *node);
void		pwd(t_stack *node);
void		unset(char *input);
void		exit_kill(t_stack *node);
int			exec_built_in(char *input, t_stack *node);

//export
void		export_add(char *vbl);
//t_env	*sort_env(void) //t_env version
void		export(t_stack *node);
void		export_no_args(t_stack *node);
int		export_check_arg(t_stack *node);

//cd
char		*active_dir(void);
int			init_cd(char *input, t_stack *node);
void		update_pwd(t_stack *node);
void		expand_relative(t_stack *node);
void		expand_relative2(t_stack *node);
void		cd(char *input, t_stack *node);

//execbash
void		exec_in_child(char *input, t_stack *stack);
pid_t		child_launch(char *input, t_stack *stack);
void		exec_stack(t_stack *stack, char *input);

//execv
char		**tab_env(void);
int			launch(char *intro, t_stack *node);
const char	*search_cmd(char *txt);
const char	*path_exe(char *txt);
int			accesible(const char *path);

//in_out
int			is_built(char *input);
int			fd_putstr_out(char *str, t_stack *node);
void		redirect_pipes(t_stack *node);
int			read_pipe(int fd, char *str); //deshuso
int			write_pipe(int fd, char *str); //deshuso

//main
void		clear(char **intro);
void		free_all_params(t_stack **stack, char **input, char ***tokens);

//parse
int			expand(char **txt);
int			expand2(char *txt);
char		*literal(char *input);
int			inside_open_quotes(char *input);
/*version 1*/
void		quote_in_or_out(char txt, int *count, int *flags);
//void		quote_d_count(char *txt, int *count);
void		remove_quote(char *txt, int init);
char		*search_vble_env(char *txt, int init);
char		*parse(char *txt);
int			OLD_quote_in_or_out(char *txt, int ini);
void		flag_check(int flag, int *flags);
char		*quote_in_or_out_loop(char *txt, int *count, int *flags);
char		*expand_loop(char *txt);
int			inside_simple(char *txt, int *flags, int *count, int *i);
int			inside_doble(char *txt, int *flags, int *count, int *i);

void		flip_flag(char *txt, int *flags, int *count, int i, int f);

/*version 2*/
char		*parsing(char *input);
char		*expand3(char *txt, int init, int end);
int			inside_open_quotes2(char *input);
int			outside_quotes(char *input);
char		**parse_split(char *input, char c);
int			count_words(char *str);
void		fill(char *str, char **word, int index);
void		malloc_split(char *entry, char **splited, int index);

//lexer
void		create_cmds(t_stack **node, char *token);
void		cmd_path(t_stack **node);
void		relative_path(t_stack *node);
void		exp_act_path(t_stack *node);
void		exp_up_path(t_stack *node);

//stack
t_stack		*pipe_stack(char *input);
t_stack		*create_node(char *txt);
void		insert_l_pipe(t_stack *node, t_stack *stack);
void		delete_all_nodes(t_stack *start);
void		free_node_content(t_stack *node);

int			str_cmp(char *str1, char *str2);

//reorder
int			exit_cmd_in_stack(t_stack *stack);
t_stack		*reorder_stack(t_stack *stack);
t_stack		*jump_to(t_stack *stack, int to);

//signals
void		sig_handler(int sig);
void		new_sig_handler();
void		restore_prompt_C(int sig);
void		restore_prompt_D(int sig);
void		ctrl_c(int sig);
void		back_slash(int sig);
void		handler_signal_zeta();
void		sig_int(int code);
void		sig_quit(int code);
void		sig_init(void);


//enviroment
void		set_envi(t_env **envi, char **env);
//t_env  *create_vble(char *envi);
//void    insert_env(t_env *envi, t_env *vble);
//void deleteEnviro(t_env *envi);

//lst_env
t_env		*ft_lstnew(char *name, char *val);
void		ft_lstadd_back(t_env **lst, t_env *new);
t_env		*ft_lstfind(t_env *lst, char *name);
void		ft_lstclear(t_env **lst);
void		ft_lstdelone(t_env *lst);
t_env		*ft_lstlast(t_env *lst);


//parse_utils
char		*get_env(char *vble);
char		*expand_vble(char *txt, int *init);
char		*expand_vble_out(char *txt, int *init);
char		*expand_vble_word(char *txt, int init);

//split_tokens
char	**split_tokens(char *txt);
char	**split_tokens_add(char *txt);
void	flag_change(char *txt, int *flags, int f);
char	**token_add(char **dst, const char *s,  size_t i, size_t len);
char	**str3add(char **s1, char *s2);
char	*split_tokens_simples(int *flags, char *txt, int *i);
char	*split_tokens_doubles(int *flags, char *txt, int *i);
char	*split_tokens_out(int *flags, char *txt, int *i);
char	*quote_erase(char *txt);
char	*expand_vble_tokens(char *txt, int *init);
char	*expand_vble_lines(char *txt, int init);

//split_lines
char	**split_lines(char *txt);
char	*split_lines_simples(int *flags, char *txt, int *i, int *d);
char	*split_lines_doubles(int *flags, char *txt, int *i, int *d);
char	*split_lines_out(char *txt, int *i, int *d);
void	flag_flop(int *flags, int *i, int f);
size_t	ft_strilcpy(char *dst, const char *src, int from, size_t dstsize);




//words
//int     opened_quotes(char *txt, int *count, int *flags);
char	**get_words(char *txt, int *count, int *flags);
char    **line_to_words(char *txt);
char	*expand_word(char *word);

//t_flag_split
int		cut_or_pass(char c, int *flag);
char	**ft_flag_split(char const *s, char c);
int		expand_or_not(char c, int *flag);
char	*ft_flag_expand(char *s);
char	*ft_flag_rm_quotes(char *word);
int		rm_or_not(char c, int *flag, int *count);

//redirect
void	redirections_stack(t_stack *stack);
void	redir_to(t_stack **node, int *i, char *input);
void	ft_redir_forward(t_stack *stack);
void	ft_redir_apend(t_stack *stack);
void	ft_redir_back(t_stack *stack);
void	ft_redir_heredoc(t_stack *stack);

//redirect_node
void	redir_node(t_stack *stack);
void	ft_redir_node_forward(t_stack *stack);
void	ft_redir_node_apend(t_stack *stack);
void	ft_redir_node_back(t_stack *stack);
void	ft_redir_node_heredoc(t_stack *stack);

//open_quotes
int     opened_quotes(char *txt, int *count, int *flags);
void	flop_flag(int *flags, int *count, int f);
void	quote_d_count(char *txt, int *count);
int		is_line_cut(char *txt, int *i);
//lines
char	**input_to_lines(char *txt);
void	inside_simple_quotes(char *txt, int *flags, int *i, int *j, char *temp_text);
void	inside_double_quotes(char *txt, int *flags, int *i, int *j, char *temp_text);
void	process_pipe(char *temp_text, char **lines, int *c_lines, int *j, int *i);
char	**get_lines(char *txt, int *flags);

#endif
