/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:10:50 by xbasabe-          #+#    #+#             */
/*   Updated: 2024/02/17 14:06:20 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

static char	**liner(char *txt, int *count, int *flags);
char		*liner_simp(char *txt, int *count, int *flags, int *i, int *j);
char		*liner_dob(char *txt, int *count, int *flags, int *i, int *j);

char	**input_to_lines(char *txt)
{
	int		count[2];
	int		flags[2];
	char	**lines;

	count[0] = 0;
	count[1] = 0;
	flags[0] = 1;
	flags[1] = 1;
	quote_d_count(txt, count);
	if (opened_quotes(txt, count, flags) == 0)
	{
		g_shell.num_quit = 1;
		lines = (char **)malloc((sizeof(char **) * 2));
		lines[0] = (char *)malloc(sizeof(char) * 38);
		strcpy(lines[0], "echo -Minishell: echo: opened quotes\n");
		lines[1] = NULL;
		return (lines);
	}
	else
		lines = liner(txt, count, flags);
	return (lines);
}

static char	**liner(char *txt, int *count, int *flags)
{
	int		i;
	int		j;
	int		c_lines;
	char	temp_text[500];
	char	**lines;

	i = 0;
	j = 0;
	c_lines = 0;
	lines = (char **)malloc(sizeof(char *) * 50);
	while (txt && txt[i] != '\0')
	{
		temp_text[j] = txt[i];
		if (txt[i] == 39)
		{
			if (flags[0] == 1 && flags[1] == 1)
			{
				temp_text[j] = txt[i];
				flop_flag(flags, count, 0);
				while (txt[++i] != 39)
				{
					if (txt[i] == '\0')
						return (NULL);
					temp_text[++j] = txt[i];
				}
				temp_text[++j] = txt[i];
				flop_flag(flags, count, 0);
			}
		}
		else if (txt[i] == 34)
		{
			if (flags[0] == 1 && flags[1] == 1)
			{
				temp_text[j] = txt[i];
				flop_flag(flags, count, 1);
				while (txt[++i] != 34)
				{
					if (txt[i] == '\0')
						return (NULL);
					temp_text[++j] = txt[i];
				}
				flop_flag(flags, count, 1);
				temp_text[++j] = txt[i];
			}
		}
		else if (is_line_cut(txt, &i) == 0)
		{
			temp_text[j] = '\0';
			lines[c_lines] = (char *)malloc(sizeof(char) * 999); //ft_strelen de tem_text
			strcpy(lines[c_lines], temp_text); //cambiar por ft_strcpy
			temp_text[0] = '\0'; //reinicio alternativo
			j = 0;
			i++;
			c_lines++;
		}
		temp_text[j] = txt[i];
		i++;
		j++;
	}
	temp_text[j] = '\0';
	lines[c_lines] = (char *)malloc(sizeof(char) * (ft_strlen(temp_text) + 1));
	strcpy(lines[c_lines], temp_text);
	temp_text[0] = '\0';
	c_lines++;
	lines[c_lines] = (char *)malloc(sizeof(char) * 1);
	lines[c_lines] = "\0";
	return (lines);
}


char	*liner_simp(char *txt, int *count, int *flags, int *i, int *j)
{
	char	*tp;
	int		init;
	
	init = *i;
	if (flags[0] == 1 && flags[1] == 1)
	{
		(*i)++;
		(*j)++;
		//temp_text[j] = txt[i]; //comilla entrada
		flop_flag(flags, count, 0);
		while (txt[(*i)] != 39)
		{
			(*i)++;
			(*j)++;
		}
		(*i)++;
		(*j)++;
		flop_flag(flags, count, 0);
	}
	tp = (char *)malloc(sizeof(char) * (*i - init + 3));
	ft_strilcpy(tp, txt, init, *i);
	return (tp);
}

char	*liner_dob(char *txt, int *count, int *flags, int *i, int *j) //cambiar init por pasar j en int[i, j]
{
	char	*tp;
	int		init;
	int		iner;
	
	init = *i;
	iner = 0;
	tp = NULL;
	if (flags[0] == 1 && flags[1] == 1)
	{
		(*i)++;
		(*j)++;
		iner++;
		flop_flag(flags, count, 0);
		while (txt[(*i)] != 34)
		{
			(*i)++;
			(*j)++;
			iner++;
		}
		(*i)++;
		(*j)++;
		iner++;
		flop_flag(flags, count, 0);
	}
	printf("dob i%d j%d iner%d init%d\n", *i, *j, iner, init);
	tp = (char *)malloc(sizeof(char) * (iner + 3));
	tp = ft_striscpy(tp, txt, init, iner);
	//printf("liner dob tp %s", tp);
	return(tp);
}


void	new_line(char **lines, int *i, int *j, int *c_lines, char *temp_text, char *txt)
{
	char *tp;

	printf("Contadores new line i%d  j%d\n", *i, *j);
	//tp = (char *)malloc(sizeof(char) * (*i - *j + 3)); //volcar a tp e texto 'acumulado'
	//ft_strilcpy(tp, txt, *j, *i);
	tp = (char *)malloc(sizeof(char) * (*j + 2)); //volcar a tp e texto 'acumulado'
	ft_strlcpy(tp, txt, *j);

	if(temp_text != NULL)
		temp_text = ft_strjoin(temp_text, tp);
	else
		ft_strcpy(temp_text, tp);
	printf("new line %s\n", temp_text);
	lines[*c_lines] = (char *)malloc(sizeof(char) * ft_strlen(temp_text)); //ft_strelen de tem_text
	strcpy(lines[*c_lines], temp_text); //cambiar por ft_strcpy
	//temp_text[0] = '\0'; //reinicio alternativo
	temp_text = NULL;
	*j = 0;
	(*i)++;
	(*c_lines)++;
	printf("liner dob tp %s\n", tp);
}

void	last_line(char **lines, int *i, int *j, int *c_lines, char *temp_text, char *txt)
{
	//char *tp;

	printf("Contadores last line i%d  j%d\n", *i, *j);
	printf("last line tmp_text %s\n", temp_text);
	(void)txt;
	//tp = (char *)malloc(sizeof(char) * (*i - *j + 3)); //volcar a tp e texto 'acumulado'
	//ft_strilcpy(tp, txt, *j, *i);
	//tp = (char *)malloc(sizeof(char) * (*i + 2)); //volcar a tp e texto 'acumulado'
	//ft_strlcpy(tp, txt, *i);
	//temp_text = ft_strjoin(temp_text, tp);
	
	lines[*c_lines] = (char *)malloc(sizeof(char) * (ft_strlen(temp_text) + 1)); //ft_strelen de tem_text
	strcpy(lines[*c_lines], temp_text); //cambiar por ft_strcpy
	//temp_text[0] = '\0'; //reinicio alternativo
	temp_text = NULL;
	(*c_lines)++;
	lines[*c_lines] = (char *)malloc(sizeof(char) * 1);
	lines[*c_lines] = "\0";
	*j = 0;
	(*i)++;
	(*c_lines)++;
}
/*
static char	**liner(char *txt, int *count, int *flags) //new_liner
{
	int		i;
	int		j;
	int		c_lines;
	char	*temp_text; //primer malloc del tamaño de txt
	char	**lines;

	i = 0;
	j = 0;
	c_lines = 0;
	lines = (char **)malloc(sizeof(char *) * 50); //50 es arbitrario
	temp_text = (char *)malloc(sizeof(char) * ft_strlen(txt));
	while (txt && txt[i] != '\0')
	{
		temp_text[j] = txt[i];
		if (txt[i] == 39)
			temp_text = ft_strjoin(temp_text, liner_simp(txt, count, flags, &i, &j));
		else if (txt[i] == 34)
			temp_text = ft_strjoin(temp_text, liner_dob(txt, count, flags, &i, &j));
		else if (is_line_cut(txt, &i) == 0)
			new_line(lines, &i, &j, &c_lines, temp_text, txt);
		//temp_text[j] = txt[i]; //esto se cuento y lo acumulado se mete en is line cut
		i++;
		j++;
	}
	last_line(lines, &i, &j, &c_lines, temp_text, txt);
	//
	temp_text[j] = '\0';
	lines[c_lines] = (char *)malloc(sizeof(char) * (ft_strlen(temp_text) + 1));
	strcpy(lines[c_lines], temp_text);
	temp_text[0] = '\0';
	c_lines++;
	lines[c_lines] = (char *)malloc(sizeof(char) * 1);
	lines[c_lines] = "\0";
	//
	return (lines);
}
*/
