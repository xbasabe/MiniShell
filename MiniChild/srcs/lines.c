#include "minishell.h"
#include <string.h>

static char	**liner(char *txt, int *count, int *flags);

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

void	inside_simple_quotes(char *txt, int *flags, int *i, int *j, char *temp_text)
{
    flags[0] = flags[0] * -1;
    while (txt[++(*i)] != 39)
        temp_text[++(*j)] = txt[*i];
    flags[0] = flags[0] * -1;
	temp_text[++(*j)] = txt[*i];
}

void	inside_double_quotes(char *txt, int *flags, int *i, int *j, char *temp_text)
{
    flags[1] = flags[1] * -1;
    while (txt[++(*i)] != 34)
        temp_text[++(*j)] = txt[*i];
    flags[1] = flags[1] * -1;
	temp_text[++(*j)] = txt[*i];
}

void	process_pipe(char *temp_text, char **lines, int *c_lines, int *j, int *i)
{
    temp_text[*j] = '\0';
	
    lines[*c_lines] = (char *)malloc(sizeof(char) * (ft_strlen((const char *)temp_text) + 1));
    strcpy(lines[*c_lines], temp_text);
    temp_text[0] = '\0';
    *j = 0;
    (*c_lines)++;
	(*i)++;
}

char	**get_lines(char *txt, int *flags)
{
	int		i;
	int 	j;
    int     c_lines;
	char	temp_text[500];
    char    **lines;

	i = 0;
	j = 0;
	c_lines = 0;
	lines = (char**)malloc(20);
	while (txt && txt[i] != '\0')
	{
		temp_text[j] = txt[i];
		if (txt[i] == 39)
			if (flags[0] == 1 && flags[1] == 1)
				inside_simple_quotes(txt, flags, &i, &j, temp_text);
		if (txt[i] == 34)
			if (flags[0] == 1 && flags[1] == 1)
				inside_double_quotes(txt, flags, &i, &j, temp_text);
        if (txt[i] == '|' )
			process_pipe(temp_text, lines, &c_lines, &j, &i);
		temp_text[j] = txt[i];
		i++;
        j++;
	}
	temp_text[j] = '\0';
	lines[c_lines] = (char*)malloc(sizeof(char) * (ft_strlen((const char*)temp_text) + 1));
    ft_strcpy(lines[c_lines], temp_text);
	lines[c_lines++] = NULL;
	return (lines);
}

static char	**liner(char *txt, int *count, int *flags)
{
	int		i;
	int 	j;
    int     c_lines;
	char	temp_text[500];
    char    **lines;

	i = 0;
	j = 0;
	c_lines = 0;
	lines = (char**)malloc(sizeof(char*) * 50);
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
			lines[c_lines] = (char*)malloc(sizeof(char) * 999); //ft_strelen de tem_text
            strcpy(lines[c_lines], temp_text); //cambiar por ft_strcpy
            //temp_text == NULL; //reiniciar
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
	lines[c_lines] = (char*)malloc(sizeof(char) * (ft_strlen(temp_text) + 1));
    strcpy(lines[c_lines], temp_text);
	temp_text[0] = '\0';
	c_lines++;
	lines[c_lines] = (char*)malloc(sizeof(char) * 1);
	lines[c_lines] = "\0";
	return (lines);
}
