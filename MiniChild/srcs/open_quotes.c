#include "minishell.h"
#include <string.h>

void	flop_flag(int *flags, int *count, int f)
{
	flags[f] = flags[f] * -1;
	count[f]--;
}

int opened_quotes(char *txt, int *count, int *flags) //count numero de comillas 0 = comillas abiertas ¿cambiar a paso por valor los int?
{
	int		i;
	int     l_count[2]; //local value
	int     l_flags[2];

	l_count[0] = count[0];
	l_count[1] = count[1];
	l_flags[0] = flags[0];
	l_flags[1] = flags[1];

	i = 0;
	while(txt && txt[i] != '\0')
	{
		if(txt[i] == 39) // simples ' 39 ascci de '
		{	
			if( l_flags[0] == 1 && l_flags[1] == 1)
			{
				flop_flag(l_flags, l_count, 0);
				while(txt[++i] != 39)
				{
					if (txt[i] == '\0')
						return(0);
				}
				flop_flag(l_flags, l_count, 0);
			}
		}
		else if(txt[i] == 34) //34 es el ascci de ""
		{
			if( l_flags[0] == 1 && l_flags[1] == 1)
			{	
				flop_flag(l_flags, l_count, 1);
				while(txt[++i] != 34)
				{
					if (txt[i] == '\0')
						return(0);
				}
				flop_flag(l_flags, l_count, 1);
			}
		}
		else if (txt[i] == 39 || txt[i] == 34) //comillas que no cierran, opened quotes
			return(0);
		else if (txt[i] == '\0') //prueba, quitar
			return(1);
		i++;
	}
	return(1);
}

void	quote_d_count(char *txt, int *count)
{
	int	i;

	i = 0;
	while(txt[i] != '\0')
	{
		if(txt[i] == '"')
			count[1]++;
		else if(txt[i] == 39)
			count[0]++;
		i++;
	}
}

int	is_line_cut(char *txt, int *i)
{
	char	c;
	char	next;
	
	c = txt[*i];
	if (txt[*i + 1])
		next = txt[*i + 1];
	if(c == '|')
		return(0);
	if(c == '<' && next != '<')
		return(0);
	if(c == '>' && next != '>')
		return(0);
	else if(c == '<' && next == '<') //HEREDOC
	{
		*i = *i + 1;
		return(0);
	}
    else if(c == '>' && next == '>') //apend
	{
		*i = *i + 1;
		return(0);
	}
	//else if(c == '>' && next == '>') //esta opcion ver si la pide el subjct
	return(1);
}
