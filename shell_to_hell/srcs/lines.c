
#include "minishell.h"

char **input_to_lines(char *txt)
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
		lines = get_lines(txt, count, flags);
	}
	return(lines);
}

void	flop_flag(int *flags, int *count, int f) //version de flip-flag sin quitar las comillas
{
	flags[f] = flags[f] * -1;
	count[f]--;
	//remove_quote(txt, init); las comillas deben seguir para prsear las lineas
}

char	**get_lines(char *txt, int *count, int *flags) //count numero de comillas
{
	int		i; //txt index
	int 	j; //temp_text index
    int     c_lines; //lines index
	char	temp_text[500];
    char    **lines;

	i = 0;
	j = 0;
	c_lines = 0;
	lines = (char**)malloc(sizeof(char*) * 50);
	while(txt && txt[i] != '\0')
	{
		temp_text[j] = txt[i];
		if(txt[i] == 39) // simples ' 39 ascci de '
		{	
			
			//if((count[1] % 2 == 0 && count[1] > 0) && flags[0] != -1)//dentro, entramos simples (ignorar dentro las dobles)
			//if((count[0] > 0) && flags[0] != -1 && flags[1] != -1)
			if(flags[0] == 1 && flags[1] == 1)
			{
				flop_flag(flags, count, 0);
				while(txt[++i] != 39)
				{
					if (txt[i] == '\0')
						return(NULL);
					temp_text[++j] = txt[i]; //añadir el caracter a la cadena temporal
				}
				flop_flag(flags, count, 0);
			}
		}
		else if(txt[i] == 34) //34 es el ascci de ""
		{
			
			//if((count[0] % 2 == 0 && count[0] > 0) && flags[1] != -1) //dentro, entramos dobles (ignorar dentro las simples)
			//if((count[1] > 0) && flags[0] != -1 && flags[1] != -1)
			if( flags[0] == 1 && flags[1] == 1)
			{	
				temp_text[j] = txt[i]; // guardamos la coma
				flop_flag(flags, count, 1);
				while(txt[++i] != 34)
				{
					if (txt[i] == '\0')
						return(NULL);
					temp_text[++j] = txt[i];
				}
				flop_flag(flags, count, 1);
			}
		}
        //iterar fuera de comillas, cortar por | < > y crear la lines[i] con el texto temp_text acumulado
        //else if(txt[i] == '|' )
		else if(is_line_cut(txt, i) == 0)
        {
    		
		    temp_text[j] = '\0';
			//printf("  get lines: pipe: %d\n", i);
			lines[c_lines] = (char*)malloc(sizeof(char) * 999);
            strcpy(lines[c_lines], temp_text); //cambiar por ft_strcpy
			//printf("     LINE[%d] %s\n", c_lines, lines[c_lines]);
            //temp_text == NULL; //reiniciar
			temp_text[0] = '\0'; //reinicio alternativo
			j = 0; //reinicio contador de temp_text
			i++;
			c_lines++;
        }
		temp_text[j] = txt[i];
        //si llegamos a pipe, lo acumulado en temp_text a lines, crear contador de lines.
		i++;
        j++;
	}
	temp_text[j] = '\0';
	lines[c_lines] = (char*)malloc(sizeof(char) * (ft_strlen(temp_text) + 1));
    strcpy(lines[c_lines], temp_text); //strdup?
	//printf("     LINE[%d] %s\n", c_lines, lines[c_lines]);
	temp_text[0] = '\0';
	//probar words o split tokens
	line_to_words(lines[0]);
	split_tokens(lines[0]);
	//vuelve al codigo line
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
			//if((count[0] % 2 == 0 && count[0] > 0) && flags[1] != -1)//dentro, entramos simples (ignorar dentro las dobles)
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
			//if((count[1] % 2 == 0 && count[1] > 0) && flags[0] != -1) //dentro, entramos dobles (ignorar dentro las simples)
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

int	is_line_cut(char *txt, int i)
{
	char	c;
	char	next;

	c = txt[i];
	if (txt[i + 1])
		next = txt[i + 1];
	if(c == '|' || c == '<' || c == '>')
		return(0);
	else if(c == '<' && next == '<')
		return(0);
	else if(c == '>' && next == '>') //esta opcion ver si la pide el subjct
		return(0);
	return(1);
}
