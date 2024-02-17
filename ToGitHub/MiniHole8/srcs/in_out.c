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
		write(1, str, sizeof(char) * ft_strlen(str));
		return (1);
	}
	else if (node->next != NULL)
	{
		write(node->pipe.p[1], str, sizeof(char) * ft_strlen(str));
		return (2);
	}
	return (0);
}

int	fd_putstr(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
	return (i);
}
