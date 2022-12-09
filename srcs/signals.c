/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:56:10 by marvin            #+#    #+#             */
/*   Updated: 2022/12/07 22:32:27 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_prompt(int sig)
{
	g_shell.num_quit = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	g_shell.num_quit = 130;
	write(1, "\b\b\n", 1);
	(void)sig;
}

void	back_slash(int sig)
{
	g_shell.num_quit = 131;
	printf("Quit (core dumped)\n");
	(void)sig;
}

void	sig_handler(int sig)
{
	printf("\b\b  \b\b");
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{
		printf("\b\b\b\b\b\b\b\b\bexit\n");
		exit(0);
	}
}

