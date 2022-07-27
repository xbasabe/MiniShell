/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exebash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:33:24 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/07/27 13:51:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch(char *intro, char **envi)
{
	const char	*path;
	char *const	*arguments;
	char		**tokens;

	tokens = ft_split(intro, ' ');
	arguments = (char *const *)tokens;
	path = (const char *)search_cmd(tokens[0], envi);
	if (path == NULL)
		return ;
	path = stradd((char *)path, "/");
	path = stradd((char *)path, tokens[0]);
	execve(path, arguments, envi);
	free((char *)path);
	clear(tokens);
}

const char	*search_cmd(char *txt, char **envi)
{
	const char	**p;
	int			i;

	p = (const char **)ft_split(getenv("PATH"), ':');
	i = path_exe(p, envi, txt);
	if (i >= 0)
		return (p[i]);
	clear((char **)p);
	return (NULL);
}

int	path_exe(const char **p, char **envi, char *txt)
{
	const char		*directory;
	struct dirent	*dir;
	DIR				*dp;
	int				i;
	int				j;

	(void) envi;
	i = 0;
	j = 0;
	while (p[i])
	{
		directory = p[i];
		if ((dp = opendir(directory)) == NULL)
		{
			printf("'%s' not found\n", txt);
			return (-1);
		}
		while ((dir = readdir(dp)) != NULL)
		{
			if (str_cmp(dir->d_name, txt) == 0)
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

pid_t	child_launch_pipe(char *input, char **envi, struct t_stack *node)
{
	pid_t	ch_pid;
	//int		wstatus;
	char 	pipe_text[99999];
	char	tmp[1];
	//int		i;

	//pipe(node->pipe.p);
	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (ch_pid == 0) //hijo
	{
		close(node->pipe.p[1]); //cerrado lado escritura
		if (node->next != NULL) //si hay nodos despues, redirigir la salida
		{
			dup2(node->pipe.p[1] ,STDOUT_FILENO); //en vez de ejecuatr y mandar a pantalla
		}
		
		if (is_built(input) == 1)
		{
			//cargar como argumento pipe_text;
			//i = 0;
			if (node->prev != NULL) //si hay nodos antes leer su output
			{
				write(1, "nuevo argumento: ", 17);
				/*
				while (read(node->pipe.p[0], tmp, 1) == 1)
				{
					node->pipe.prev_arg[i] = tmp[0];
					write(1, tmp, 1);
					i++;
				}
				*/
				node->pipe.prev_arg = pipe_text;
				//fd_putstr(node->pipe.prev_arg, 1);
				write(1, "\n", 1);
			}
			launch(input, envi);
		}
	}
	//clear(tokens);
	if(ch_pid > 0)
	{
		close(node->pipe.p[0]);//cerrado lado lectura
		//ft_strcpy(node->prev->pipe.prev_arg, pipe_text);
		//write(node->pipe.p[1], node->next->pipe.prev_arg, 31); //esto queda como cmd anterior
		while(read(node->pipe.fd_out, tmp, 1) == 1)
		{
			//read(node->pipe.fd_out, tmp, 10);
			write(node->pipe.p[1], tmp, 1);

		}
	}
	/*
	if (waitpid(ch_pid, &wstatus, WUNTRACED | WCONTINUED) == -1)
	{
		perror("waitpid");
		free(input);
		exit(EXIT_FAILURE);
	}
	*/
	return (ch_pid);
}

pid_t	child_launch(char *input, char **envi, struct t_stack *node)
{
	pid_t	ch_pid;
	int		wstatus;

	pipe(node->pipe.p);
	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (ch_pid == 0) //hijo
	{
		launch(input, envi);
	}
	if(ch_pid > 0)
	{
		close(node->pipe.p[0]);
	}

	if (waitpid(ch_pid, &wstatus, WUNTRACED | WCONTINUED) == -1)
		{
			perror("waitpid");
			free(input);
			exit(EXIT_FAILURE);
		}

	return (ch_pid);
}

int	exec_cmd(char *input, char **envi, struct t_stack *stack)
{
	struct t_stack *node;
	int		wstatus;
	pid_t	pid_back;
	
	node = stack;
	if (is_built(input) == 0)
	{
		node->pipe.fd = built_in_out(input, envi, node);
		prev_cmd_out(input, envi, node); //funcion cargar argumentos desde archivo, salida del anterior comando
		is_built_in(input, envi, node);
	}
	else if(is_built(input) == 1)
	{
		//child_launch(input, envi, node);
		//node->pipe.fd = built_in_out(input, envi, node);
		pid_back = child_launch_pipe(input, envi, node);
		if (waitpid(pid_back, &wstatus, WUNTRACED | WCONTINUED) == -1)
		{
			perror("waitpid");
			free(input);
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
