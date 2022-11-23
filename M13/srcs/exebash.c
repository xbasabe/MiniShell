/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exebash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:33:24 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/11/03 17:57:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_in_child(char *input, char **envi, struct t_stack *stack)
{
	struct t_stack *node;

	node = stack;
	if (node->next != NULL) // send stdout to the pipe to next comand
		dup2(node->next->pipe.p[1],1);
	if(node->prev != NULL)  //stdin entrada debe ser lo leido del pipe
		dup2(node->pipe.p[0], 0);
	close(node->pipe.p[0]);
	close(node->pipe.p[1]);
	if (is_built(input) == 0)
		exit(0); //close the process, it will be excecuted in the parent
	//printf("exec child input '%s'.\n", node->pipe.input);
	if(is_built(input) == 1)
	{
		if (launch(input, envi, node) == -1) //get path and launch execve. -1 = error
		{
			fd_putstr_out("-Minishell: ", node); //printf para que salga siemrpe en pantalla?
			fd_putstr_out(node->pipe.cmd, node);
			fd_putstr_out(": command not found\n", node);
			exit(0);
		}
	}
}

pid_t	child_launch(char *input, char **envi, struct t_stack *stack)
{
	pid_t	ch_pid;
	struct t_stack *node;
	
	node = stack;
	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (ch_pid == 0) //HIJO
	{
		exec_in_child(input, envi, stack);
	}
	if(ch_pid > 0) //PADRE
	{
		close(node->pipe.p[1]);
		if (is_built(input) == 0)
		{
			//create_cmds(node); //lexer, falta el parsing(comillas)
			exec_built_in(input, envi, node);
			//free_node_content(node);
		}
		close(node->pipe.p[0]);
 	}
	wait(NULL);
	return (ch_pid);
}

void    exec_stack(struct t_stack *stack)
{
    struct t_stack  *tmp;
    int             i;

    tmp = stack;
	i = 0;
    while(tmp != NULL)
    {
        if (str_cmp(tmp->pipe.input, "^C") == 0) //no funciona para cerrar función y seguir en minishell (usar señales?)
			break ;
        child_launch(tmp->pipe.input, tmp->pipe.envi, tmp);
        tmp = tmp->next;
        i++;
    }
    //deleteAllNodes(stack);
}

int is_built(char *input)
{
    char	**tokens;
    int     r;

	tokens = ft_split((const char*)input, ' ');
	tokens[0] = lowercase(tokens[0]);
    r = 1;
	if (str_cmp(tokens[0], "pwd") == 0)
		r = 0;
	else if (str_cmp(tokens[0], "echo") == 0)
		r = 0;
	else if (str_cmp(tokens[0], "cd") == 0)
		r = 0;
	else if (str_cmp(tokens[0], "export") == 0)
		r = 0;
	else if (str_cmp(tokens[0], "unset") == 0)
		r = 0;
	else if (str_cmp(tokens[0], "env") == 0)
		r = 0;
	else if (str_cmp(tokens[0], "exit") == 0)
		r = 0;
	else if (str_cmp(tokens[0], "parse") == 0)
		r = 0;
	clear(tokens);
	return (r);
}
