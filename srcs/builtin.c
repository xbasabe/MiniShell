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

#include"minishell.h"

int	echo(char *input, int n, struct t_stack *node)
{
	char	**temp;
	int		i;

	temp = ft_split(input, ' ');
	i = 1;
	if (temp[1])
	{
		if (str_cmp(temp[1], "-n") == 0)
		{
			n = 1;
			i++;
		}
	}
	expand(temp);
	while (temp[i])
	{
		fd_putstr(temp[i], node->pipe.fd);
		i++;
		if (temp[i])
			fd_putstr(" ", node->pipe.fd);
	}
	if (n == 0)
		write(node->pipe.fd, "\n", 1);
	clear(temp);
	return (0);
}

int	cd(char **intro, char **envi)
{
	//const char		*directory;
	//struct dirent	*dir;
	//DIR				*dp;

	(void) envi;
	//ft_strcpy((char *)directory, intro[1]);
	//directory = intro[1];
	printf("   directorio: '%s'\n", intro[1]);
	if (chdir(intro[1]) != 0) 
    	perror("ch failed");

	/*
	dp = opendir(directory);
	dir = readdir(dp);
	printf("dir_name: '%s'\n", dir->d_name);
	*/
	
	return (0);
}

void	env(char **envi, struct t_stack *node)
{
	int	i;

	if (node->next == NULL)
		while (envi[i])
		{
			fd_putstr(envi[i++], node->pipe.fd);
			write(node->pipe.fd, "\n", 1);
		}
	i = 1;
	if (node->next != NULL)
	{
		node->next->pipe.prev_arg = envi[0];
		node->next->pipe.prev_arg = stradd(node->next->pipe.prev_arg, "\n");
		while (envi[i])
		{
			node->next->pipe.prev_arg = stradd(node->next->pipe.prev_arg, envi[i]);
			node->next->pipe.prev_arg = stradd(node->next->pipe.prev_arg, "\n");
			i++;
		}
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
			//fd_putstr(var[1], node->pipe.fd);
			//write(node->pipe.fd, "\n", 1);
			if (node->next != NULL)
				node->next->pipe.prev_arg = var[1];
				//ft_strcpy(node->next->pipe.prev_arg, var[1]); // el ft_strcpy falla
			else if (node->next == NULL)
			{
				fd_putstr(var[1], 1);
				write(node->pipe.fd, "\n", 1);
			}
			break;
		}
		i++;
		//clear(var);
		free(var[0]);
	}
	//clear(var);
	//free(var[0]);
}

void	export(char *input, char **envi)
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
			envi[i] = stradd(var[0], "=");
			envi[i] = stradd(envi[i], arguments[2]);
			return ;
		}
		i++;
	}
	if ((ft_str2len(arguments) == 3))
		envi = str2add(envi, input);
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
			//variable localizada, eliminar.
			printf("vble %s located in enviroment\n", envi[i]);
			return ;
		}
		i++;
	}
}

int	is_built_in(char *input, char **envi, struct t_stack *node)
{
	char	**tokens;

	tokens = ft_split(input, ' ');
	tokens[0] = lowercase(tokens[0]);
	if (str_cmp(tokens[0], "echo") == 0)
		echo(input, 0, node);
	else if (str_cmp(tokens[0], "pwd") == 0)
		pwd(envi, node);
	else if (str_cmp(tokens[0], "cd") == 0)
		cd(tokens, envi);
	else if (str_cmp(tokens[0], "export") == 0)
		export(input, envi);
	else if (str_cmp(tokens[0], "unset") == 0)
		unset(input, envi);
	else if (str_cmp(tokens[0], "env") == 0)
		env(envi, node);
	else if (str_cmp(tokens[0], "exit") == 0)
		printf("Function EXIT, under contruction\n");
	else
	{
		clear(tokens);
		return (1);
	}
	clear(tokens);
	return (0);
}
