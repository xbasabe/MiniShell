/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:47:29 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/02/08 13:12:28 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_integer(const char *str)
{
	long	integer;

	integer = 0;
	while (*str > 47 && *str < 58)
	{
		integer = (integer * 10) + (*str - '0');
		str++;
	}
	return (integer);
}

long	ft_atoi(const char *str)
{
	long	minus;
	long	plus;
	long	integer;

	while (*str == ' ' || (*str > 8 && *str < 14))
		str++;
	minus = 0;
	plus = 0;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus++;
		plus++;
		str++;
	}
	if (minus > 1 || plus > 1)
		return (0);
	integer = ft_integer(str);
	if ((minus % 2) != 0)
		integer = integer * (-1);
	return (integer);
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	if (!str[len])
		return(0);
	while (str[len] != '\0')
		len++;
	return (len);
}

int	aux_len(char **str)
{
	int	len;

	len = 0;
	while (str[len] != NULL)
		len++;
	return (len);
}

void	ft_strintcpy(int *dst, int *stack_a, int size)
{
	int	i;

	i = 0;
	while (i < (size))
	{
		if (stack_a[i] == 0)
			dst[i] = 0;
		else
			dst[i] = stack_a[i];
		i++;
	}
}
