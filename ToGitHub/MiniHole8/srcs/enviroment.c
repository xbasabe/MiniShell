/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:17:41 by marvin            #+#    #+#             */
/*   Updated: 2022/12/07 21:34:19 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_envi(t_env **envi, char **env)
{
	t_env	*new;
	char	**values;
	int		i;

	i = -1;
	while (env[++i])
	{
		values = ft_split(env[i], '=');
		new = ft_lstnew(values[0], values[1]);
		ft_lstadd_back(envi, new);
		clear(values);
	}
}

int	env_size(void)
{
	t_env	*env;
	int		i;

	env = g_shell.env;
	i = 1;
	while (env)
	{
		i++;
		env = env ->next;
	}
	return (i);
}
