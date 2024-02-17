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

void	signals_up(void);
void	miniexe(char *input, t_stack *stack, char **tokens);

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
	g_shell.env = NULL;
	input = NULL;
	set_envi(&(g_shell.env), env);
	signals_up();
	miniexe(input, stack, tokens);
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

void	signals_up(void)
{
	signal(SIGINT, handler_control_c);
	signal(SIGTSTP, handler_signal_zeta);
	signal(SIGQUIT, SIG_IGN);
}

void	miniexe(char *input, t_stack *stack, char **tokens)
{
	while (1)
	{
		input = readline(COLOR "MiniShell $> " RESET);
		if (!input)
		{
			write(2, "exit\n", 5);
			exit(1);
		}
		add_history(input);
		if (ft_strlen(input) > 0)
		{
			stack = pipe_stack(input);
			redir_stack_fb(stack);
			exec_stack(stack, input);
		}
		free_all_params(&stack, &input, &tokens);
	}
}
