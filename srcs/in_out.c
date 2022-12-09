/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:05:17 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/02 01:29:12 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_putstr_out(char *str, t_stack *node)
{
	if (node->next == NULL)
	{
		//i = 0;
		//while(str[i])
		//{
		//	write(1, &str[i], 1);
		//	i++;
		//}
		write(1, str, sizeof(char) * ft_strlen(str));
		return (1);
	}
	else if (node->next != NULL)
	{
		//i = 0;
		//while(str[i])
		//{
		//	write(node->next->pipe.p[1], &str[i], 1);
		//	i++;
		//}
		write(node->next->pipe.p[1], str, sizeof(char) * ft_strlen(str));
		return (2);
	}
	return (0);
}

void    redirect_pipes(t_stack *stack) //reformular la funcion para cambiar orden del stack si tenemos < 0 >
{
	t_stack *node;

	node = stack;
	if (node->next == NULL)
		return ;
	//node = node->next;
	while (node->next != NULL)
	{	
		if (node->next != NULL) // send stdout to the pipe to next comand
			dup2(node->next->pipe.p[1],1);
		if(node->prev != NULL)  //entrada debe ser lo leido del pipe anterio
			dup2(node->pipe.p[0], 0);
		node = node->next;
	}
}
