/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 13:33:15 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/12 17:03:10 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*aux;

	aux = str;
	while (n-- > 0)
		*aux++ = c;
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*aux;
	size_t			i;

	aux = (void *)malloc(size * count);
	if (aux == NULL)
		return (NULL);
	i = size * count;
	return (ft_memset(aux, 0, i));
}
