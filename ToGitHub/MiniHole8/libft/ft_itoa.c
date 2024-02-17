/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:27:02 by xbasabe-          #+#    #+#             */
/*   Updated: 2024/02/16 17:27:02 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_char(int nb, char *str, int i)
{
	if (nb / 10)
		ft_char(nb / 10, str, i + 1);
	str[i] = '0' + nb % 10;
}

void	ft_rev_str(char	*str, int lenght)
{
	int	i;
	int	temp;

	i = 0;
	while (i < (lenght / 2))
	{
		temp = str[i];
		str[i] = str[lenght - i - 1];
		str[lenght - i - 1] = temp;
		i++;
	}
}

int	n_len(int n, int i)
{
	if (n / 10)
		return (n_len (n / 10, ++i));
	if (!(n / 10))
		return (++i);
	return (i);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;
	int		sign;

	sign = 0;
	if (n < 0)
	{
		n *= -1;
		sign = -1;
	}
	len = n_len(n, 0);
	s = (char *)malloc(sizeof(char) * (len + 1 + ((sign - 1) * -1 - 1)));
	if (!s)
		return (NULL);
	ft_char(n, s, 0);
	if (sign < 0)
		s[len] = '-';
	s[len - sign] = 0;
	ft_rev_str(s, (len - sign));
	return (s);
}
