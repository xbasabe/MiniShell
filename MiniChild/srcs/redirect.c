#include "minishell.h"

char	*pre_parse(char *input) //tratar redirecciones como pipes
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
			if (input[i - 1] == ' ' && input[i + 1] == ' ')
				input[i] = '|';
		i++;
	}
	return (input);
}

void	redirections_stack(t_stack *stack)
{
	t_stack	*tmp;
	int		i;

	tmp = stack;
	i = 0;
	//if (exit_cmd_in_stack(stack) > 0) 
	//	tmp = reorder_stack(stack);
	while (tmp != NULL) //bucle recorrer stack, la pila
	{
		//if(tmp->pipe.redir == 'p')
		//	printf("redirections_stack p\n");
		if(tmp->pipe.redir == 'b') // <
			ft_redir_back(tmp);
		if(tmp->pipe.redir == 'f') //  >
			ft_redir_forward(tmp);
		if(tmp->pipe.redir == 'h') //  <<
			ft_redir_heredoc(tmp);
		if(tmp->pipe.redir == 'a') //  >>
			ft_redir_apend(tmp);
		tmp = tmp->next;
		i++;
	}
}

void	redir_to(t_stack **node, int *i, char *input) //pasar el node de stack y marcar que se hace con la salida
{
	char	c;
	char	next;
	t_stack *temp;
	int		j;
	int		count;

	temp = *node; //lo que lleg como argumento
	j = 0;
	count = 0;
	while (input[j])
	{
		c = input[j];
		if (input[j + 1])
			next = input[j + 1];
		if(c == '|')
		{
			temp->pipe.redir = 'p'; // p pipe
			count++;
			if (*i == count)
				return;
		}
		if(c == '<' && next != '<')
		{
			temp->pipe.redir = 'b'; ///b back
			count++;
			if (*i == count)
				return;
		}
		if(c == '>' && next != '>') // prev salida a archivo, popesterio al > arg[0] nombre de archivo
		{
			temp->pipe.redir= 'f'; //f forward
			count++;
			if (*i == count)
				return;
		}
		else if(c == '<' && next == '<') //HEREDOC
		{
			temp->pipe.redir = 'h'; // h = heredoc
			count++;
			if (*i == count)
				return;
		}
		else if(c == '>' && next == '>') //append
		{
			temp->pipe.redir = 'a'; // a = apend
			count++;
			if (*i == count)
				return;
		}
		j++;
	}
	return;
}

void ft_redir_forward(t_stack *stack) // >
{
	t_stack	*tmp;
	int		fd;
	char 	*path;
	t_env	*env;

	tmp = stack;
	env = g_shell.env;
	path = NULL;
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
		{
			path = (char*)malloc(sizeof(char) * strlen(env->val));
			path = env->val;
			break ;
		}
		env = env->next;
	}
	path = ft_strjoin(path, "/");
	path = ft_strjoin(path, tmp->pipe.cmd);
	fd = open(path, O_WRONLY  | O_CREAT | O_TRUNC, S_IRWXU);
	dup2(fd, tmp->pipe.p[1]);
}

void ft_redir_apend(t_stack *stack) // >>
{
	t_stack	*tmp;
	int		fd;
	char 	*path;
	t_env	*env;

	tmp = stack;
	env = g_shell.env;
	path = NULL;
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
		{
			path = (char*)malloc(sizeof(char) * strlen(env->val));
			path = env->val;
			break ;
		}
		env = env->next;
	}
	path = ft_strjoin(path, "/"); //se puede meter ./filename sin tener que buscar el path
	path = ft_strjoin(path, tmp->pipe.cmd);
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	dup2(fd, tmp->pipe.p[1]);
	/*
	//redireccioar salida del prev
	if(tmp->prev) 
		dup2(tmp->prev->pipe.p[1],fd); //salida del previo a archio fd
	printf("saliendo de ft_redir_forward fd %d\n", fd);
	//redireccionar la salida de comando que reciba eñ fichero y ejecuta
	*/
	
}

void ft_redir_heredoc(t_stack *stack) // <<
{
	t_stack	*tmp;
	char 	*path;
	char	*txt;
	char	*limit;
	int		fd;

	tmp = stack;
	path = NULL;
	txt = NULL;

	fd = open("./heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	/*
	if(tmp->prev)
		//tmp->prev->pipe.p[0] = dup(fd);
		dup2(fd, tmp->prev->pipe.p[0]); //stdin por fd en vez de 0
	*/
	limit = tmp->pipe.cmd;
	
	while (1)
	{
		txt = readline("heredoc$> ");
		if(strcmp(txt, limit) == 0)
			break;
		write(fd, txt, sizeof(char) * ft_strlen(txt));
		write(fd, "\n", 1);
	}
	//redireccioar entrada de prev
	//dup2(fd, tmp->prev->pipe.p[0]);
	dup2(fd, tmp->pipe.p[0]);
	close(fd);
}

void ft_redir_back(t_stack *stack) // <
{
	t_stack	*tmp;
	int		fd;
	char 	*path;
	t_env	*env;
	//char	txt[2];

	//if(tmp->prev)
	//	tmp->prev->pipe.arg[0] = tmp->pipe.cmd;
	
	tmp = stack;
	env = g_shell.env;
	path = NULL;
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
		{
			path = (char*)malloc(sizeof(char) * strlen(env->val));
			path = env->val;
			break ;
		}
		env = env->next;
	}
	path = ft_strjoin(path, "/");
	path = ft_strjoin(path, tmp->pipe.cmd);
	fd = open(path, O_RDONLY, S_IRWXU);
	
	
	/*Fake, escribimos en el pipe
	while(read(fd, txt, 2) > 0)
		write(fd, txt, sizeof(char) * ft_strlen(txt));
	*/
	//redirection	
	//dup2(tmp->pipe.p[1], tmp->prev->pipe.p[0]);
	//dup2(fd, STDIN_FILENO);
	//dup2(fd, tmp->pipe.p[0]);
	tmp->prev->pipe.p[0] = fd; //dup2(fd, tmp->prev->pipe.p[0]);
	
	printf("redireccionando < en el cmd %s\n", tmp->pipe.cmd);
	printf(" fd %d\n", fd);
	printf(" tmp->prev->pipe.p[0] %d cmd %s\n", tmp->prev->pipe.p[0], tmp->prev->pipe.cmd);
	printf(" tmp->pipe.p[0] %d cmd %s\n", tmp->pipe.p[0], tmp->pipe.cmd);
	write(tmp->prev->pipe.p[0], "check\n", 6);
	close(fd);
}
