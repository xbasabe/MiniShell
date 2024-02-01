
#include "minishell.h"
#include <string.h>

static char const *redirect_type(char *txt, int *i);

char **input_to_lines(char *txt, char *rd) //pasar un array para devolve las redirecciones
{
	int     count[2];
	int     flags[2];
    char    **lines;

	count[0] = 0;
	count[1] = 0;
	flags[0] = 1;
	flags[1] = 1;
	
	quote_d_count(txt, count); //inicializar count y flags como para parser
	if (opened_quotes(txt, count, flags) == 0)
	{
		g_shell.num_quit = 1; //registrar el error en le vble global
		lines = (char**)malloc(sizeof(char*)*2);
		lines[0] = (char*)malloc(sizeof(char)*40);
		strcpy(lines[0], "echo -Minishell: echo: opened quotes");
		lines[1] = (char*)malloc(sizeof(char)*1);
		strcpy(lines[1], "\0");
		return(lines);
	}
    else
	{
		lines = get_lines(txt, count, flags, rd);
	}
	printf("redirecciones %s\n", rd);
	return(lines);
}

void	flop_flag(int *flags, int *count, int f) //version de flip-flag sin quitar las comillas
{
	flags[f] = flags[f] * -1;
	count[f]--;
}

char	**get_lines(char *txt, int *count, int *flags, char *rd) //count numero de comillas
{
	int		i; //txt index
	int 	j; //temp_text index
    int     c_lines; //lines index
	char	temp_text[500];
    char    **lines;

	i = 0;
	j = 0;
	c_lines = 0;
	lines = (char**)malloc(sizeof(char*) * 50); //o contar?
	while(txt && txt[i] != '\0')
	{
		temp_text[j] = txt[i];
		if(txt[i] == 39) // simples ' 39 ascci de '
		{	
			if(flags[0] == 1 && flags[1] == 1)
			{
				temp_text[j] = txt[i]; // guardamos la comilla
				flop_flag(flags, count, 0);
				while(txt[++i] != 39)
				{
					if (txt[i] == '\0')
						return(NULL);
					temp_text[++j] = txt[i]; //añadir el caracter a la cadena temporal
				}
				temp_text[++j] = txt[i];
				flop_flag(flags, count, 0);
			}
		}
		else if(txt[i] == 34) //34 es el ascci de ""
		{
			if( flags[0] == 1 && flags[1] == 1)
			{	
				temp_text[j] = txt[i]; // guardamos la comilla
				flop_flag(flags, count, 1);
				while(txt[++i] != 34)
				{
					if (txt[i] == '\0')
						return(NULL);
					temp_text[++j] = txt[i];
				}
				flop_flag(flags, count, 1);
				temp_text[++j] = txt[i];
			}
		}
        //iterar fuera de comillas, cortar por | < > y crear la lines[i] con el texto temp_text acumulado
		else if(is_line_cut(txt, &i) == 0)
        {
		    temp_text[j] = '\0';
			lines[c_lines] = (char*)malloc(sizeof(char) * 999); //ft_strelen de tem_text
            strcpy(lines[c_lines], temp_text); //cambiar por ft_strcpy
            //temp_text == NULL; //reiniciar
			rd = ft_strjoin(rd, redirect_type(txt, &i));
			temp_text[0] = '\0'; //reinicio alternativo
			j = 0; //reinicio contador de temp_text
			i++;
			c_lines++;
        }
		temp_text[j] = txt[i];
		i++;
        j++;
	}
	temp_text[j] = '\0';
	lines[c_lines] = (char*)malloc(sizeof(char) * (ft_strlen(temp_text) + 1));
    strcpy(lines[c_lines], temp_text); //strdup?
	temp_text[0] = '\0';
	c_lines++;
	lines[c_lines] = (char*)malloc(sizeof(char) * 1);
	lines[c_lines] = "\0";
	//strcpy(lines[c_lines], "");
	return(lines);
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
				//while(txt[i] != 39)
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
	if(c == '<')
		return(0);
	if(c == '>')
		return(0);
	else if(c == '<' && next == '<') //HEREDOC
	{
		*i = *i + 1;
		return(0);
	}
	//else if(c == '>' && next == '>') //esta opcion ver si la pide el subjct
	return(1);
}

char	*line_quotes_pre_split(char *txt)
{
	int		i;
	int		flags[2];
	char	*q_line;
	char	temp[999];

	i = 0;
	flags[0] = 1;
	flags[1] = 1;
	q_line = (char *)malloc((sizeof(char *) * 1)); //de un caracter y le hacemos joint
	q_line[0] = ' ';
	while (txt && txt[i] != '\0')
	//while(txt && (txt[i] != '\0' ) && (i < (int)ft_strlen(txt)))
	{
		if (txt[i] == 39) // simples ' 39 ascci de '
		{
			//ft_strjoin(q_line, split_tokens_simples(flags, txt, &i));
			//printf("  sim q_line -%s-\n", q_line);
			ft_strcpy(temp, split_tokens_simples(flags, txt, &i));
			printf("  simples q_line -%s-\n", temp);
			q_line = ft_strjoin(q_line, temp);
			temp[0] = '\0';
		}
		else if (txt[i] == 34) //34 es el ascci de ""
		{
			//ft_strjoin(q_line, split_tokens_doubles(flags, txt, &i));
			//printf("  dob q_line -%s-\n", q_line);
			ft_strcpy(temp, split_tokens_doubles(flags, txt, &i));
			printf("  double q_line -%s-\n", temp);
			q_line = ft_strjoin(q_line, temp);
			temp[0] = '\0';
		}
		//else if (txt[i] != ' ')
		else
		{
			//q_line = ft_strjoin(q_line, split_tokens_out(flags, txt, &i));
			//printf("  out q_line -%s-\n", q_line);
			ft_strcpy(temp, split_tokens_out(flags, txt, &i));
			printf("  out q_line -%s-\n", temp);
			q_line = ft_strjoin(q_line, temp);
			temp[0] = '\0';
		}
		i++;
		//q_line = ft_strjoin(q_line, " ");
		if(i == ((int)ft_strlen(txt) - 1))
			break;
		if(!txt)
			break;
	}
	ft_strjoin(q_line, "\0");
	return (q_line);
}

static char const *redirect_type(char *txt, int *i) //pasar el node de stack y marcar que se hace con la salida
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
