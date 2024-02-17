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

void	get_path(t_stack **node, int *i);

void	create_cmds(t_stack **node, char *token)
{
	char	**words;
	int		i;
	int		len;

	words = ft_flag_split(token, ' ');
	len = ft_str2len(words);
	(*node)->pipe.arg = (char **)malloc(sizeof(char *) * (len + 1));
	if (!((*node)->pipe.arg))
		return ;
	words[0] = ft_flag_expand(words[0]);
	words[0] = ft_flag_rm_quotes(words[0]);
	(*node)->pipe.cmd = ft_strdup(words[0]);
	i = 1;
	while (words[i])
	{
		words[i] = ft_flag_expand(words[i]);
		words[i] = ft_flag_rm_quotes(words[i]);
		(*node)->pipe.arg[i - 1] = ft_strdup(words[i]);
		i++;
	}
	(*node)->pipe.arg[i - 1] = NULL;
	cmd_path(node);
	clear(words);
}

void	cmd_path(t_stack **node)
{
	char	comand[999];
	int		i;
	int		c;

	get_path(node, &i);
	c = 0;
	while ((*node)->pipe.cmd[i] != '\0')
	{
		comand[c] = (*node)->pipe.cmd[i];
		i++;
		c++;
	}
	comand[c] = '\0';
	ft_strcpy((*node)->pipe.cmd, comand);
}

void	get_path(t_stack **node, int *i)
{
	char	ruta[999];
	int		c;

	(*i) = ft_strlen((*node)->pipe.cmd);
	c = 0;
	while (--(*i) >= 0)
	{
		if ((*node)->pipe.cmd[(*i)] == '/')
			c++;
	}
	(*i) = 0;
	while (c > 0)
	{
		if ((*node)->pipe.cmd[(*i)] == '/')
			c--;
		ruta[(*i)] = (*node)->pipe.cmd[(*i)];
		(*i)++;
	}
	ruta[(*i)] = '\0';
	(*node)->pipe.ext_path = ruta;
	if (ruta[0] != '\0')
		relative_path(*node);
}
