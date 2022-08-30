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



static char	**free_all_if_error(char **array)
{
	unsigned int	i;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}
static unsigned int	get_nb_cols(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_cols;
	
	nb_cols = 0;
	if (!s[0])
		return (0);
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_cols++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_cols++;
	return (nb_cols);
}
static void	get_row(char **row, unsigned int *row_len, char c)
{
	unsigned int	i;
	*row += *row_len;
	*row_len = 0;
	i = 0;
	while (**row && **row == c)
		(*row)++;
	while ((*row)[i])
	{
		if ((*row)[i] == c)
			return ;
		(*row_len)++;
		i++;
	}
}
char	**ft_split(char const *s, char c)
{
	char			**splitted;
	char			*row;
	unsigned int	i;
	unsigned int	nb_c;
	unsigned int	row_len;
	nb_c = get_nb_cols(s, c);
	splitted = malloc(sizeof(char *) * (nb_c + 1));
	if (splitted == NULL)
		return (NULL);
	row = (char *)s;
	row_len = 0;
	i = 0;
	while (i < nb_c)
	{
		get_row(&row, &row_len, c);
		splitted[i] = malloc(sizeof(char) * (row_len + 1));
		if (splitted[i] == NULL)
			return (free_all_if_error(splitted));
		ft_strlcpy(splitted[i], row, row_len + 1);
		i++;
	}
	splitted[i] = NULL;
	return (splitted);
}

/* OLD SPLIT

char	**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

unsigned int	ft_get_nb_strs(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strs++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_strs++;
	return (nb_strs);
}

void	ft_get_next_str(char **next_str, unsigned int *next_str_len, char c)
{
	unsigned int	i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == c)
			return ;
		(*next_str_len)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
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
	while (i < ft_get_nb_strs(s, c))
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
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	char	*csrc;

	if (dst == NULL || src == NULL)
		return (0);
	i = 0;
	csrc = (char *)src;
	if (size == 0)
		return (ft_strlen(csrc));
	while ((i < (size) - 1) && csrc[i] != '\0')
	{
		dst[i] = csrc [i];
		i++;
	}
	if (size > i)
		dst[i] = '\0';
	return (ft_strlen(csrc));
}

