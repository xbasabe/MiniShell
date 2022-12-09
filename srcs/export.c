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

char	**sort_env(void)
{
	char	**sort;
	char	*tmp;
	int		i;
	int		j;

	sort = tab_env();
	i = -1;
	while (sort[++i])
	{
		j = -1;
		while (sort[++j])
		if (ft_strncmp(sort[i], sort[j], ft_strlen(sort[i])) < 0)
		{
			tmp = sort[i];
			sort[i] = sort[j];
			sort[j] = tmp;
		}
	}
	return (sort);
}

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

void	export_add(char *vbl)
{
	t_env	*new;
	char	**vble;

	vble = ft_split(vbl, '=');
	new = ft_lstnew(vble[0], vble[1]);
	clear(vble);
    ft_lstadd_back(&(g_shell.env), new);
}

void	export(t_stack *node)
{
	int		exist;
	char	**var;
	t_env	*env;

	if (!node->pipe.arg[0])
	{
		export_no_args(node);
		return ;
	}
	//comprobra si hay más de un argumento? cada argumento de node se toma como una variable a trata por export while arg[i]
	var = ft_split(node->pipe.arg[0], '=');
	exist = 0;
	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, var[0]) == 0) 
		{
			free(env->val);
			env->val = ft_strdup((const char*)var[1]);
			exist = 1;
			break ;
		}
		env = env->next;
	}
	if (exist == 0)
		export_add(node->pipe.arg[0]);
	clear(var);
}
