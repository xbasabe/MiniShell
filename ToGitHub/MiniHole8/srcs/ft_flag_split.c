/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:26:08 by xbasabe-          #+#    #+#             */
/*   Updated: 2024/02/16 13:26:08 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_flag_get_split_size(char const *s, char c)
{
	size_t	count;
	int		flag[2];

	flag[0] = 1;
	flag[1] = 1;
	count = 0;
	while (*s && s++)
	{
		while (cut_or_pass(*s, flag) == 0 && *s)
			s++;
		count++;
		while (*s == c && *s)
			s++;
	}
	return (count);
}

static char	**ft_flag_split_add(const char *s, char **dst, size_t i, size_t len)
{
	dst[i] = (char *)malloc(sizeof(char) * len + 1);
	if (!dst[i])
	{
		while (i)
			free (dst[--i]);
		free(dst);
		return (NULL);
	}
	ft_strlcpy(dst[i], s - len, len + 1);
	return (dst);
}

char	**ft_flag_split(char const *s, char c)
{
	char	**dst;
	size_t	len;
	size_t	i;
	int		flag[2];

	flag[0] = 1;
	flag[1] = 1;
	if (!s)
		return (NULL);
	dst = (char **)malloc(sizeof(char *) * (ft_flag_get_split_size(s, c) + 40));
	if (!dst)
		return (NULL);
	i = 0;
	while (*s)
	{
		len = 0;
		while (cut_or_pass(*s, flag) == 0 && *s && ++s)
			len++;
		if (len > 0)
		{
			dst = ft_flag_split_add(s, dst, i, len);
			i++;
		}
		while (*s == c && *s)
			s++;
	}
	dst[i] = NULL;
	return (dst);
}

int	cut_or_pass(char c, int *flag)
{
	if (c == ' ' && flag[0] == 1 && flag[1] == 1)
		return (1);
	else if (c == '\'' && flag[1] == 1)
	{
		flag[0] = flag[0] * -1;
	}
	else if (c == '"' && flag[0] == 1)
	{
		flag[1] = flag[1] * -1;
	}
	return (0);
}

char	*ft_flag_expand(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] && s[i] != '\0')
	{
		if (s[i] == '$')
			count++;
		i++;
	}
	if (count == 0)
		return (s);
	while (count-- > 0)
	{
		s = expand_vble_lines(s, 0);
	}
	return (s);
}

int	expand_or_not(char c, int *flag)
{
	if ((c == '$' && flag[0] == 1) || c == '\0')
		return (1);
	else if (c == '\'' && flag[1] == 1)
	{
		flag[0] = flag[0] * -1;
	}
	return (0);
}

int	rm_or_not(char c, int *flag, int *count)
{
	if (c == 39 && flag[0] == 1 && flag[1] == 1 && count[0] == 2)
	{
		count[0]--;
		flag[0] = flag[0] * -1;
		return (3);
	}
	else if (c == 39 && count[0] == 1 && flag[0] == -1)
	{
		flag[0] = flag[0] * -1;
		return (3);
	}
	else if (c == 34 && flag[1] == 1 && flag[0] == 1 && count[1] == 2)
	{
		count[1]--;
		flag[1] = flag[1] * -1;
		return (3);
	}
	else if (c == 34 && count[1] == 1 && flag[1] == -1)
	{
		flag[1] = flag[1] * -1;
		return (3);
	}
	return (0);
}

char	*ft_flag_rm_quotes(char *word)
{
	char	*clean;
	int		flag[2];
	int		i;
	int		j;
	int		count[2];

	count[0] = 2;
	count[1] = 2;
	flag[0] = 1;
	flag[1] = 1;
	i = 0;
	j = 0;
	clean = (char *)malloc(sizeof(char) * (strlen(word) + 1));
	while (word[i])
	{
		if (rm_or_not(word[i], flag, count) == 0)
		{
			clean[j] = word[i];
			j++;
		}
		i++;
	}
	if (j > 0)
		clean[j] = '\0';
	return (clean);
}
