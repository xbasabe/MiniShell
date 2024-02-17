/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:22:36 by xbasabe-          #+#    #+#             */
/*   Updated: 2024/02/16 14:23:55 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear(t_env **lst)
{
	t_env	*begin;

	if (lst)
	{
		while (*lst)
		{
			begin = (*lst)->next;
			ft_lstdelone(*lst);
			*lst = begin;
		}
	}
}

void	ft_lstdelone(t_env *lst)
{
	if (lst)
	{
		free(lst->name);
		free(lst->val);
		free(lst);
	}
}

t_env	*ft_lstlast(t_env *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
