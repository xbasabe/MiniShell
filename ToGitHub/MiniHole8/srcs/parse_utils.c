/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:47:37 by xbasabe-          #+#    #+#             */
/*   Updated: 2024/02/16 14:47:37 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *vble)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, vble) == 0)
		{
			return (env->val);
		}
		env = env->next;
	}
	return (NULL);
}

char	*expand_vble_out(char *txt, int *init)
{
	char	*value;
	char	exp[999];
	int		i;
	int		j;
	int		add;

	i = 0;
	add = *init;
	while (txt[add] != ' ' && txt[add] != '\0' && txt[add] != '"')
		add++;
	add = add - *init;
	value = search_vble_env(txt, *init);
	j = 0;
	ft_strncpy(exp, txt, *init);
	if (value != NULL)
	{
		while (value[j])
		{
			exp[*init + j] = value[j];
			j++;
		}
	}
	j = j + *init;
	i = *init + add;
	*init = j - 2;
	exp[j] = '\0';
	j++;
	while (txt[i])
	{
		i++;
		exp[j] = txt[i];
		j++;
	}
	exp[j] = '\0';
	txt = exp;
	return (txt);
}

char	*expand_vble(char *txt, int *init)
{
	char	*value;
	char	exp[999];
	int		i;
	int		j;
	int		add;

	i = 0;
	add = *init;
	while (txt[add] != ' ' && txt[add] != '\0' && txt[add] != '"')
		add++;
	add = add - *init;
	value = search_vble_env(txt, *init);
	j = 0;
	ft_strncpy(exp, txt, *init);
	if (value != NULL)
	{
		while (value[j])
		{
			exp[*init + j] = value[j];
			j++;
		}
	}
	j = j + *init;
	i = *init + add;
	*init = j - 1;
	exp[j] = '"';
	exp[j + 1] = '\0';
	j++;
	while (txt[i])
	{
		i++;
		exp[j] = txt[i];
		j++;
	}
	exp[j] = '\0';
	txt = exp;
	return (txt);
}
