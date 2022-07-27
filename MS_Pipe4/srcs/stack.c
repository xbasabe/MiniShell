/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 11:39:07 by marvin            #+#    #+#             */
/*   Updated: 2022/07/13 11:39:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct t_stack *pipe_stack(char * input, char **envi)
{
    struct t_stack  *stack;
    struct t_stack  *tmp_node;
    char            **tokens;
    int             i;
    
    //PARSEO VA AQUI
    //
    //
    tokens = ft_split(input, '|');
    
    if (tokens[0])
    {
        stack = create_node(tokens[0], envi);
        stack->pipe.fd_out = open("results", O_RDWR | O_TRUNC);
    }
    i = 1;
    while (tokens[i])
    {
        tmp_node = create_node(tokens[i], envi);
        tmp_node->pipe.fd_out = stack->pipe.fd_out;
        insert_l_pipe(tmp_node, stack);
        i++;
    }
    return (stack);
}

struct t_stack  *create_node(char *txt, char **envi) 
{
    struct t_stack  *node;

    node = (struct t_stack *)malloc(sizeof(struct t_stack));
    node->pipe.input = txt;
    node->pipe.envi = envi;
    node->next = NULL;
    node->prev = NULL;
    pipe(node->pipe.p); //debe ir aquí?
    return(node);
}

void    insert_f_pipe(struct t_stack *node, struct t_stack *stack) //first MAL!!
{
    node->next = stack;
    //stack->next = node;
}

void    insert_l_pipe(struct t_stack *node, struct t_stack *stack) //last
{
    struct t_stack  *temp;
    
    if (stack->next == NULL)
    {
        stack->next = node;
        node->prev = stack;
    }
    else
    {
        temp = stack->next;
        while(temp->next)
            temp = temp->next;
        node->prev = temp;
        temp->next = node;
    }
}

void    exec_stack(struct t_stack *stack)
{
    struct t_stack  *tmp;
    int             i = 0;

    tmp = stack;
    while(tmp != NULL)
    {
        exec_cmd(tmp->pipe.input, tmp->pipe.envi, tmp);  //built in no son childs
        tmp = tmp->next;
        i++;
    }
    free(stack);
}

void    free_stack(struct t_stack *stack)
{
    struct t_stack  *tmp;

    tmp = stack;
    close(stack->pipe.fd_out);
    free(tmp->pipe.envi);
    free(tmp->pipe.p);
    while(stack)
    {
        tmp = stack->next;
        free(stack->pipe.input);
        free(stack);
        stack = tmp;
    }
}
