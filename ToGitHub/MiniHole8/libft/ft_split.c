/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:53:14 by nlibano-          #+#    #+#             */
/*   Updated: 2024/02/16 17:25:50 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_split_size(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s && s++)
	{
		while (*s != c && *s)
			s++;
		count++;
		while (*s == c && *s)
			s++;
	}
	return (count);
}

static char	**ft_split_add(const char *s, char **dst, size_t i, size_t len)
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

char	**ft_split(char const *s, char c)
{
	char	**dst;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	dst = (char **)malloc(sizeof(char *) * (ft_get_split_size(s, c) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (*s)
	{
		len = 0;
		while (*s != c && *s && ++s)
			len++;
		if (len > 0)
		{
			dst = ft_split_add(s, dst, i, len);
			i++;
		}
		while (*s == c && *s)
			s++;
	}
	dst[i] = NULL;
	return (dst);
}
