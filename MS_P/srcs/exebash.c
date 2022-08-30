/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exebash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:33:24 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/08/08 13:26:35 by marvin           ###   ########.fr       */
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
	clear((char **)arguments);
	clear(tokens);
}

const char	*search_cmd(char *txt, char **envi)
{
	const char	**p;
	int			i;

	p = (const char **)ft_split(getenv("PATH"), ':');
	i = path_exe(p, envi, txt);
	if (i == -1)
	{
		clear((char **)p);
		return (NULL);
	}
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
			printf("%s: command not found\n", txt);
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
	closedir(dp);
	return (-1);
}

pid_t	child_launch_pipe(char *input, char **envi, struct t_stack *node)
{
	pid_t	ch_pid;
	char 	pipe_text[99999];
	int		size;

	(void)input;
	//pipe(node->pipe.p); //lo hacemos al inicializar, traerlo aqui?
	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (ch_pid == 0) //hijo
	{
		close(node->pipe.p[0]); //cerrado lado lectura
		if (node->next != NULL) //si hay nodos despues, redirigir la salida
			dup2(node->pipe.p[1] ,STDOUT_FILENO); //en vez de ejecuatr y mandar a pantalla
		if (node->prev != NULL && node->pipe.prev_arg != NULL)
		{
			node->pipe.arg = node->pipe.prev_arg; //cargar argumento al siguiente nodo
		}
		//PARSEO AQUI
		launch(node->pipe.input, envi);	
	}
	if (ch_pid > 0) //padre
	{
		close(node->pipe.p[1]);//cerrado lado escritura
		if ((size = read(node->pipe.p[0], pipe_text,100) > 0) && node->next != NULL) //limitado a 100 caracteres
		{
			node->next->pipe.prev_arg = pipe_text; //retocar quedan 'restos' si el arg nterior es más largo
			/*
			while(--size > 0)
			{
				node->next->pipe.prev_arg[size]= pipe_text[size];
				size--;
			}
			*/
		}
	}
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
	//if (node->prev != NULL && node->pipe.prev_arg != NULL)
		//printf("Argumento previo:\n '%s'\n", node->pipe.prev_arg);
	if (is_built(input) == 0)
		exec_built_in(input, envi, node);
	else if(is_built(input) == 1)
	{
		prev_cmd_out(input, envi, node);  //funcion para cargar el argumento del anterio.
		printf("new input: '%s'\n", node->pipe.input);
		pid_back = child_launch_pipe(node->pipe.input, envi, node);
		if (waitpid(pid_back, &wstatus, WUNTRACED | WCONTINUED) == -1)
		{
			//perror("waitpid"); //muteado evitamos el aviso de "waitpid: no child process"
			free(input);
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
