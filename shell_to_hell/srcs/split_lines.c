
#include "minishell.h"

char	**split_lines(char *txt)
{
	int		i; //contador para recorrer txt
	int		flags[2];
	char	**lines;
	char	temp[999];
	int		d;
	int		c; //contador de lineas

	i = 0;
	d = 0;
	c = 0;
	flags[0] = 1;
	flags[1] = 1;
	lines = (char **)malloc((sizeof(char *) * 20)); //20 pipes, arbitrario, podria cascar
	while (txt && txt[i] != '\0')
	{
		if (txt[i] == '\'') // simples ' 39 ascci de '
			//ft_strcpy(temp, split_lines_simples(flags, txt, &i, &d));
			ft_strjoin(temp, split_lines_simples(flags, txt, &i, &d));
		else if (txt[i] == '\"') //34 es el ascci de ""
			//ft_strcpy(temp, split_lines_doubles(flags, txt, &i, &d));
			ft_strjoin(temp, split_lines_doubles(flags, txt, &i, &d));
		//else if(txt[i] != '\0')
		//	ft_strjoin(temp, split_lines_out(txt, &i, &d));
		
		else if (txt[i] == '|' || txt[i] == '>' || txt[i] == '<')
		{
			remove_quote(txt, i);
			temp [d] = '\0';
			lines[c] = ft_strdup(temp);
			c++;
			d = 0;
		}
		temp[d] = txt[i];
		
		i++;
		d++;
		temp[d] = '\0';
		//printf(" spli lines: temp va: %s\n", temp);
		lines[c] = ft_strdup(temp);
		//lines[c + 1] = NULL;
	}
	//temp[d] = '\0';
	//lines[c] = ft_strdup(temp);
	lines[c + 1] = NULL;
	return (lines);
}

char	*split_lines_simples(int *flags, char *txt, int *i, int *d) // en vez de i para que se actualize y *d
{	
	char	*temp;
	
	temp = NULL;
	temp = (char *)malloc(sizeof(char) * ft_strlen(txt) + 1);
	if (flags[0] != -1 && flags[1] != -1)//dentro, entramos simples (ignorar dentro las dobles)
	{
		flag_flop(flags, i, 1);
		while (txt[*i] != 39) // 39 es el ascii de '
		{
			//temp[*d] = txt[*i];
			if (txt[*i] == '\0')
			{
				g_shell.num_quit = 1;
				return ("NULL"); //igual mejor return NULL y sacar opened quotes en el split_tokens
				//exit(1);
			}	
			*i = *i + 1;
			*d = *d + 1;
		}
		flag_flop(flags, i, 1);
	}
	temp[*d] = '\0';
	ft_strilcpy(temp, txt, *i - *d, *d);
	printf("   devuelve lines simple:%s\n", temp);
	return(temp);
}

char	*split_lines_doubles(int *flags, char *txt, int *i, int *d) // en vez de i para que se actualize y *d
{
	char	*temp;
	int		init;
	int		len = 1;

	temp = NULL;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(txt) + 2));
	init = *i;
	*d = 0;
	printf(" entramos dobles con txt %c.\n", txt[*i]);
	temp[*d] = txt[*i];
	if (flags[1] != -1 && flags[0] != -1) //dentro, entramos dobles (ignorar dentro las simples)
	{
		flags[0] = flags[0] * -1;
		//flag_flop(flags, i, 0);
		temp[*d] = txt[*i];
		*i = *i + 1;
		*d = *d + 1;
		while (txt[*i] != 34)
		{
			temp[*d] = txt[*i];
			printf("double %c.\n", txt[*i]);
			if (txt[*i] == '\0')
			{
				g_shell.num_quit = 1;
				//exit(1);
				return ("NULL");
			}
			*i = *i + 1;
			*d = *d + 1;
			len++;
		}
		//printf("  el temp va: %s", temp);
		flags[0] = flags[0] * -1;
		//flag_flop(flags, i, 0);
	}
	//temp[*d] = '\0';
	//*d = *d + 1;
	//temp[*d] = '\"';
	*d = *d +1;
	temp[*d] = '\0';
	//ft_strilcpy(temp, txt, init, len);
	//printf(" salimos dobles con temp %c.\n", temp[*d]);
	printf("   devuelve lines dobles:%s\n", temp);
	return(temp);
}

char	*split_lines_out(char *txt, int *i, int *d) // fuera de comillas
{
	char	*temp;
	int		init;
	int len = 0;

	temp = (char *)malloc(sizeof(char) * (ft_strlen(txt) + 1));
	init = *i;
	while ((txt[*i] != '|' || txt[*i] != '>' || txt[*i] != '<') && txt[*i] != '\0' )
	{
		//temp[*d] = txt[*i];
		if (txt[*i] == '\0')
		{
			g_shell.num_quit = 1;
			//exit(1);
			//return ("NULL");
			return(temp);
		}
		*i = *i + 1;
		*d = *d + 1;
		len ++;
	}
	//temp[*d] = '\0';
	ft_strilcpy(temp, txt, init, len);
	printf("   devuelve lines out:%s\n", temp);
	return(temp);
}

void	flag_flop(int *flags, int *i, int f)
{
	int	init;

	init = *i;
	flags[f] = flags[f] * -1;
}

size_t	ft_strilcpy(char *dst, const char *src, int from, size_t dstsize)
{
	size_t	i;
	size_t	src_size;

	src_size = 0;
	while (src[src_size] != '\0')
		src_size++;
	if (dstsize == 0)
		return (src_size);
	i = from;
	while (i < dstsize && src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (i == dstsize)
		dst[dstsize - 1] = '\0';
	else
		dst[i] = '\0';
	return (src_size);
}


/*

char	*split_lines_doubles(int *flags, char *txt, int *i, int *d) // en vez de i para que se actualize y *d
{
	char	*temp;

	temp = NULL;
	if (flags[1] != -1 && flags[0] != -1) //dentro, entramos dobles (ignorar dentro las simples)
	{
		flags[0] = flags[0] * -1;
		//flag_flop(flags, i, 0);
		while (txt[*i] != 34)
		{
			temp[*d] = txt[*i];
			if (txt[*i] == '\0')
			{
				g_shell.num_quit = 1;
				//exit(1);
				return ("NULL");
			}
			*i = *i + 1;
			*d = *d + 1;
		}
		flags[0] = flags[0] * -1;
		//flag_flop(flags, i, 0);
	}
	//temp[*d] = '\0';
	printf("   devuelve lines dobles:%s\n", temp);
	return(temp);
}
*/