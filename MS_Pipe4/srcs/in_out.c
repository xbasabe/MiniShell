#include "minishell.h"

int is_built(char *input)
{
    char	**tokens;
    int     r;

	tokens = ft_split((const char*)input, ' ');
	tokens[0] = lowercase(tokens[0]);
    r = 1;
	if (str_cmp(tokens[0], "echo") == 0)
		r = 0;
	else if (str_cmp(tokens[0], "pwd") == 0)
		r = 0;
	else if (str_cmp(tokens[0], "cd") == 0)
		r = 0;
	else if (str_cmp(tokens[0], "export") == 0)
		r = 0;
	else if (str_cmp(tokens[0], "unset") == 0)
		r = 0;
	else if (str_cmp(tokens[0], "env") == 0)
		r = 0;
	else if (str_cmp(tokens[0], "exit") == 0)
		r = 0;
	clear(tokens);
	return (r);
}

int    built_in_out(char *input, char **envi, struct t_stack *node)
{
    int fd_result;
    
    (void) envi;
	(void) input;
    fd_result = 1;
	if (node->next != NULL)
    {
		fd_result = node->pipe.fd_out;
    }
	else
	{
		fd_result = 1;
	}
    return (fd_result);
}

/*
void	prev_cmd_out(char *input, char **envi, struct t_stack *node) //leer salida del anterio cmd del archivo
{
	//char	c[1];
	int		i;
	char	prueba[999];

	(void)input;
	(void)envi;
	if (node->prev != NULL)
	{	
		i = 1;
		//write(1, "cmd pipe built in: ", 19);
		//i = read(node->pipe.fd_out, c, 1);
		close(node->pipe.fd_out);
		node->pipe.fd_out = open("results", O_RDWR | O_TRUNC);
		node->pipe.fd_out = open("results", O_RDWR);
		node->prev->pipe.fd_out = node->pipe.fd_out;
		if (i == -1)
			return ;
		while (i > 0)
		{
			//node->pipe.input[i++] = c[0];
			//prueba[i++] = c[0];
			write(1, "cmd pipe built in: ", 19);
			i = read(node->prev->pipe.fd_out, prueba, 25);
			write(1, prueba, i);
			write(1, "\n", 1);
			//write(1, &c, 1);
		}
	}
}
*/

void	prev_cmd_out(char *input, char **envi, struct t_stack *node) //leer salida del anterio cmd del archivo
{
	(void)input;
	(void)envi;
	if (node->prev != NULL && node->pipe.prev_arg != NULL)
	{	
		
		//node->pipe.input[i++] = c[0];
		//prueba[i++] = c[0];
		//write(1, "cmd prev argument: ", 19);
		//write(1, node->pipe.prev_arg, 25);
		//write(1, "\n", 1);
		printf("   -prev argument: %s\n", node->pipe.prev_arg);
		free(node->pipe.prev_arg);
	}
	else
		printf("   -NO prev arg\n");
}

void	clear_file(char *file) //no utilizada, archivo abierto en modo de borrado al cerrar
{
	char	c[1];
	int		fd;
	
	fd = open(file, O_WRONLY);
	while(read(fd, c, 1) != 0)
		write(fd, "", 1);
	close(fd);
}
