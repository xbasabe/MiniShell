/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 13:45:16 by xbasabe-          #+#    #+#             */
/*   Updated: 2021/06/16 12:15:13 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strtok(char const *s, char c)
{
	char			**tab;
	char			*next_str;
	unsigned int	next_str_len;
	unsigned int	i;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_get_nb_strs(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	next_str = (char *)s;
	next_str_len = 0;
	while (i < 3)
	{
		ft_get_next_str(&next_str, &next_str_len, c);
		tab[i] = (char *)malloc(sizeof(char) * (next_str_len + 1));
		if (!tab[i])
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i], next_str, next_str_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	i;
	char	*csrc;

	if (dst == NULL || src == NULL)
		return (0);
	i = 0;
	csrc = (char *)src;
	while (csrc[i] != '\0')
	{
		dst[i] = csrc [i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(csrc));
}
