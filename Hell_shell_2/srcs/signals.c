/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:56:10 by marvin            #+#    #+#             */
/*   Updated: 2023/12/05 10:21:35 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_prompt_C(int sig)
{
	g_shell.num_quit = 130;
	write(1, "\n", 1);
	//rl_replace_line("", 0);
	rl_on_new_line();
	//rl_redisplay(); //saca el segundo Minihsell en el promt
	(void)sig;
}

void	restore_prompt_D(int sig)
{
	g_shell.num_quit = 130;
	write(1, "\n", 1);
	//rl_replace_line("", 0);
	//rl_on_new_line();
	rl_redisplay(); //saca el segundo Minihsell en el promt
	(void)sig;
}

void	ctrl_c(int sig)
{
	(void)sig;
	
	//write(1, "\b\b\b\n", 1); //añadido
	write(2, "\n\n", 2);
	rl_replace_line("", 0);//añadido
	rl_on_new_line(); //añadido
	rl_redisplay();
	g_shell.num_quit = 130;
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
		signal(SIGINT, restore_prompt_C);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{
		rl_on_new_line();
		printf("\b\b\b\b\b\b\b\b\\b\b\b\bexit\n");
		exit(0);
	}
}
void	handler_signal_zeta()
{
    printf(" Pulsada ctrl Z\n");
	rl_replace_line("", 0);
	rl_on_new_line(); //añadido
	rl_redisplay();
	if(g_shell.pid == 0)
		kill(0, SIGTERM);
	//en caso de star en padre ignorar
	//en caso de estar en hijo execv matar hijo/ matar proceso de execv
}


void	new_sig_handler()
{
	printf("\b\b  \b\b");
	if(g_shell.pid == 0) //proceso hijo, execve
	{
		signal(SIGINT, restore_prompt_C); //SIGN INT ctrl C
		//signal(SIGQUIT, SIG_IGN);      //SIGQUIT  Ctrl D
		signal(SIGQUIT, restore_prompt_D);
		//signal(SIGTSTP, signal_zeta);    //SIGTSTP Ctrl Z
	}
	if(g_shell.pid > 0) //proceso padre
	{
		//signal(SIGINT, ctrl_c);
		signal(SIGINT, restore_prompt_C);
		signal(SIGQUIT, back_slash);
		//signal(SIGTSTP, signal_zeta);
		exit(0);
	}
	/*
	if (sig == 3)
	{
		printf("\b\b\b\b\b\b\b\b\bexit\n");
		exit(0);
	}
	*/
}
