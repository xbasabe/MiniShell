/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:03:32 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/08 02:50:05 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	relative_path(t_stack *node)
{
	if (node->pipe.ext_path[0] == '.' && node->pipe.ext_path[1] == '/')
		exp_act_path(node);
	if (node->pipe.ext_path[0] == '.'
		&& node->pipe.ext_path[1] == '.' && node->pipe.ext_path[2] == '/')
		exp_up_path(node);
}

void	exp_act_path(t_stack *node)
{
	char	*exp_dir;

	exp_dir = active_dir();
	node->pipe.ext_path++;
	exp_dir = stradd(exp_dir, node->pipe.ext_path);
	node->pipe.ext_path = exp_dir;
}

void	exp_up_path(t_stack *node)
{
	char	*exp_dir;
	char	*tmp;
	int		i;

	exp_dir = active_dir();
	i = ft_strlen(exp_dir);
	while (exp_dir[i] != '/')
		i--;
	tmp = (char *)malloc(sizeof(char) * (i + 2));
	tmp[i + 1] = '\0';
	while (i >= 0)
	{
		tmp[i] = exp_dir[i];
		i--;
	}
	node->pipe.ext_path++;
	node->pipe.ext_path++;
	node->pipe.ext_path++;
	exp_dir = tmp;
	exp_dir = stradd(exp_dir, node->pipe.ext_path);
	node->pipe.cmd = exp_dir;
	free(tmp);
}
