/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_f_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:13:14 by xbasabe-          #+#    #+#             */
/*   Updated: 2024/02/16 15:13:14 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack	*to_end_of_stack(t_stack *stack);
int		open_back(t_stack *stack);
int		open_heredoc(t_stack *stack);
int		open_write(t_stack *stack);
t_stack	*back_redir_count(t_stack *tmp);

void	redir_stack_fb(t_stack *stack)
{
	t_stack	*tmp;
	t_stack	*tmp_back;

	tmp = stack;
	if (tmp->prev == NULL && tmp->next == NULL)
	{
		tmp->pipe.p[0] = 0;
		tmp->pipe.p[1] = 1;
		return ;
	}
	while (tmp != NULL)
	{
		redir_token_f(tmp);
		printf("Redir forward `%s' pipe[0] %d pipe[1] %d\n", tmp->pipe.cmd, tmp->pipe.p[0], tmp->pipe.p[1]);
		tmp_back = tmp;
		tmp = tmp->next;
	}
	if (tmp_back->pipe.redir == 'b' || tmp_back->pipe.redir == 'h' || tmp_back->pipe.redir == 'p')
	{
		tmp_back->pipe.p[1] = 1;
	}
	while (tmp_back != NULL)
	{
		redir_token_b(tmp_back);
		printf("Redir back '%s' pipe[0] %d pipe[1] %d\n", tmp_back->pipe.cmd, tmp_back->pipe.p[0], tmp_back->pipe.p[1]);
		tmp_back = tmp_back->prev;
	}
}

void	redir_token_b(t_stack *stack)
{
	t_stack	*tmp;
	int		fd;
	t_stack	*countb;

	tmp = stack;
	fd = -1;
	countb = 0;
	if (tmp != NULL)
	{
		if (tmp->pipe.redir == 'b' || tmp->pipe.redir == 'h')
		{
			if (tmp->prev->pipe.redir == 'b' || tmp->prev->pipe.redir == 'h')
			{
				tmp->prev->pipe.p[1] = tmp->pipe.p[1];
			}
			else
			{
				tmp->prev->pipe.p[0] = tmp->pipe.p[1];
				countb = back_redir_count(tmp);
				if (countb->next == NULL)
				{
					tmp->prev->pipe.p[1] = 1;
				}
				else
				{
					countb->next->pipe.p[0] = tmp->prev->pipe.p[1];
				}
			}
		}
		else if (tmp->pipe.redir == 'f' || tmp->pipe.redir == 'a')
		{
			if (tmp->prev->pipe.redir == 'f' || tmp->prev->pipe.redir == 'a')
			{
				tmp->prev->pipe.p[0] = tmp->pipe.p[0];
			}
			else
			{
				tmp->prev->pipe.p[1] = tmp->pipe.p[0];
			}
		}
		else if (tmp->pipe.redir == 'p')
		{
			fd = open_read_pipe(tmp);
			tmp->pipe.p[0] = fd;
		}
		//else if (tmp->next== NULL && (tmp->pipe.redir == 'b' || tmp->pipe.redir == 'h'|| tmp->pipe.redir == 'p'))
		else if (tmp->prev == NULL && (tmp->pipe.redir != 'b' || tmp->pipe.redir != 'h'))
		{
			tmp->pipe.p[0] = 0;
		}
	}
}

t_stack	*redir_token_f(t_stack *stack)
{
	t_stack	*tmp;
	int		fd;

	tmp = stack;
	fd = -1;
	//if(tmp->pipe.redir == 'o') //¿quitar? wc
	//{
	//	close(tmp->pipe.p[0]);
	//	tmp->pipe.p[0] = 0;
	//}
	if (tmp->next != NULL)
	{
		if (tmp->next->pipe.redir == 'f' || tmp->next->pipe.redir == 'a')
		{
			fd = open_write(tmp);
			tmp->pipe.p[1] = fd;
			tmp->next->pipe.p[0] = fd;
		}
		if (tmp->next->pipe.redir == 'p') //cerrar y abrir. segun el lado del pipe
		{
			fd = open_write_pipe(tmp);
			tmp->pipe.p[1] = fd;
		}
		else if (tmp->next->pipe.redir == 'b')
		{
			fd = open_back(tmp);
			tmp->pipe.p[0] = fd;
			tmp->next->pipe.p[1] = fd;
		}
		else if (tmp->next->pipe.redir == 'h') //cerrar y abrir para que la lectura no deje bloqueado el fichero
		{
			fd = open_heredoc(tmp);
			tmp->pipe.p[0] = fd;
			tmp->next->pipe.p[1] = fd;
		}
		else if (tmp->next->next == NULL)
		//else if (tmp->next->next== NULL && (tmp->next->pipe.redir == 'b' || tmp->next->pipe.redir == 'h'|| tmp->next->pipe.redir == 'p'))
			tmp->next->pipe.p[1] = 1;
	}
	return (tmp);
}

t_stack	*back_redir_count(t_stack *tmp)
{
	t_stack	*tp;

	tp = tmp;
	while (tp->next != NULL && (tp->next->pipe.redir == 'b' || tp->next->pipe.redir == 'h' ))
		tp = tp->next;
	return (tp);
}
