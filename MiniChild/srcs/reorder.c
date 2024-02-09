/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:54:17 by marvin            #+#    #+#             */
/*   Updated: 2022/12/12 11:10:44 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//static t_stack *swap_tokens(t_stack *stack);
//static t_stack *skip_tokens(t_stack *tmp);
//static t_stack *flop_tokens(t_stack *tmp);

static void swap_tokens(t_stack *stack);
static void skip_tokens(t_stack *tmp);
static void flop_tokens(t_stack *tmp, int i);


int	exit_cmd_in_stack(t_stack *stack)
{
	int		i;
	t_stack	*tmp;

	i = 0;
	tmp = stack;
	while (tmp->next != NULL)
	{
		if (str_cmp(tmp->pipe.cmd, "exit") == 0)
			return (i);
		i++;
		tmp = tmp->next;
	}
	return (0);
}

t_stack	*jump_to(t_stack *stack, int to)
{
	int		i;
	t_stack	*jump;

	i = 0;
	to++;
	jump = stack;
	while (i < to)
	{
		jump = jump->next;
		i++;
	}
	return (jump);
}

t_stack	*reorder_stack(t_stack *stack)
{
	int	i;

	i = exit_cmd_in_stack(stack);
	if (i != 0)
		return (jump_to(stack, i));
	swap_tokens(stack);
	return (stack);
}

//static t_stack *swap_tokens(t_stack *tmp) // para cambiar orden en redirecciones
static void swap_tokens(t_stack *stack)
{
	t_stack *tmp;
	t_stack *init;
	int i;

	i = 0;
	init = stack;
	tmp = stack;
	while (tmp->next != NULL)
	{
		//printf("Estamos en linea %d, con redir %c cmd %s arg %s\n", i, tmp->pipe.redir, tmp->pipe.cmd, tmp->pipe.arg[0]);
		if (tmp->next->pipe.redir == 'h' || tmp->next->pipe.redir == 'b') //  << <
			 flop_tokens(tmp, i);
		if (tmp->next->pipe.redir == 'f' || tmp->next->pipe.redir == 'a' ) // >  >> <
			skip_tokens(tmp);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while(init->next != NULL)
	{
		printf("Reordered %d, cmd %s\n", i, init->pipe.cmd);
		init = init->next;
		i++;
	}
}

//static t_stack *flop_tokens(t_stack *tmp)
static void flop_tokens(t_stack *tmp, int i)
{
	t_stack *a_p_prev;
	t_stack *a_p_next;
	t_stack *a_t_prev;
	t_stack	*a_t_next;
	//t_stack	*anterio;
	//t_stack	*posterior;

	a_p_prev = NULL;
	a_p_next = NULL;
	a_t_prev = NULL;
	a_t_next = NULL;
	//anterio = NULL;
	//posterior = NULL;

	//guardar los punteros
	if(i > 0)
		a_p_prev = tmp->prev->prev;
	a_p_next = tmp->prev->next;
	a_t_prev = tmp->prev;
	if(tmp->next)
		a_t_next = tmp->next;

	//reasignar punteros
	tmp->prev->prev = a_t_prev;
	tmp->prev->next = a_t_next;
	tmp->prev = a_p_prev;
	tmp->next = a_p_next;	
}



//static t_stack *skip_tokens(t_stack *tmp)
static void skip_tokens(t_stack *tmp)
{
	printf("SKIP\n");
	//tmp->prev->pipe.arg[0] = tmp->pipe.cmd;
	tmp = tmp->next;
	//free token
}
