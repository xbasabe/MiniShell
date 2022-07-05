/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:33:34 by marvin            #+#    #+#             */
/*   Updated: 2022/06/30 16:33:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *stradd(char *s1, char *s2)
{
    char *united;
    int     len;
    int     i;
    int     j;

    len = (ft_strlen(s1) + ft_strlen(s2) + 1);
    i = ft_strlen(s1);
    j = 0;
    united = (char *)malloc(sizeof(char) * len);
    ft_strcpy(united, s1);
    j = 0;
    while(i < len)
    {
        united[i] = s2[j];
        i++;
        j++;
    }
    united[i] = '\0';
    return(united);
}

int str_cmp(char *str1, char *str2)
{
    int i;

    i = 0;
    while(str1[i] && str2[i])
    {
        if (str1[i] != str2[i])
            return(1);
        i++;
    }
    return(0);
}
