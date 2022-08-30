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
    
    tokens = ft_split(input, '|');
    if (tokens[0])
    {
        stack = create_node(tokens[0], envi);
    }
    i = 1;
    while (tokens[i])
    {
        tmp_node = create_node(tokens[i], envi);
        insert_l_pipe(tmp_node, stack);
        i++;
    }
    free(tokens);
    return (stack);
}

struct t_stack  *create_node(char *txt, char **envi) 
{
    struct t_stack  *node;

    node = (struct t_stack *)malloc(sizeof(struct t_stack));
    node->pipe.input = txt;
    node->pipe.envi = envi;
    node->pipe.prev_arg = NULL;
    node->pipe.cmd = NULL;
    node->pipe.arg = NULL;
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
        exec_cmd(tmp->pipe.input, tmp->pipe.envi, tmp);
        tmp = tmp->next;
        i++;
        //librar aqui cada nodo ejecutado?
    }
    deleteAllNodes(stack);
    //free_node(stack);
}

/*
void    free_stack(struct t_stack *stack)
{
    struct t_stack  *tmp;

    tmp = stack;
    while(stack)
    {
        tmp = stack->next;
        free(stack->pipe.input);
        //free(tmp->pipe.envi); // prueba
        //free(tmp->pipe.p); //prueba
        //free(tmp->pipe.arg);
        //free(tmp->pipe.cmd);
        //free(tmp->pipe.prev_arg);
        free(tmp->next);
        free(tmp->prev);
        //free(stack);
        stack = tmp;
    }
    free(stack);
    free(tmp);
}
*/

void    free_stack(struct t_stack *stack)
{
    //struct t_stack  *tmp;

    
    if (stack->next == NULL)
    {
        free_node(stack);
        //free(stack);
    }
    /*
    else if(stack->next != NULL) //recorrer la pila y liberar los nodos
    {
        tmp = stack;
        while(stack)
        {
            tmp = stack->next;
            free_node(stack->prev);
            stack = tmp;
        }
        free(stack);
    } */
}

void    free_node(struct t_stack *node)
{
    if (node == NULL)
        return ;
        //FREE DATA
    
    //free(node->pipe.arg);
    //if (node->pipe.prev_arg)
        //free(node->pipe.prev_arg);
    //free(node->pipe.cmd);

    free_node(node->next);
    free_node(node->prev);
    free(node->pipe.input);
    free(node);
}

void deleteAllNodes(struct t_stack *start)
{
    struct t_stack * temp;

    while (start != NULL)
    { 
        temp = start;
        free(temp->pipe.input);
        start = start -> next;
        free(temp);
    }
}