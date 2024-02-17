/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:01:40 by xbasabe-          #+#    #+#             */
/*   Updated: 2024/02/16 15:01:40 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_relative(t_stack *node)
{
	char	*exp_dir;

	exp_dir = active_dir();
	node->pipe.arg[0]++;
	exp_dir = stradd(exp_dir, node->pipe.arg[0]);
	node->pipe.arg[0] = exp_dir;
}

char	*expand_update(char *dir)
{
	char	*exp_dir;

	if (dir[0] == '/')
		return (dir);
	exp_dir = active_dir();
	exp_dir = stradd(exp_dir, "/");
	exp_dir = stradd(exp_dir, dir);
	return (exp_dir);
}

void	expand_parent(t_stack *node)
{
	char	*exp_dir;

	exp_dir = active_dir();
	exp_dir = cut_dir(exp_dir);
	node->pipe.arg[0] = exp_dir;
}

void	expand_relative2(t_stack *node)
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
	node->pipe.arg[0]++;
	node->pipe.arg[0]++;
	node->pipe.arg[0]++;
	exp_dir = tmp;
	exp_dir = stradd(exp_dir, node->pipe.arg[0]);
	node->pipe.arg[0] = exp_dir;
}

char	*cut_dir(char *dir)
{
	int		i;
	char	*cut;

	i = ft_strlen(dir);
	cut = (char *)malloc(sizeof(char) * i);
	while (dir)
	{
		if (dir[i] == '/')
			break ;
		i--;
	}
	ft_strncpy(cut, dir, i);
	free(dir);
	return (cut);
}
