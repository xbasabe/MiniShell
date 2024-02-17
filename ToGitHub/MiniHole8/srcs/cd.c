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

int	init_cd(t_stack *node)
{
	if (node->pipe.arg[0] == NULL)
	{
		home_dir(node);
		return (0);
	}
	else if (node->pipe.arg[1] != NULL)
	{
		fd_putstr_out("-Minishell: cd: too many arguments\n", node);
		g_shell.num_quit = 1;
		return (1);
	}
	else if (node->pipe.arg[0])
	{
		if (node->pipe.arg[0][0] == '.' && node->pipe.arg[0][1] == '/')
			expand_relative(node);
		if (node->pipe.arg[0][0] == '.' && node->pipe.arg[0][1] == '.'
			&& node->pipe.arg[0][2] == '/')
			expand_relative2(node);
		if (strcmp(node->pipe.arg[0], "-") == 0 && !node->pipe.arg[1])
			node->pipe.arg[0] = old_dir();
		if (node->pipe.arg[0][0] == '.' && node->pipe.arg[0][1] == '\0')
			return (1);
		if (node->pipe.arg[0][0] == '.' && node->pipe.arg[0][1] == '.'
			&& node->pipe.arg[0][2] == '\0')
			expand_parent(node);
	}
	node->pipe.arg[0] = last_slash(node->pipe.arg[0]);
	return (0);
}

void	update_pwd(t_stack *node)
{
	t_env	*env;
	t_env	*tmp;
	t_env	*head;
	t_env	*aux;

	env = g_shell.env;
	tmp = ft_lstnew(env->name, env->val);
	env = env->next;
	head = tmp;
	printf("a updatepwd entra %s\n", node->pipe.arg[0]);
	while (env != NULL)
	{
		if (str_cmp(env->name, "PWD") == 0)
		{
			if (str_cmp(node->pipe.arg[0], stradd(get_env("HOME"), "/")) == 0)
			{
				aux = ft_lstnew(env->name, last_slash(node->pipe.arg[0]));
			}
			else
				aux = ft_lstnew(env->name, last_slash(expand_update(node->pipe.arg[0])));
			ft_lstadd_back(&tmp, aux);
		}
		else if (str_cmp(env->name, "PWD") != 0)
		{
			aux = ft_lstnew(env->name, env->val);
			ft_lstadd_back(&tmp, aux);
		}
		env = env->next;
		tmp = tmp->next;
	}
	g_shell.env = head;
}

int	update_chdir(t_stack *node)
{
	t_env	*env;

	env = g_shell.env;
	node->pipe.arg[0] = stradd(node->pipe.arg[0], "/");
	if (access((const char *)node->pipe.arg[0], F_OK) == -1)
	{
		printf("-Minishell: cd: %s: No such file or directory\n", node->pipe.arg[0]);
		g_shell.num_quit = 1;
		return (1);
	}
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
		{
			chdir((const char *)node->pipe.arg[0]);
			break ;
		}
		env = env->next;
	}
	return (0);
}

void	update_oldpwd(char *old_dir)
{
	t_env	*env;
	t_env	*tmp;
	t_env	*head;
	t_env	*aux;

	env = g_shell.env;
	tmp = ft_lstnew(env->name, env->val);
	env = env->next;
	head = tmp;
	while (env != NULL)
	{
		if (str_cmp(env->name, "OLDPWD") == 0)
		{
			aux = ft_lstnew(env->name, old_dir);
			ft_lstadd_back(&tmp, aux);
		}
		else if (str_cmp(env->name, "OLDPWD") != 0)
		{
			aux = ft_lstnew(env->name, env->val);
			ft_lstadd_back(&tmp, aux);
		}
		env = env->next;
		tmp = tmp->next;
	}
	g_shell.env = head;
}

void	cd(t_stack *node)
{
	t_env	*env;
	char	*old_dir;

	env = g_shell.env;
	old_dir = NULL;
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
		{
			old_dir = ft_strdup(env->val);
			break ;
		}
		env = env->next;
	}
	if (init_cd(node) == 0)
	{
		if (update_chdir(node) == 0)
			update_pwd(node);
	}
	update_oldpwd(old_dir);
	if (old_dir)
		free(old_dir);
}
