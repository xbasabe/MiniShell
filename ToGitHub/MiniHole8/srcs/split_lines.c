/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:17:51 by xbasabe-          #+#    #+#             */
/*   Updated: 2024/02/17 14:05:02 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flag_flop(int *flags, int *i, int f)
{
	int	init;

	init = *i;
	flags[f] = flags[f] * -1;
}

char	*ft_striscpy(char *dst, const char *src, int from, size_t dstsize)
{
	size_t	i;
	size_t	src_size;
	char	*cpy;

	src_size = 0;
	cpy = (char *)malloc(sizeof(char) * (dstsize + 1));
	while (src[src_size] != '\0')
		src_size++;
	if (dstsize == 0)
		return (NULL);
	i = from;
	while (i < dstsize && src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (i == dstsize)
		dst[dstsize - 1] = '\0';
	else
		dst[i] = '\0';
	ft_strcpy(cpy, dst);
	return (cpy);
}

size_t	ft_strilcpy(char *dst, const char *src, int from, size_t dstsize)
{
	size_t	i;
	size_t	src_size;

	src_size = 0;
	while (src[src_size] != '\0')
		src_size++;
	if (dstsize == 0)
		return (src_size);
	i = from;
	while (i < dstsize && src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (i == dstsize)
		dst[dstsize - 1] = '\0';
	else
		dst[i] = '\0';
	return (src_size);
}
