/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:33:47 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/07 22:35:23 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define COLOR "\001\e[1;34m\002"
#define RESET   "\001\e[0m\002"

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
	t_stack	*stack;

	(void)argc;
	(void)argv;
	stack = NULL;
	tokens = NULL;
	//sig_handler(1);
	new_sig_handler();
	g_shell.env = NULL;
	set_envi(&(g_shell.env), env);
	
	while (1)
	{
		input = readline(COLOR "MiniShell $> " RESET);
		add_history(input);
		//if (!input)
		//	sig_handler(3);
		if (ft_strlen(input) > 0)
		{
			tokens = ft_split(input, ' ');
			//tokens = split_tokens(input);
			if (str_cmp(tokens[0], "exit") == 0)
			{
				exit(g_shell.num_quit);
			}
			stack = pipe_stack(input);
			exec_stack(stack, input);
		}
		free_all_params(&stack, &input, &tokens);
	}
	ft_lstclear(&g_shell.env);
	return (g_shell.num_quit);
}

void	free_all_params(t_stack **stack, char **input, char ***tokens)
{
	if (*stack)
		delete_all_nodes(*stack);
	if (*input)
		free(*input);
	if (*tokens)
		clear(*tokens);
}
