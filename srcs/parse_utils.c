/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:54:39 by xbasabe-         #+#    #+#             */
/*   Updated: 2022/12/09 00:08:29 by nlibano-         ###   ########.fr       */
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
	char 	*value; //valor que tiene la vble tras el $
	char 	exp[999]; //el nuevo txt expandido
	int		i;
	int		j;
	int		add;

	i = 0;
	add = *init;
	while (txt[add] != ' ' && txt[add] != '\0' && txt[add] != '"') //&& txt[add] != '\'')
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
	//exp[j + 1] = '\0';
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
	char	*value; //valor que tiene la vble tras el $
	char	exp[999]; //el nuevo txt expandido
	int		i;
	int		j;
	int		add;

	i = 0;
	add = *init;
	while (txt[add] != ' ' && txt[add] != '\0' && txt[add] != '"') //&& txt[add] != '\'')
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

char *OLD_expand_vble(char *txt, int *init)
{
	char *value; //valor que tiene la vble tras el $
	char exp[999]; //el nuevo txt expandido
	int		i;
	int		j;
	int		add;

	i = 0;
	add = *init;
	while (txt[add] != ' ' && txt[add] != '\0' && txt[add] != '"' && txt[add] != '\'')
		add++;
	add = add - *init;
	value = search_vble_env(txt, *init);
	j = 0;
	ft_strncpy(exp, txt, *init);
	if(value != NULL)
	{
		while(value[j])
		{
			exp[*init + j] = value[j];
			j++;
		}
	}
	j = j + *init;
	exp[j] = ' '; //problema!!
	exp[j + 1] = '\0';
	j++;
	i = *init + add;
	while(txt[i])
	{
		i++;
		exp[j] = txt[i];
		j++;
	}
	exp[j] = '\0';
	txt = exp;
	return(txt);
}
