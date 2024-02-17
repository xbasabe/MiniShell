/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:00:11 by xbasabe-          #+#    #+#             */
/*   Updated: 2024/02/16 20:00:11 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_back(t_stack *stack);
int	open_heredoc(t_stack *stack);
int	open_write(t_stack *stack);

int	open_write(t_stack *stack)
{
	t_stack	*tmp;
	int		fd;
	char	*path;
	t_env	*env;

	tmp = stack;
	env = g_shell.env;
	path = NULL;
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
		{
			path = (char *)malloc(sizeof(char) * strlen(env->val));
			path = env->val;
			break ;
		}
		env = env->next;
	}
	path = ft_strjoin(path, "/");
	path = ft_strjoin(path, tmp->next->pipe.cmd);
	if (tmp->next->pipe.redir == 'a')
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (tmp->next->pipe.redir == 'f')
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	return (fd);
}

int	open_write_pipe(t_stack *stack)
{
	t_stack	*tmp;
	int		fd;
	char	*path;
	t_env	*env;

	tmp = stack;
	env = g_shell.env;
	path = NULL;
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
		{
			path = (char *)malloc(sizeof(char) * strlen(env->val));
			path = env->val;
			break ;
		}
		env = env->next;
	}
	path = ft_strjoin(path, "/");
	path = ft_strjoin(path, "aux_file_pipe.txt");
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRWXU);
	return (fd);
}

int	open_read_pipe(t_stack *stack)
{
	t_stack	*tmp;
	int		fd;
	char	*path;
	t_env	*env;

	tmp = stack;
	env = g_shell.env;
	path = NULL;
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
		{
			path = (char *)malloc(sizeof(char) * strlen(env->val));
			path = env->val;
			break ;
		}
		env = env->next;
	}
	path = ft_strjoin(path, "/");
	path = ft_strjoin(path, "aux_file_pipe.txt");
	fd = open(path, O_RDONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRWXU);
	return (fd);
}

int	open_heredoc(t_stack *stack)
{
	t_stack	*tmp;
	char	*path;
	char	*txt;
	char	*limit;
	int		fd;

	tmp = stack;
	path = NULL;
	txt = NULL;
	limit = tmp->next->pipe.cmd;
	fd = open("./heredoc.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	while (1)
	{
		txt = readline("heredoc$> ");
		if (strcmp(txt, limit) == 0)
			break ;
		write(fd, txt, sizeof(char) * ft_strlen(txt));
		write(fd, "\n", 1);
	}
	return (fd);
}

int	open_back(t_stack *stack)
{
	t_stack	*tmp;
	int		fd;
	char	*path;
	t_env	*env;

	tmp = stack;
	env = g_shell.env;
	path = NULL;
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
		{
			path = (char *)malloc(sizeof(char) * strlen(env->val));
			path = env->val;
			break ;
		}
		env = env->next;
	}
	path = ft_strjoin(path, "/");
	path = ft_strjoin(path, tmp->next->pipe.cmd);
	fd = open(path, O_RDONLY, S_IRWXU);
	if (fd < 0)
		fd_putstr_out("Minishell: No such file or directory", tmp);
	return (fd);
}
