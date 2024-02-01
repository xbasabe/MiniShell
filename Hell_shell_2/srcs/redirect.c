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
	if (exit_cmd_in_stack(stack) > 0)
		tmp = reorder_stack(stack);
	while (tmp != NULL) //buclre recorrer stack, la pila
	{
		//redireccionar
		if((tmp->pipe.redir = 'p'))
			//es por defecto
		if((tmp->pipe.redir = 'b')) // hacemos <
			//funcion redirect <
		if((tmp->pipe.redir = 'f')) // hacemos >
			//funcion redirect >
		if((tmp->pipe.redir = 'h')) // hacemos <<
			//funtion heredoc
		tmp = tmp->next;
		i++;
	}
}
