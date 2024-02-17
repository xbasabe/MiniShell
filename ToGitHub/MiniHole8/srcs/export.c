/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:15:56 by marvin            #+#    #+#             */
/*   Updated: 2022/12/08 17:55:50 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_no_args(t_stack *node)
{
	int		i;
	char	**sort;
	char	**split;

	sort = sort_env();
	i = -1;
	while (sort[++i])
	{
		split = ft_split(sort[i], '=');
		fd_putstr_out("declare -x ", node);
		fd_putstr_out(split[0], node);
		fd_putstr_out("=\"", node);
		fd_putstr_out(split[1], node);
		fd_putstr_out("\"", node);
		fd_putstr_out("\n", node);
		clear (split);
	}
}

void	export(t_stack *node)
{
	int		exist;
	char	**var;
	t_env	*env;
	int		i;

	i = 0;
	if (!node->pipe.arg[0])
		return (export_no_args(node));
	export_check_arg(node);
	exist = 0;
	env = g_shell.env;
	while (node->pipe.arg[i])
	{
		var = ft_split(node->pipe.arg[i], '=');
		env_iterate(env, var, &exist);
		if (exist == 0)
			export_add(node->pipe.arg[i]);
		i++;
	}
	clear(var);
	return ;
}
