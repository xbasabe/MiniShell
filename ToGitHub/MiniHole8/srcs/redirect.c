/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:08:57 by xbasabe-          #+#    #+#             */
/*   Updated: 2024/02/16 20:08:57 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_loop(t_stack *temp, int count, int *i, char *input);

int	redir_to_sub(t_stack *temp, int count, int *i, char option)
{
	temp->pipe.redir = option;
	(count)++;
	if (*i == count)
		return (1);
	return (0);
}

void	redir_to(t_stack **node, int *i, char *input)
{
	t_stack	*temp;
	int		j;
	int		count;

	temp = *node;
	j = 0;
	count = 0;
	if (redir_loop(temp, count, i, input) == 1)
		return ;
	return ;
}

int	redir_loop(t_stack *temp, int count, int *i, char *input)
{
	char	next;
	int		j;

	j = 0;
	while (input[j])
	{
		if (input[j + 1])
			next = input[j + 1];
		if (input[j] == '|')
			return (redir_to_sub(temp, count, i, 'p'));
		else if (input[j] == '<' && next != '<')
			return (redir_to_sub(temp, count, i, 'b'));
		else if (input[j] == '>' && next != '>')
			return (redir_to_sub(temp, count, i, 'f'));
		else if (input[j] == '<' && next == '<')
			return (redir_to_sub(temp, count, i, 'h'));
		else if (input[j] == '>' && next == '>')
			return (redir_to_sub(temp, count, i, 'a'));
		j++;
	}
	return (0);
}
