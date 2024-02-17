/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:42:42 by xbasabe-          #+#    #+#             */
/*   Updated: 2024/02/16 19:54:11 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	quote_d_count(char *txt, int *count)
{
	int	i;

	i = 0;
	while (txt[i] != '\0')
	{
		if (txt[i] == '"')
			count[1]++;
		else if (txt[i] == 39)
			count[0]++;
		i++;
	}
}

int	is_line_cut(char *txt, int *i)
{
	char	c;
	char	next;

	c = txt[*i];
	if (txt[*i + 1])
		next = txt[*i + 1];
	if (c == '|')
		return (0);
	if (c == '<' && next != '<')
		return (0);
	if (c == '>' && next != '>')
		return (0);
	else if (c == '<' && next == '<')
	{
		*i = *i + 1;
		return (0);
	}
	else if (c == '>' && next == '>')
	{
		*i = *i + 1;
		return (0);
	}
	return (1);
}
