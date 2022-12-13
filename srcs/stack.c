/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 11:39:07 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/08 18:19:06 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack	*pipe_stack(char *input)
{
	t_stack	*stack;
	t_stack	*tmp_node;
	char	**tokens;
	int		i;

	input = pre_parse(input);
	//tokens = ft_split(input, ' ');
	tokens = split_tokens(input);
	if (tokens[0])
	{
		stack = create_node(tokens[0]);
		create_cmds(&stack, tokens[0]);
		//stack->pipe.parsed_input = parse(stack->pipe.input);
	}
	if(tokens[1] != NULL)
	{
		i = 1;
		while (tokens[i])
		{
			tmp_node = create_node(tokens[i]);
			create_cmds(&tmp_node, tokens[i]);
			//tmp_node->pipe.parsed_input = parse(tmp_node->pipe.input);
			insert_l_pipe(tmp_node, stack);
			i++;
		}
	}
	return (stack);
}

t_stack	*create_node(char *txt)
{
	t_stack	*node;

	node = (t_stack *)malloc(sizeof(t_stack));
	node->pipe.input = ft_strdup(txt);
	node->pipe.parsed_input = parse(txt);
	//node->pipe.parsed_input = NULL;
	node->pipe.cmd = NULL;
	node->pipe.arg = NULL;
	node->pipe.ext_path = NULL;
	node->next = NULL;
	node->prev = NULL;
	pipe(node->pipe.p);
	return (node);
}

void	insert_l_pipe(t_stack *node, t_stack *stack)
{
	t_stack	*temp;

	if (stack->next == NULL)
	{
		stack->next = node;
		node->prev = stack;
	}
	else
	{
		temp = stack->next;
		while (temp->next)
			temp = temp->next;
		node->prev = temp;
		temp->next = node;
	}
}

void	free_node_content(t_stack *node)
{
	if (node == NULL)
		return ;
	if (node->pipe.arg != NULL)
		clear(node->pipe.arg);
	free(node->pipe.input);
	free(node->pipe.cmd);
	//free(node->pipe.parsed_input);
}

void	delete_all_nodes(t_stack *start)
{
	t_stack	*temp;

	while (start != NULL)
	{
		temp = start;
		free_node_content(temp);
		start = start -> next;
		free(temp);
	}
}
