#include "minishell.h"

t_stack *to_end_of_stack(t_stack *stack);

void	redir_node(t_stack *stack)
{
	t_stack	*tmp;

	tmp = stack;
	if(tmp->prev == NULL && tmp->next == NULL)
		return; //nodo unico

	if(tmp->next->pipe.redir == 'b') // hacemos <
		ft_redir_node_back(tmp);
	else if(tmp->next->pipe.redir == 'f') // hacemos >
		ft_redir_node_forward(tmp);
	else if(tmp->next->pipe.redir == 'h') // hacemos <<
		ft_redir_node_heredoc(tmp);
	else if(tmp->next->pipe.redir == 'a') // hacemos >>
		ft_redir_node_apend(tmp);
	//if(tmp->next->pipe.redir == 'o')
	if (tmp->next->next == NULL) // send stdout to the pipe to next comand
		//dup2(1, tmp->pipe.p[1]);
		tmp->pipe.p[1] = 1;
	//if(tmp->prev != NULL)  //stdin entrada debe ser lo leido del pipe
	//	dup2(tmp->pipe.p[0], 0);

	dup2(tmp->pipe.p[0], STDIN_FILENO); //tmp sustituye a stdin
	dup2(tmp->pipe.p[1], STDOUT_FILENO);
	printf("REDIRETC stdin: %d pipe[0] %d\n", STDIN_FILENO, tmp->pipe.p[0]);
	printf("REDIRETC stdout %d pipe[1]%d\n",  STDOUT_FILENO, tmp->pipe.p[1]);
}

void ft_redir_node_forward(t_stack *stack) // >
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

void ft_redir_node_apend(t_stack *stack) // >>
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
	path = ft_strjoin(path, tmp->next->pipe.cmd);
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	dup2(fd, tmp->next->pipe.p[1]);
	/*
	//redireccioar salida del prev
	if(tmp->prev) 
		dup2(tmp->prev->pipe.p[1],fd); //salida del previo a archio fd
	printf("saliendo de ft_redir_forward fd %d\n", fd);
	//redireccionar la salida de comando que reciba eñ fichero y ejecuta
	*/
	
}

void ft_redir_node_heredoc(t_stack *stack) // <<
{
	t_stack	*tmp;
	char 	*path;
	char	*txt;
	char	*limit;
	int		fd;

	tmp = stack;
	path = NULL;
	txt = NULL;

	fd = open("./heredoc.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	/*
	if(tmp->prev)
		//tmp->prev->pipe.p[0] = dup(fd);
		dup2(fd, tmp->prev->pipe.p[0]); //stdin por fd en vez de 0
	*/
	limit = tmp->next->pipe.cmd;
	
	while (1)
	{
		txt = readline("heredoc$> ");
		if(strcmp(txt, limit) == 0)
			break;
		write(fd, txt, sizeof(char) * ft_strlen(txt));
		write(fd, "\n", 1);
	}
	//redireccioar entrada de prev
	tmp->pipe.p[0] = fd;
	tmp->pipe.p[1] = tmp->next->pipe.p[1];
}

void ft_redir_node_back(t_stack *stack) // <
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
	path = ft_strjoin(path, tmp->next->pipe.cmd);
	fd = open(path, O_RDONLY, S_IRWXU);
	tmp->pipe.p[0] = fd; //file descriptor from next node
	tmp->pipe.p[1] = tmp->next->pipe.p[1]; //output to next node output 
}

char *redir_squence(t_stack *stack)
{
	char	*c;

	t_stack	*tmp;
	int		i;

	tmp = stack;
	i = 0;
	c = (char*)malloc(sizeof(char));
	while (tmp != NULL) //bucle recorrer stack, la pila
	{
		//c = ft_strjoin(c, tmp->pipe.redir);
		tmp = tmp->next;
	}
	return(c);
}

t_stack *to_end_of_stack(t_stack *stack)
{
	t_stack	*tmp;
	
	tmp = stack;
	while (tmp != NULL) //bucle recorrer stack, la pila
		tmp = tmp->next;
	return(tmp);
}

void	reverse_redir_node(t_stack *stack) //LOGICA PARA mirar no solo la edir propia
{
	t_stack	*tmp;

	tmp = stack;
	tmp = to_end_of_stack(tmp);
	if(tmp->prev == NULL && tmp->next == NULL)
		return; //nodo unico

	if(tmp->next->pipe.redir == 'b') // hacemos <
		ft_redir_node_back(tmp); //abrir el fila y segun que haya prev y post redireccionamos en consecuencia
	else if(tmp->next->pipe.redir == 'f') // hacemos >
		ft_redir_node_forward(tmp);
	else if(tmp->next->pipe.redir == 'h') // hacemos <<
		ft_redir_node_heredoc(tmp);
	else if(tmp->next->pipe.redir == 'a') // hacemos >>
		ft_redir_node_apend(tmp);
	//if(tmp->next->pipe.redir == 'o')
	if (tmp->next->next == NULL) // send stdout to the pipe to next comand
		//dup2(1, tmp->pipe.p[1]);
		tmp->pipe.p[1] = 1;
	//if(tmp->prev != NULL)  //stdin entrada debe ser lo leido del pipe
	//	dup2(tmp->pipe.p[0], 0);

	dup2(tmp->pipe.p[0], STDIN_FILENO); //tmp sustituye a stdin
	dup2(tmp->pipe.p[1], STDOUT_FILENO);
	printf("REDIRETC stdin: %d pipe[0] %d\n", STDIN_FILENO, tmp->pipe.p[0]);
	printf("REDIRETC stdout %d pipe[1]%d\n",  STDOUT_FILENO, tmp->pipe.p[1]);
}