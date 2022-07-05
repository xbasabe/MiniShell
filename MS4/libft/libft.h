/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:06:39 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/02/08 13:11:41 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>

int     ft_integer(const char *str);
long	ft_atoi(const char *str);
int		ft_strlen(const char *str);
int		aux_len(char **str);
void	ft_strintcpy(int *dst, int *stack_a, int size);
char	**ft_malloc_error(char **tab);
unsigned int	ft_get_nb_strs(char const *s, char c);
void	ft_get_next_str(char **next_str, unsigned int *next_str_len, char c);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strcpy(char *dst, const char *src);
char	**ft_strtok(char const *s, char c);
char    *stradd(char *s1, char *s2);

#endif