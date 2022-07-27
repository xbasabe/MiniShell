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

/*
int	is_cmd(char *input, char **envi)
{
	char	**tokens;
	int		wstatus;
	pid_t	child;

	tokens = ft_split(input, ' ');
	if (str_cmp(tokens[0], "echo") == 0
		|| str_cmp(tokens[0], "ECHO") == 0)
		echo(input, 0);
	else if (str_cmp(tokens[0], "pwd") == 0
		|| str_cmp(tokens[0], "PWD") == 0)
		printf("%s\n", getenv("PWD"));
	else if (str_cmp(tokens[0], "cd") == 0
		|| str_cmp(tokens[0], "CD") == 0)
		printf("funcion cd NOT IMPLEMENTED\n");
	else if (str_cmp(tokens[0], "export") == 0
		|| str_cmp(tokens[0], "EXPORT") == 0)
		export(input, envi);
	else if (str_cmp(tokens[0], "unset") == 0
		|| str_cmp(tokens[0], "UNSET") == 0)
		printf("funcion unset NOT IMPLEMENTED\n");
	else if (str_cmp(tokens[0], "env") == 0)
		env(envi);
	else
	{
		child = child_launch(input, envi);
		if (waitpid(child, &wstatus, WUNTRACED | WCONTINUED) == -1)
		{
			perror("waitpid");
			//clear(tokens);
			//free(input);
			exit(EXIT_FAILURE);
		}
	}
	clear(tokens);
	return (0);
}
*/

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	**tokens;
	char	*next;
	char	**envi;
	struct t_stack *stack;

	(void)argc;
	(void)argv;
	envi = env;
	while (1)
	{
		input = readline("MiniShell: ");
		add_history(input);
		if (ft_strlen(input) > 0)
		{
			tokens = ft_split(input, ' ');
			next = pipetoken(input, "|");
			if (str_cmp(tokens[0], "exit") == 0 || str_cmp(tokens[0], "EXIT") == 0)
			{
				clear(tokens);
				free(input);
				free(next);
				break ;
			}
			
			stack = pipe_stack(input, envi);
			exec_stack(stack);

		}
		free(next);
		free(input);
		clear(tokens);
	}
	return (0);
}
