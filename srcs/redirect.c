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

