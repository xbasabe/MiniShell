/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:38:34 by nlibano-          #+#    #+#             */
/*   Updated: 2022/12/08 12:18:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	count;

	i = 0;
	while (dst[i] && i < size)
		i++;
	count = 0;
	while (i + 1 < size && src[count])
	{
		dst[i] = src [count];
		i++;
		count++;
	}
	if (size > i)
		dst[i] = '\0';
	return (ft_strlen((char *)src) + (i - count));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_strdup(s2));
	if (s2[0] == '\0')
		return (ft_strdup(s1));
	dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
	ft_strlcat(dst, s2, (ft_strlen(s1) + ft_strlen(s2) + 1));
	return (dst);
}
