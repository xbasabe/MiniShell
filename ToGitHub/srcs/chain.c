/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:18:15 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/02 22:16:41 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*stradd(char *s1, char *s2)
{
	char	*united;
	int		len;
	int		i;
	int		j;

	len = (ft_strlen((const char *)s1) + ft_strlen((const char *)s2) + 1);
	i = ft_strlen((const char *)s1);
	j = 0;
	united = (char *)malloc(sizeof(char) * len + 1);
	if (!united)
		return (NULL);
	ft_strcpy(united, s1);
	j = 0;
	while (i < len)
	{
		united[i] = s2[j];
		i++;
		j++;
	}
	united[i] = '\0';
	return (united);
}

char	**str2add(char **s1, char *s2)
{
	char	**united;
	int		len;
	int		i;

	len = (ft_str2len(s1));
	united = (char **)malloc(sizeof(char *) * (len + 1) + 1);
	if (!united)
		return (NULL);
	i = -1;
	while (s1[++i])
		//united[i] = s1[i];
		ft_strcpy(united[i], s1[i]);
	ft_strcpy(united[i], s2);
	//united[i] = s2;
	united[i + 1] = NULL;
	return (united);
}

char	**str3add(char **s1, char *s2)
{
	char	**united;
	int		len;
	int		i;

	len = (ft_str2len(s1));
	united = (char **)malloc(sizeof(char *) * (len + 1) + 1);
	if (!united)
		return (NULL);
	i = 0;
	ft_strcpy(united[i], s2);
	while (s1[++i])
		//united[i] = s1[i];
		ft_strcpy(united[i], s1[i]);
	ft_strcpy(united[i], s2);
	//united[i] = s2;
	united[i + 1] = NULL;
	i = 0;
	while (united[i])
	{
		printf("str3add  united[%d] %sn", i, united[i]);
		i++;
	}
	return (united);
}

int	str_cmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (1);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (1);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	return (0);
}

int	fd_putstr(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
	return (i);
}

char	*lowercase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 'A' && str[i] < 'Z')
			str[i] = str[i] + 32;
	i++;
	}
	return (str);
}
