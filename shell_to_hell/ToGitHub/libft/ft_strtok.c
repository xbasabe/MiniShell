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

size_t	ft_strcpy(char *dst, char *src)
{
	size_t	i;

	if (dst == NULL || src == NULL)
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src [i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}

size_t	ft_strncpy(char *dst, const char *src, int init)
{
	int	i;
	char	*csrc;

	if (dst == NULL || src == NULL)
		return (0);
	i = 0;
	csrc = (char *)src;
	while (csrc[i] != '\0' && i <= init)
	{
		dst[i] = csrc [i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}

int	ft_str2len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
