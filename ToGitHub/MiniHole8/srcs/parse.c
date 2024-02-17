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

char	*parse(char *txt)
{
	int	count[2];
	int	flags[2];

	count[0] = 0;
	count[1] = 0;
	flags[0] = 1;
	flags[1] = 1;
	quote_d_count(txt, count);
	if (opened_quotes(txt, count, flags) == 0)
	{
		return ("echo -Minishell: echo: opened quotes");
	}
	return (txt);
}

void	remove_quote(char *txt, int init)
{
	int	i;

	i = init + 1;
	while (txt[i])
	{
		txt[i -1] = txt[i];
		i++;
	}
	i--;
	txt[i] = '\0';
}

void	delete_quotes(char	**s)
{
	int	i;
	int	j;

	i = -1;
	while ((*s)[++i])
	{
		if ((*s)[i] == 34)
		{
			j = i - 1;
			while ((*s)[++j])
			{
				(*s)[j] = (*s)[j + 1];
				if ((*s)[j + 1] == '\0')
					break ;
			}
		}
	}
}
