/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipetoken.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:54:39 by marvin            #+#    #+#             */
/*   Updated: 2022/06/22 11:54:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*EXPANDIR VBLE $*/
int	expand(char **txt)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (txt[i])
	{
		if (txt[i][0] == '$')
		{
			while (txt[i][j])
			{
				txt[i][j - 1] = txt[i][j];
				j++;
			}
			txt[i][j - 1] = '\0';
			txt[i] = getenv(txt[i]);
			if (!txt[i])
				return (1);
			j = 1;
		}
		i++;
	}
	return (0);
}

int	expand2(char *txt)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (txt[0] == '$')
	{
		while (txt[i])
		{
			txt[i - 1] = txt[i];
			j++;
		}
		txt[i - 1] = '\0';
		printf("txt '%s'", txt);
		txt = getenv(txt);
		if (!txt[i])
			return (1);
		i++;
	}
	return (0);
}

char	*literal(char *input)
{
	char	**tokens;
	char	**next;

	tokens = ft_split(input, '"');
	next = (char**)malloc(sizeof(char *) * 2);
    /*
    if (tokens[0])
        next[0] = (char *)malloc(sizeof(char) * ft_strlen(tokens[0]));
    if (tokens[1])
        next[1] = (char *)malloc(sizeof(char) * ft_strlen(tokens[1]));
    */
    //ft_strcpy(next[0], tokens[0]);
    //ft_strcpy(next[1], tokens[1]);
	if (!next[0] && !next[1])
		return ("");
	next[0] = tokens[0];
	next[1] = tokens[1];
	return (next[1]);
}

/*SI ESTAMOS DENTRO O FUERA DE "dobles" o 'simples'*/
/*Dobles: dentro inhibir menos $*/
/*Simples: dentro inhibir todo*/

/*ESTE ES EL PARSER*/

char	*new_parse(char *txt)
{
	int	count[2];
	int	flags[2];

	count[0] = 0;
	count[1] = 0;
	flags[0] = 1;
	flags[1] = 1;
	quote_d_count(txt, count);
	if ( (txt = quote_in_or_out_loop(txt, count, flags)) == NULL)
		return("echo -Minishell: echo: opened quotes");
	return(txt);
}

char	*new_quote_in_or_out_loop(char *txt, int *count, int *flags)
{
	int	i;
	int *j;

	i = 0;
	j = &i;
	while(txt[i] != '\0')
	{
		if(txt[i] == 39) // simples ' 39 ascci de '
		{	
			if((count[1] % 2 == 0 && count[1] > 0) && flags[0] != -1)//dentro, entramos simples (ignorar dentro las dobles)
			//if(flags[1] == 1 && flags[0] == 1) //además fuera de simples
			{
				flip_flag(txt, flags, count, 1);
				write(1, "simple in\n", 10);
				while(txt[i] != 39) // 39 es el ascii de '
				{
					if (txt[i] == '\0')
						return(NULL);
		
					write(1,".", 1);
					i++;
				}
				flip_flag(txt, flags, count, 1);
				write(1, "\nsimple out\n", 11);
			}
		}
		else if(txt[i] == 34) //34 es el ascci de ""
		{
			if((count[0] % 2 == 0 && count[0] > 0) && flags[1] != -1) //dentro, entramos dobles (ignorar dentro las simples)
			//if (flags[0] == 1 && flags[1] == 1)
			{	
				flip_flag(txt, flags, count, 0);
				write(1, "doble in\n", 9);
				while(txt[i] != 34)
				{
		
					if (txt[i] == 36) //36 es el ascci de $
					{
						txt = expand_vble(txt, j);
						i = i + (ft_strlen(txt) - size);
						size = ft_strlen(txt);
			
					}
					if (txt[i] == '\0')
					{
						return(NULL);
					}
					write(1,".", 1);
					i++;
				}
				flip_flag(txt, flags, count, 0);
			}
		}
		else if (txt[i] == 36) //36 es el ascci de $
			txt = expand_vble(txt, j);
		i++;
	}
	printf("   -> parse loop ::%s::\n", txt); //al final deberiamos tener ya el txt parseado, ojo con el trim, entre comillas se respetan los espacios
	if (count[0] > 0 || count[1] > 0)
		return(NULL);
	return(txt);
}

void	flip_flag(char *txt, int *flags, int *count, int *j, int f)
{
	flags[f] = flags[f] * -1;
	count[f]--;
	remove_quote(txt, i);
}

int	inside_simple(char *txt, int *flags, int *count, int *j)
{
	int i;

	i = *j;
	flags[1] = flags[1] * -1;
	count[1]--;
	remove_quote(txt, i);
	write(1, "simple in\n", 10);
	while(txt[i] != 39) // 39 es el ascii de '
	{
		if (txt[i] == '\0')
			return(1);
		
		write(1,".", 1);
		i++;
	}
	flags[1] = flags[1] * -1;
	count[1]--;
	remove_quote(txt, i);
	write(1, "\nsimple out\n", 11);
	return(0);
}

int	inside_doble(char *txt, int *flags, int *count, int *j)
{	
	int size;
	int i;

	size = ft_strlen(txt);
	i = *j;
	flags[0] = flags[0] * -1;
	count[0]--;
	remove_quote(txt, i);
	write(1, "doble in\n", 9);
	while(txt[i] != 34)
	{
		
		if (txt[i] == 36) //36 es el ascci de $
		{
			txt = expand_vble(txt, j);
			i = i + (ft_strlen(txt) - size);
			size = ft_strlen(txt);
			
		}
		if (txt[i] == '\0')
		{
			return(1); //return 1 y es caso de quotes abiertas
		}
		write(1,".", 1);
		i++;
	}
	flags[0] = flags[0] * -1;
	count[0]--;
	remove_quote(txt, i);
	write(1, "\ndoble out\n", 10);
	return(0);
}

void	quote_d_count(char *txt, int *count)
{
	int	i;

	i = 0;
	while(txt[i])
	{
		if(txt[i] == '"')
			count[0]++;
		//
		if(txt[i] == 39)
			count[1]++;
		i++;
	}
	//con count  sabemos si hay comillas (count > 0) y si alguna queda abierta count impar
}

void	remove_quote(char *txt, int init)
{
	int i;

	i = init + 1;
	while(txt[i])
	{
		txt[i -1] = txt[i];
		i++;
	}
	i--;
	txt[i] = '\0';
}

char *expand_vble(char *txt, int *init)
{
	char *value; //valor que tiene la vble tras el $
	char exp[999]; //el nuevo txt expandido
	int		i;
	int		j;
	int		add;

	i = 0;
	add = *init;
	while (txt[add] != ' ' && txt[add] != '\0' && txt[add] != '"' && txt[add] != '\'')
		add++;
	add = add - *init;
	value = search_vble_env(txt, *init);
	j = 0;
	ft_strncpy(exp, txt, *init);
	if(value != NULL)
	{
		while(value[j])
		{
			exp[*init + j] = value[j];
			j++;
		}
	}
	j = j + *init;
	exp[j] = ' ';
	exp[j + 1] = '\0';
	j++;
	i = *init + add;
	//while(txt[i] != '\0') //hasta terminar txt volvemos copiar el resto de txt
	while(txt[i])
	{
		i++;
		exp[j] = txt[i];
		j++;
	}
	exp[j] = '\0';
	txt = exp;
	//ft_strcpy(txt, exp);
	//printf("expanded ::%s::\n", txt);
	return(txt);
}

char    *search_vble_env(char *txt, int init)
{
	int	j;
	char vble[999];

	init++;
	j = 0;
	while (txt[init] != ' ' && txt[init] != '\0' && txt[init] != '"')
	{
		vble[j] = txt[init];
		j++;
		init++;
	}
	vble[j] = '\0';
	//tratar error, si no se encuentr la variable
	return (getenv((const char*)vble));
}
