#include "libft.h"

/*Crear y manejra la linked list*/
typedef struct token
{
	char*			content;
	struct token*	next;
	char			quotes; // s simples, d dobles, n nada
	char			direction;  // si lo siguiente es pipe p, redirección r o final f
} t_token



t_token  *create_token(char *txt) 
{
    t_token  *chope;
   
    chope = (t_token *)malloc(sizeof(t_token));
    chope->content = txt;
	quotes = NULL;
	direction = NULL;
    return(chope);
}

void    insert_token(t_token *token, t_token *choped_line) //last
{
    t_token  *temp;
    
    if (choped_line->next != NULL)
    {   
		while (choped_line != NULL)
		{
        	choped_line = choped_line->next;
		}
    }
	choped_line->next = node;
}

//Faltan funciones de liberar, free a cada malloc. Elimir nodos (tokens) y la lista (choped line)

/*Recorrer la linea de entrada, input, y crear tokens
usar funciones del anterior parse*/

char	*parse(char *input, t_token *choped) //pasar tambien la choped line vacia para ir rellenando
{
	int	count[2];
	int	flags[2];

	count[0] = 0;
	count[1] = 0;
	flags[0] = 1;
	flags[1] = 1;
	
	quote_d_count(input, count);
	if ( (txt = quote_in_or_out_loop(input, count, flags, choped)) == NULL)
	{
		g_num_quit = 1;
		return("echo -Minishell: echo: opened quotes");
	}
	return(input);
}

void	quote_d_count(char *txt, int *count)
{
	int	i;

	i = 0;
	while(txt[i] != '\0')
	{
		if(txt[i] == '"')
			count[0]++;
		if(txt[i] == 39)
			count[1]++;
		i++;
	}
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
	exp[j] = ' '; //problema!!
	exp[j + 1] = '\0';
	j++;
	i = *init + add;
	while(txt[i])
	{
		i++;
		exp[j] = txt[i];
		j++;
	}
	exp[j] = '\0';
	txt = exp;
	return(txt);
}

char    *search_vble_env(char *txt, int init)
{
	int	j;
	char vble[999];

	init++;
	j = 0;
	while (txt[init] != ' ' && txt[init] != '\0' && txt[init] != '"' && txt[init] != '\'')
	{
		vble[j] = txt[init];
		j++;
		init++;
	}
	vble[j] = '\0';
	if(str_cmp(vble, "?") == 0) //$? devuelve el exit status de la ultima ejecuciÃ³n
	{ 
		//return(ft_itoa(g_num_quit)); //retornar el status. ft_itoa sin 
		return("0"); 
	}
	return (getenv((const char*)vble));
}

void	flip_flag(char *txt, int *flags, int *count, int i, int f)
{
	int init;
	
	init = i;
	flags[f] = flags[f] * -1;
	count[f]--;
	remove_quote(txt, init);
}


char	*quote_in_or_out_loop(char *txt, int *count, int *flags, t_token *choped) //count numero de comillas
{
	int		i;
	int 	*j;
	char	*temp_text;
	t_token	*temp_token;

	i = 0;
	j = &i;
	while(txt[i] != '\0')
	{
		if(txt[i] == 39) // simples ' 39 ascci de '
		{	
			if((count[1] % 2 == 0 && count[1] > 0) && flags[0] != -1)//dentro, entramos simples (ignorar dentro las dobles)
			{
				flip_flag(txt, flags, count, i, 1);
				while(txt[i] != 39)
				{
					if (txt[i] == '\0')
						return(NULL);
					i++;
					temp_text++ = txt[i]; //añadir el caracter a la cadena temporal
				}
				flip_flag(txt, flags, count, i, 1);
				temp_token = create_token(temp_text);
				insert_token(temp_token, choped);//añadir la cadena como nuevo token y poner en el token que quote=s
			}
		}
		else if(txt[i] == 34) //34 es el ascci de ""
		{
			if((count[0] % 2 == 0 && count[0] > 0) && flags[1] != -1) //dentro, entramos dobles (ignorar dentro las simples)
			{	
				flip_flag(txt, flags, count, i, 0);
				while(txt[i] != 34)
				{
					if (txt[i] == 36) //36 es el ascci de $
					{
						txt = expand_vble(txt, j);
					}
					if (txt[i] == '\0')
						return(NULL);
					i++;
					temp_text = txt[i];
				}
				flip_flag(txt, flags, count, i, 0);
				temp_token = create_token(temp_text);
				insert_token(temp_token, choped); //añadir la cadena como nuevo token y poner en el token que quote=d
			}
		}
		else if (txt[i] == 36) //36 es el ascci de $
			txt = expand_vble(txt, j);
		else if (txt[i] == 39 || txt[i] == 34) //comillas que no cierran, opened quotes
			return(NULL);	
		temp_text = txt[i];
		temp_token = create_token(temp_text);
		insert_token(temp_token, choped); //añadir la cadena como nuevo token y poner en el token que quote=n //siguiente cortar por | y >< y split espacios 
		i++;
	}
	//if (txt[i] == 39 || txt[i] == 34)
	//	return(NULL);
	return(txt);
}

//Tratar los tokens.
//sin comillas cortar por espacios y expandir variables $ --> buscar primnera palabra que sea comando.
//comillas simples ignorar, dejar como están
//comillas dobles expandir vbles $
//buscar los pipes y redirecciones y cortar
//redireccionar

/*From split*/
static size_t	ft_get_line_size(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s && s++)
	{
		while (*s != c && *s)
			s++;
		count++;
		while (*s == c && *s)
			s++;
	}
	return (count);
}

static char	**ft_chope_add(const char *s, char **dst, size_t i, size_t len)
{
	dst[i] = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst[i])
	{
		while (i)
			free (dst[--i]);
		free(dst);
		return (NULL);
	}
	ft_strlcpy(dst[i], s - len, len + 1);
	return (dst);
}

char	**ft_chopedline(char const *s, char c)
{
	char	**dst;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	dst = (char **)malloc(sizeof(char *) * (ft_get_line_size(s, c) + 1));	
	if (!dst)
		return (NULL);
	i = 0;
	while (*s)
	{
		len = 0;
		while (*s != c && *s && ++s)
			len++;
		if (len > 0)
		{
			dst = ft_chope_add(s, dst, i, len);
			i++;
		}
		while (*s == c && *s)
			s++;
	}
	dst[i] = NULL;
	return (dst);
}
