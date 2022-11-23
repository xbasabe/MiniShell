/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:40:03 by marvin            #+#    #+#             */
/*   Updated: 2022/06/15 10:40:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(struct t_stack *node)
{
	//int	i;
	int	n;
	char *output;

	//i = 0;
	n = 0;
	//create_cmds(node);
	//Si imprimimos el input falta quitar el echo
	if (node->pipe.arg[0] == NULL)
	{
		fd_putstr_out("\n", node);
		return (1);
	}
	if (str_cmp(node->pipe.arg[0], "-n") == 0)
	{
		n = 1;
		//i = 1;
	}
	/*
	while(node->pipe.arg[i]) //este bucle imprime palabras, trimea siempre
	{
		parse(node->pipe.arg[i]);
		fd_putstr_out(node->pipe.arg[i], node);
		i++;
		if (node->pipe.arg[i])
			fd_putstr_out(" ", node);
		
	}
	*/
	output = parse(node->pipe.input); //antes de imprimir saltar la primera palabra y no imprimir echo
	//fd_putstr_out(node->pipe.input, node);
	output++;
	output++;
	output++;
	output++;
	output++;
	fd_putstr_out(output, node);
	
	if (n == 0)
		fd_putstr_out("\n", node);
	return (0);
}

void	env(char **envi, struct t_stack *node)
{
	int	i;

	i = 0;
	while (envi[i])
	{
		fd_putstr_out(envi[i++], node);
		fd_putstr_out("\n", node);
	}
}

void	pwd(char **envi, struct t_stack *node)
{
	int		i;
	char	**var;

	i = 0;
	while (envi[i])
	{
		var = ft_split(envi[i], '=');
		if (str_cmp(var[0], "PWD") == 0)
		{
			fd_putstr_out(envi[i], node);
			fd_putstr_out("\n", node);
			break;
		}
		i++;
		clear(var);
	}
	clear(var);
}

void	export(char *input, char **envi)
{
	int		i;
	char	**var;
	char	**arguments;

	i = 0;
	arguments = ft_split(input, ' ');
	if (!arguments[1])
	{
		clear(arguments);
		return ;
	}
	if ((ft_str2len(arguments) == 3)) //1export 2vble 3valor
		while (envi[i])
		{
			var = ft_split(envi[i], '=');
			if (str_cmp(var[0], arguments[1]) == 0)
			{
				envi[i] = stradd(var[0], "=");
				envi[i] = stradd(envi[i], arguments[2]);
				clear(var);
				clear(arguments);
				return ;
			}
			i++;
			//clear(var);
		}
	if ((ft_str2len(arguments) == 4))
		envi = str2add(envi, input);
	//opcion de añadir  variable
	
	clear(var);
	clear(arguments);
}

void	unset(char *input, char **envi)
{
	int		i;
	char	**var;
	char	**arguments;

	i = 0;
	arguments = ft_split(input, ' ');
	if (!arguments[1])
		return ;
	while (envi[i])
	{
		var = ft_split(envi[i], '=');
		if (str_cmp(var[0], arguments[1]) == 0)
		{
			while(envi[i + 1])
			{
				envi[i] = envi[i + 1];
				i++;
			}
			envi[i] = '\0';
			clear(var);
			return ;
		}
		i++;
	}
	clear(var);
	return ;
}

void	exit_kill(struct t_stack *node)
{
	//kill(node->pipe.node_pid, SIGKILL);
	deleteAllNodes(node);
	exit(0);
}

int	exec_built_in(char *input, char **envi, struct t_stack *node) //reconvertir en exec in parent y sacar echo para el caso de comillas sin cerrar
{
	char	**tokens;

	tokens = ft_split(input, ' ');
	tokens[0] = lowercase(tokens[0]);
	if (str_cmp(tokens[0], "echo") == 0)
		echo(node);
	else if (str_cmp(tokens[0], "pwd") == 0)
		pwd(envi, node);
	else if (str_cmp(tokens[0], "cd") == 0)
	{
		//create_cmds(node);
		cd(input, envi, node);
	}
	else if (str_cmp(tokens[0], "export") == 0)
		export(input, envi);
	else if (str_cmp(tokens[0], "unset") == 0)
		unset(input, envi);
	else if (str_cmp(tokens[0], "env") == 0)
		env(envi, node);
	else if (str_cmp(tokens[0], "parse") == 0)
		parse(input);
	else if (str_cmp(tokens[0], "exit") == 0)
		exit_kill(node);
	else
	{
		clear(tokens);
		return (1);
	}
	clear(tokens);
	return (0);
}
