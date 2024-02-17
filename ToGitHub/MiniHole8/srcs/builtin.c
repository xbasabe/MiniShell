/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:40:03 by marvin            #+#    #+#             */
/*   Updated: 2022/12/09 01:41:10 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_stack *node, char *input)
{
	int		i;
	int		n;

	(void)input;
	i = 0;
	n = 0;
	if (node->pipe.arg[0] == NULL)
	{
		fd_putstr_out("\n", node);
		return (0);
	}
	if (strcmp(node->pipe.arg[0], "-n") == 0)
	{
		n = 1;
		i++;
	}
	while (node->pipe.arg[i])
	{
		fd_putstr_out(node->pipe.arg[i], node);
		fd_putstr_out(" ", node);
		i++;
	}
	if (n == 0)
		fd_putstr_out("\n", node);
	return (0);
}

void	env(t_stack *node)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		fd_putstr_out(env->name, node);
		fd_putstr_out("=", node);
		fd_putstr_out(env->val, node);
		fd_putstr_out("\n", node);
		env = env->next;
	}
}

void	pwd(t_stack *node)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
		{
			fd_putstr_out(env->val, node);
			fd_putstr_out("\n", node);
			break ;
		}
		env = env->next;
	}
}

void	unset(t_stack *node)
{
	t_env	*env;
	t_env	*tmp;
	t_env	*head;
	t_env	*aux;

	env = g_shell.env;
	tmp = ft_lstnew(env->name, env->val);
	head = tmp;
	if (node->pipe.cmd != NULL)
	{
		while (env->next != NULL)
		{
			if (str_cmp(env->next->name, node->pipe.arg[0]) == 0)
				env = env->next->next;
			env = env->next;
			aux = ft_lstnew(env->name, env->val);
			ft_lstadd_back(&tmp, aux);
			tmp = tmp->next;
		}
	}
	g_shell.env = head;
	return ;
}

void	exit_kill(t_stack *node)
{
	if (node->pipe.cmd != NULL)
		g_shell.num_quit = (int)node->pipe.cmd;
	else
		g_shell.num_quit = 0;
	delete_all_nodes(node);
	exit(g_shell.num_quit);
}
