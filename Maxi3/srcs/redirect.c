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
		printf("redirections_stack token [%d] redir %c\n", i, tmp->pipe.redir);
		//redireccionar
		if(tmp->pipe.redir == 'p')
			printf("redirections_stack p\n");
		if(tmp->pipe.redir == 'b') // hacemos <
			ft_redir_back(tmp);
		if(tmp->pipe.redir == 'f') // hacemos >
			ft_redir_forward(tmp);
		if(tmp->pipe.redir == 'h') // hacemos <<
			ft_redir_heredoc(tmp);
		if(tmp->pipe.redir == 'a') // hacemos >>
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
			//*i = *i + 1;
			temp->pipe.redir = 'h'; // h = heredoc
			count++;
			if (*i == count)
				return;
		}
		else if(c == '>' && next == '>') //append
		{
			//*i = *i + 1;
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
	char *text = NULL;

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
	printf("buscando archivo %s\n", tmp->pipe.cmd);
	printf("en la carpeta %s\n", path);
	//fd = open(path, O_WRONLY | O_CREAT);
	fd = open(path, O_RDWR | O_CREAT, S_IRWXU);
	//redireccioar salida del prev
	//if(tmp->prev) 
	//	dup2(tmp->prev->pipe.p[1],fd); //salida del previo a archio fd
	printf("saliendo de ft_redir_forward fd %d\n", fd);
	//redireccionar la salida de comando que reciba e fichero y ejecuta
	
	read(tmp->pipe.p[0], text, 20);
	
	dup2(tmp->prev->pipe.p[1],fd);
	write(tmp->prev->pipe.p[1], text, sizeof(char) * ft_strlen(text));
	
	close(fd);
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
	path = ft_strjoin(path, "/");
	path = ft_strjoin(path, tmp->pipe.cmd);
	printf("buscando archivo %s\n", tmp->pipe.cmd);
	printf("en la carpeta %s\n", path);
	//fd = open(path, O_WRONLY | O_CREAT);
	fd = open(path, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
	//redireccioar salida del prev
	if(tmp->prev) 
		dup2(tmp->prev->pipe.p[1],fd); //salida del previo a archio fd
	printf("saliendo de ft_redir_forward fd %d\n", fd);
	//redireccionar la salida de comando que reciba eñ fichero y ejecuta

	close(fd);
}

void ft_redir_heredoc(t_stack *stack)
{
	t_stack	*tmp;
	char 	*path;

	tmp = stack;
	path = NULL;
	if(tmp->prev) 
		dup2(tmp->prev->pipe.p[0], 0); //stdin
	/*
	while (env)
	{
		readline?
	}
	*/
	//redireccioar entrada del pr
}

void ft_redir_back(t_stack *stack) // <
{
	t_stack	*tmp;
	int		fd;
	char 	*path;
	t_env	*env;
	char *txt;

	tmp = stack;
	env = g_shell.env;
	path = NULL;
	txt = NULL;
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
	printf("Archivo ft_redir back %s\n", path);
	fd = open(path, O_RDONLY | O_CREAT);
	//redireccioar entrada del prev
	if(tmp->prev) 
		dup2(tmp->prev->pipe.p[0],fd); // abrá que escribirlo al pipe.
	printf("saliendo de ft_redir_back fd %d\n", fd);
	if(tmp->next) 
		dup2(tmp->prev->pipe.p[1],tmp->pipe.p[0]);
	read(fd, txt, 5);
	write(tmp->pipe.p[1], txt, 5);
	close(fd);
}

/*
char const *redirect_type(char *txt, int *i) //pasar el node de stack y marcar que se hace con la salida
{
	char	*c;
	char	next;
	//t_stack *temp;

	//temp = node //lo que lleg como argumento
	c = (char *)malloc(sizeof(char) * 1);
	c[0] = txt[*i];
	if (txt[*i + 1])
		next = txt[*i + 1];
	if(c[0] == '|')
	{
		//temp->pipe.redir='p'; // p pipe
		return(c);
	}
	if(c[0] == '<')
	{
		//temp->pipe.redir='b'; ///b back
		return(c);
	}
	if(c[0] == '>') // prev salida a archivo, popesterio al > arg[0] nombre de archivo
	{
		//temp->pipe.redir='f'; //f forward
		return(c);
	}
	else if(c[0] == '<' && next == '<') //HEREDOC
	{
		*i = *i + 1;
		//temp->pipe.redir='h'; // h = heredoc
		return(c);
	}
	//else if(c == '>' && next == '>') //esta opcion ver si la pide el subjct
	return((char const *)c);
}

*/