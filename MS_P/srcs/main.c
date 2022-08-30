/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:33:47 by marvin            #+#    #+#             */
/*   Updated: 2022/06/08 11:33:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear(char **intro)
{
	int	i;

	i = 0;
	while (intro[i])
	{
		free(intro[i]);
		i++;
	}
	free (intro);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	**tokens;
	char	**envi;
	struct t_stack *stack;

	(void)argc;
	(void)argv;
	envi = env; //crear una copia?
	while (1)
	{
		input = readline("MiniShell: ");
		add_history(input);
		if (ft_strlen(input) > 0)
		{
			tokens = ft_split(input, ' ');
			if (str_cmp(tokens[0], "exit") == 0 || str_cmp(tokens[0], "EXIT") == 0)
			{
				clear(tokens);
				free(input);
				break ;
			}
			stack = pipe_stack(input, envi);
			exec_stack(stack);
			//free_stack(stack);
		}
		free(input);
		clear(tokens);
	}
	return (0);
}
