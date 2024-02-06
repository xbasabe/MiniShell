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

/*
char	*no_blancks(char *txt)
{
	int		i;
	int		j;
	char	*ret;

	ret = NULL;
	i = 0;
	j = 0;
	while (txt[i])
	{
		if (txt[i] == ' ')
		{
			while (txt[j] == ' ')
				j++;
			i = i + j;
		}
		j = 0;
		ret[i] = txt[i];
	}
	return (ret);
}
*/

void	create_cmds(t_stack **node, char *token)
{
	char	**words;
	int		i;

	printf("Linea a cortar en palabras: -%s-\n", token);
	words = ft_flag_split(token, ' ');
	(*node)->pipe.arg = (char **)malloc(sizeof(char *) * (ft_str2len(words)) + 1);
	if (!((*node)->pipe.arg))
		return ;
	(*node)->pipe.cmd = ft_strdup(words[0]);
	printf(" palabra fltsplit 0 %s\n",words[0]);
	i = 1;
	while (words[i])
	{
		if(words[i][0] == '$')
			//words[i] = expand_vble_lines(words[i], 0);
			words[i] = expand_vble_word(words[i], 0);
			printf(" palabra %d %s\n", i, words[i]);
		(*node)->pipe.arg[i - 1] = ft_strdup(words[i]);
		i++;
	}
	(*node)->pipe.arg[i - 1] = NULL;
	cmd_path(node);
	clear(words);
}

void	cmd_path(t_stack **node)
{
	char	ruta[999];
	char	comand[999];
	int		i;
	int		c;

	i = ft_strlen((*node)->pipe.cmd);
	c = 0;
	while (--i >= 0)
	{
		if ((*node)->pipe.cmd[i] == '/')
			c++;
	}
	i = 0;
	while (c > 0)
	{
		if ((*node)->pipe.cmd[i] == '/')
			c--;
		ruta[i] = (*node)->pipe.cmd[i];
		i++;
	}
	ruta[i] = '\0';
	(*node)->pipe.ext_path = ruta;
	if (ruta[0] != '\0')
		relative_path(*node);
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

void	relative_path(t_stack *node) //expandir una ruta relativa ../ o ./
{
	if (node->pipe.ext_path[0] == '.' && node->pipe.ext_path[1] == '/')
		exp_act_path(node);
	if (node->pipe.ext_path[0] == '.' && node->pipe.ext_path[1] == '.' && node->pipe.ext_path[2] == '/')
		exp_up_path(node);
}

void	exp_act_path(t_stack *node) //expandir path actuak ./
{
	char	*exp_dir;

	exp_dir = active_dir();
	node->pipe.ext_path++; //cambiar esto?
	exp_dir = stradd(exp_dir, node->pipe.ext_path);
	node->pipe.ext_path = exp_dir;
}

void	exp_up_path(t_stack *node) //expandir directorio arriba ../
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
