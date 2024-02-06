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
	return (stack);
}
/*
t_stack *swap_tokens(t_stack *stack)
{

}
*/
