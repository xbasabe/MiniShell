/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exebash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:33:24 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/13 17:32:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_in_child(char *input, t_stack *stack)
{
	t_stack	*node;

	node = stack;
	//redir_node(node);
	printf("To exec cmd %s pipe[0] %d pipe[1] %d\n", node->pipe.cmd, node->pipe.p[0], node->pipe.p[1]);
	printf("stdin: %d stdout %d\n", STDIN_FILENO, STDOUT_FILENO);
	if (is_built(node->pipe.cmd) == 0)
		exit(0); //close the process, it will be excecuted in the parent
	if (is_built(node->pipe.cmd) == 1)
	{
		//sig_handler(2);
		//signal(SIGTSTP, handler_signal_zeta);
		if (launch(input, node) == -1) //get path and launch execve. -1 = error
		{
			fd_putstr_out("-Minishell: ", node);
			fd_putstr_out(node->pipe.cmd, node);
			fd_putstr_out(": command not found\n", node);
			g_shell.num_quit = 127;
			exit(127);
		}
		printf("CUCU\n");
	}
	close(node->pipe.p[0]);
	close(node->pipe.p[1]);
	dup2(0, STDIN_FILENO); //0 sustituye a stdin para devolverle su valor original
	dup2(1, STDOUT_FILENO);
	printf("stdin: %d stdout %d\n", STDIN_FILENO, STDOUT_FILENO);
}

pid_t	child_launch(char *input, t_stack *stack)
{
	pid_t	ch_pid;
	t_stack *node;

	node = stack;
	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (ch_pid == 0) //HIJO
	{
		g_shell.pid = getpid();
		exec_in_child(input, stack);
	}
	if (ch_pid > 0) //PADRE
	{
		g_shell.pid = getpid();
		close(node->pipe.p[1]);
		if (is_built(node->pipe.cmd) == 0)
		{
			exec_built_in(input, node);
		}
		close(node->pipe.p[0]);
	}
	wait(NULL);
	//wait(&(g_shell.num_quit)); //meter la expresio que traduce la devuelto WEXITSTATUS (estado) con wait_pid g_shell es status
	//wait(0);
	if (g_shell.num_quit == 32512)
		g_shell.num_quit = 127;
	return (ch_pid);
}

void	exec_stack(t_stack *stack, char *input)
{
	t_stack	*tmp;
	int		i;

	tmp = stack;
	i = 0;
	//if (exit_cmd_in_stack(stack) > 0)
	//	tmp = reorder_stack(stack);
	while (tmp != NULL)
	{
		//si redireccionamos bien SÍ debe pasarse por el nodo para redireccionar. ¿is comand o file?
		if (tmp->pipe.redir == 'f' || tmp->pipe.redir == 'b' || tmp->pipe.redir == 'h' || tmp->pipe.redir == 'a')
		{
			if (tmp != NULL)
				tmp = tmp->next;
			if (tmp == NULL)
				break ;
		}
		redir_node(tmp);
		child_launch(input, tmp);
		tmp = tmp->next;
		i++;
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
	else if (str_cmp(cmd, "$?") == 0)
		r = 0;
	return (r);
}
