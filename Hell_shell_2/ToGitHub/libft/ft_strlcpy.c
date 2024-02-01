/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:20:43 by nlibano-          #+#    #+#             */
/*   Updated: 2021/10/26 19:21:01 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_size;

	src_size = 0;
	while (src[src_size] != '\0')
		src_size++;
	if (dstsize == 0)
		return (src_size);
	i = 0;
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
