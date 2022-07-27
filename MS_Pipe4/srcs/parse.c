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

char	*pipetoken(char *input, char *c)
{
	int		len = 0, i = 0;
	char	*first;
	char	**words;

	words = ft_split(input, ' ');
	while (words[i])
	{
		if (str_cmp(words[i], c) == 0)
			break ;
		len = len + ft_strlen(words[i]);
		i++;
	}
	len = len + i;
	first = (char *)malloc(sizeof(char) * len);
	ft_strlcpy(first, input, len);
	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
    //printf("   first cmd: '%s'\n", first);
	return (first);
}

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

/*

char	**parse_split(char *input, char c)
{
	char **splited;

	splited = (char **)malloc(sizeof(char*) * count_words(input));
	malloc_split(input,splited, 0);
	fill(input, splited, 0);

}

int count_words(char *str)
{
	int count;

	count = 0;
	while(*str)
	{
		while(*str == '\t' || *str == 32)
			str++;
		while(*str >32 && *str && *str <127)
			str++; //aqui condicion de ver si empieza por comillas y termina comillas
		count++;
	}
	return(count);
}

void	fill(char *str, char **word, int index)
{
        int i, c, j;

        i = index;
		c = 0;
		j = 0;
        while(str[i])
        {
                while(str[i] == '\t' || str[i] == 32)
                        i++;
                while(str[i] >32 && str[i] && str[i] <127 )
		{        
			word[j][c] = str[i];
			i++;
			c++;
		}	
		j++;
		c = 0;
        }
}

void	malloc_split(char *entry, char **splited, int index)
{
        int i, c, j;

        i = index;
        c = 0;
        j = 0;
        while(entry[i])
        {
                while(entry[i] == '\t' || entry[i] == 32)
                        i++;
                while(entry[i] >32 && entry[i] && entry[i] <127 )
                {
                        i++;
                        c++;
                }
                splited[j] = (char *)malloc(sizeof(char) * c);
                j++;
                c = 0;
        }
}

*/