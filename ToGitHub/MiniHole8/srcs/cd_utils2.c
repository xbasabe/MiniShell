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

char	*active_dir(void)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
			return (env->val);
		env = env->next;
	}
	return (env->val);
}

void	home_dir(t_stack *node)
{
	t_env	*env;

	env = g_shell.env;
	node->pipe.arg = (char **)malloc(sizeof(char *) * 2);
	node->pipe.arg[1] = NULL;
	while (env)
	{
		if (str_cmp(env->name, "HOME") == 0)
		{
			node->pipe.arg[0] = env->val;
		}
		env = env->next;
	}
}

char	*old_dir(void)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, "OLDPWD") == 0)
			return (env->val);
		env = env->next;
	}
	return (env->val);
}

char	*last_slash(char *dir)
{
	int		i;
	char	*cut;

	i = ft_strlen(dir);
	if (dir[i - 1] == '/')
	{
		cut = (char *)malloc(sizeof(char) * i + 2);
		ft_strncpy(cut, dir, (i - 2));
		return (cut);
	}
	else
		return (dir);
}
