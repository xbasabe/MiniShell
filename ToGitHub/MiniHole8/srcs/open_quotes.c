/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:42:42 by xbasabe-          #+#    #+#             */
/*   Updated: 2024/02/16 19:54:29 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int	quotes_sim(int *l_flags, int *l_count, char *txt, int *i);
int	quotes_dob(int *l_flags, int *l_count, char *txt, int *i);

void	flop_flag(int *flags, int *count, int f)
{
	flags[f] = flags[f] * -1;
	count[f]--;
}

int	opened_quotes(char *txt, int *count, int *flags)
{
	int		i;
	int		l_count[2];
	int		l_flags[2];

	l_count[0] = count[0];
	l_count[1] = count[1];
	l_flags[0] = flags[0];
	l_flags[1] = flags[1];
	i = 0;
	while (txt && txt[i] != '\0')
	{
		if (txt[i] == 39)
			return (quotes_sim(l_flags, l_count, txt, &i));
		else if (txt[i] == 34)
			return (quotes_dob(l_flags, l_count, txt, &i));
		else if (txt[i] == 39 || txt[i] == 34)
			return (0);
		else if (txt[i] == '\0')
			return (1);
		i++;
	}
	return (1);
}

int	quotes_sim(int *l_flags, int *l_count, char *txt, int *i)
{
	if (l_flags[0] == 1 && l_flags[1] == 1)
	{
		flop_flag(l_flags, l_count, 0);
		while (txt[++(*i)] != 39)
		{
			if (txt[(*i)] == '\0')
				return (0);
		}
		flop_flag(l_flags, l_count, 0);
	}
	return (1);
}

int	quotes_dob(int *l_flags, int *l_count, char *txt, int *i)
{
	if (l_flags[0] == 1 && l_flags[1] == 1)
	{
		flop_flag(l_flags, l_count, 1);
		while (txt[++(*i)] != 34)
		{
			if (txt[(*i)] == '\0')
				return (0);
		}
		flop_flag(l_flags, l_count, 1);
	}
	return (1);
}
