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

int	expand(char **txt)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (txt[i])
	{
		if (txt[i][0] == '$')
		{
			while (txt[i][j])
			{
				txt[i][j - 1] = txt[i][j];
				j++;
			}
			txt[i][j - 1] = '\0';
			txt[i] = getenv(txt[i]);
			if (!txt[i])
				return (1);
			j = 1;
		}
		i++;
	}
	return (0);
}

int	expand2(char *txt)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (txt[0] == '$')
	{
		while (txt[i])
		{
			txt[i - 1] = txt[i];
			j++;
		}
		txt[i - 1] = '\0';
		printf("txt '%s'", txt);
		txt = getenv(txt);
		if (!txt[i])
			return (1);
		i++;
	}
	return (0);
}

char	*search_vble_env(char *txt, int init)
{
	int		j;
	char	vble[999];

	init++;
	j = 0;
	while (txt[init] != ' ' && txt[init] != '\0'
		&& txt[init] != '"' && txt[init] != '\'')
	{
		vble[j] = txt[init];
		j++;
		init++;
	}
	vble[j] = '\0';
	if (str_cmp(vble, "?") == 0)
	{
		return (ft_itoa(g_shell.num_quit));
	}
	return (get_env(vble));
}

void	flip_flag(int *flags, int *count, int i, int f)
{
	int	init;

	init = i;
	flags[f] = flags[f] * -1;
	count[f]--;
}
