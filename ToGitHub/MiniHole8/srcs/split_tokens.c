/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:21:05 by xbasabe-          #+#    #+#             */
/*   Updated: 2024/02/17 02:11:26 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

static char	*search_value_env(char *txt, int *init);
char		*post_vble(char *txt, int i);
char		*pre_vble(char *prev, char *txt, int *i);

char	*quote_erase(char *txt)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = (char *)malloc(sizeof(char) * 99);
	while (txt[i])
	{
		if (txt[i] == '\'' || txt[i] == '"')
			i++;
		temp[j] = txt[i];
		i++;
		j++;
	}
	return (temp);
}

char	*expand_vble_lines(char *txt, int init)
{
	char	*value;
	int		i;
	char	*prev;
	char	*temp;

	i = 0;
	prev = NULL;
	prev = pre_vble(prev, txt, &i);
	if ((int)ft_strlen(txt) == i)
		return (prev);
	value = search_value_env(txt, &i);
	printf("prev %s\n", prev);
	temp = ft_strjoin(prev, value);
	printf("temp %s\n", temp);
	if (temp == NULL)
		return (txt);
	if (txt[i] == '\0')
		return (temp);
	i = i + init;
	free(prev);
	prev = ft_strjoin(temp, post_vble(txt, i));
	free(temp);
	return (prev);
}

char	*pre_vble(char *prev, char *txt, int *i)
{
	int	flag[2];

	flag[0] = 1;
	flag[1] = 1;
	while (expand_or_not(txt[(*i)], flag) == 0)
		(*i)++;
	prev = (char *)malloc(sizeof(char) * ((*i) + 2));
	ft_strlcpy(prev, txt, (*i) + 1);
	return (prev);
}

char	*post_vble(char *txt, int i)
{
	int		j;
	char	*post;

	j = 0;
	post = (char *)malloc(sizeof(char) * 999);
	i--;
	while (txt[++i] != '\0')
	{
		post[j] = txt[i];
		j++;
	}
	post[j] = '\0';
	ft_strilcpy(post, txt, i, j);
	return (post);
}

static char	*search_value_env(char *txt, int *init)
{
	int		j;
	char	vble[999];

	(*init)++;
	j = 0;
	while (txt[*init] != ' ' && txt[*init] != '\0'
		&& txt[*init] != '"' && txt[*init] != '\'' && txt[*init] != '$')
	{
		vble[j] = txt[*init];
		j++;
		(*init)++;
	}
	vble[j] = '\0';
	if (str_cmp(vble, "?") == 0)
	{
		return (ft_itoa(g_shell.num_quit));
	}
	return (get_env(vble));
}
