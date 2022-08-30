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

void	prev_cmd_out(char *input, char **envi, struct t_stack *node) //leer salida del anterio cmd del archivo
{
	char	**tokens;
	//int		i;

	(void)envi;
	tokens = ft_split(input, ' ');
	node->pipe.cmd = tokens[0];
	if (tokens[1])
		node->pipe.arg = tokens[1];
	//i = 2;
	//while(tokens[i])
	//	node->pipe.arg = stradd(node->pipe.arg, tokens[i++]);
	
	if (node->prev != NULL && node->pipe.prev_arg != NULL)
		node->pipe.arg = node->pipe.prev_arg;
	printf("cmd: '%s'\narg: '%s'\n", node->pipe.cmd, node->pipe.arg);
	if (node->pipe.cmd != NULL && node->pipe.arg)
	{
		node->pipe.input = stradd(node->pipe.cmd, " ");
		node->pipe.input = stradd(node->pipe.input, node->pipe.arg);
	}
	clear(tokens);
}

int	fd_putstr_out(char *str, struct t_stack *node)
{
	int i;

	if (node->next == NULL)
	{
		i = 0;
		while(str[i])
			write(1, &str[i++], 1);
		return (1);
	}
	else if (node->next != NULL)
		//ft_strcpy(node->next->pipe.prev_arg , str);
		node->next->pipe.prev_arg = str;
	return (0);
}

int	read_pipe(int fd, char *str)
{
	int		i;
	int		readed;
	char	buf[1];

	if (str == NULL)
		return(0);
	while (1)
	{
    	str = '\0';
		readed = read(fd, buf, 1);

        if (readed == -1)
		{
            perror("read");
            exit(EXIT_FAILURE);
        }
		i = 0;
        if (readed > 0)
		{
			//str[i] = buf[0];
			stradd(str, buf);
			readed = read(fd, buf, 1);
			
			i++;
		}
	}
	return (i);
}
