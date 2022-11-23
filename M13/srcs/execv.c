/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:33:24 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/11/03 18:54:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch(char *intro, char **envi, struct t_stack *node)
{
	const char	*path;
	char *const	*arguments;
	char		**tokens;

	(void)node;
	tokens = ft_split(intro, ' ');
	if (tokens[0] == NULL)
		tokens[0] = node->pipe.cmd;
	arguments = (char *const *)tokens;
	if (node->pipe.ext_path != NULL) //(existe path en el comando introducido)
		execve(node->pipe.input, arguments, envi); 
	path = path_exe(envi, tokens[0]);
	if(path == NULL)
	{
		clear((char **)arguments);
		free((char *)path);
		return(-1) ;
	}
	//path = stradd((char *)path, "/");
	//path = stradd((char *)path, tokens[0]);
	execve(path, arguments, envi);
	return(0);
}

const char	*path_exe(char **envi, char *txt)
{
	char	*directory;
	const char	**p;
	int			i;

	(void) envi;
	i = 0;
	p = (const char **)ft_split(getenv("PATH"), ':');
	while (p[i])
	{
		directory = (char *)p[i];
		directory = stradd(directory, "/");
		directory = stradd(directory, txt);
		if (access((const char*)directory, F_OK) == 0)
		{
			clear((char **)p);
			return((const char*)directory);
		}
		free(directory);
		i++;
	}
	clear((char **)p);
	return(NULL);
}
