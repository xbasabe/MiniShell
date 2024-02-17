/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exebash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:33:24 by xbasabe-          #+#    #+#             */
/*   Updated: 2024/02/16 20:45:23 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_in_child(char *input, t_stack *stack)
{
	t_stack	*node;

	node = stack;
	if (node->prev != NULL && node->pipe.redir == 'p')
		close(node->prev->pipe.p[1]);
	dup2(node->pipe.p[0], STDIN_FILENO);
	dup2(node->pipe.p[1], STDOUT_FILENO);
	if (is_built(node->pipe.cmd) == 0)
		exit(0);
	if (is_built(node->pipe.cmd) == 1)
	{
		if (launch(input, node) == -1)
		{
			fd_putstr_out("-Minishell: ", node);
			fd_putstr_out(node->pipe.cmd, node);
			fd_putstr_out(": command not found\n", node);
			g_shell.num_quit = 127;
			exit(127);
		}
	}
	dup2(0, STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
}

pid_t	child_launch(char *input, t_stack *stack)
{
	pid_t	ch_pid;
	t_stack	*node;

	node = stack;
	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (ch_pid == 0)
	{
		g_shell.pid = getpid();
		exec_in_child(input, stack);
	}
	if (ch_pid > 0)
	{
		g_shell.pid = getpid();
		if (is_built(node->pipe.cmd) == 0)
			exec_built_in(input, node);
	}
	wait(NULL);
	if (g_shell.num_quit == 32512)
		g_shell.num_quit = 127;
	return (ch_pid);
}

void	exec_stack(t_stack *stack, char *input)
{
	t_stack	*tmp;

	tmp = stack;
	while (tmp != NULL)
	{
		if (tmp->pipe.redir == 'f' || tmp->pipe.redir == 'a'
			|| tmp->pipe.redir == '|'
			|| tmp->pipe.redir == 'h' || tmp->pipe.redir == 'b')
		{
			tmp = tmp->next;
			continue ;
		}
		else
			child_launch(input, tmp);
		if (tmp == NULL)
			break ;
		tmp = tmp->next;
	}
}

int	is_built(char *cmd)
{
	int	r;

	cmd = lowercase(cmd);
	r = 1;
	if (str_cmp(cmd, "pwd") == 0)
		r = 0;
	else if (str_cmp(cmd, "echo") == 0)
		r = 0;
	else if (str_cmp(cmd, "cd") == 0)
		r = 0;
	else if (str_cmp(cmd, "export") == 0)
		r = 0;
	else if (str_cmp(cmd, "unset") == 0)
		r = 0;
	else if (str_cmp(cmd, "env") == 0)
		r = 0;
	else if (str_cmp(cmd, "exit") == 0)
		r = 0;
	return (r);
}

int	exec_built_in(char *input, t_stack *node)
{
	if (str_cmp(node->pipe.cmd, "echo") == 0)
		echo(node, input);
	else if (str_cmp(node->pipe.cmd, "pwd") == 0)
		pwd(node);
	else if (str_cmp(node->pipe.cmd, "cd") == 0)
		cd(node);
	else if (str_cmp(node->pipe.cmd, "export") == 0)
		export(node);
	else if (str_cmp(node->pipe.cmd, "unset") == 0)
		unset(node);
	else if (str_cmp(node->pipe.cmd, "env") == 0)
		env(node);
	else if (str_cmp(node->pipe.cmd, "exit") == 0)
		exit_kill(node);
	g_shell.num_quit = 0;
	return (0);
}
