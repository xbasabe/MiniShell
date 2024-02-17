/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:18:24 by nlibano-          #+#    #+#             */
/*   Updated: 2024/02/16 17:29:17 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	if (n == 0)
		return (0);
	i = 0;
	while (i < (n - 1) && ((unsigned char *)s1)[i] != '\0' && \
			((unsigned char *)s2)[i] != '\0' && \
			((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		i++;
	res = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
	return (res);
}
