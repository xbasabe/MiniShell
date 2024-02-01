#include "minishell.h"

/*
static size_t	ft_get_split_size(char const *s, char c);
int cut_or_pass(char c, int *flag);
static char	**ft_split_add(const char *s, char **dst, size_t i, size_t len);
char	**ft_flag_split(char const *s, char c);
*/

static size_t	ft_flag_get_split_size(char const *s, char c)
{
	size_t	count;
    int flag[2]; //[0] simples [1] dobles
    
    flag[0] = 1; // 1 fuera -1 dentro
    flag[1] = 1;
	count = 0;
	while (*s && s++)
	{
        while(cut_or_pass(*s, flag) == 0 && *s)
			s++;
		count++;
		while (*s == c && *s)
			s++;
	}
	return (count);
}

static char	**ft_flag_split_add(const char *s, char **dst, size_t i, size_t len)
{
	dst[i] = (char *)malloc(sizeof(char) * len + 1);
	if (!dst[i])
	{
		while (i)
			free (dst[--i]);
		free(dst);
		return (NULL);
	}
	ft_strlcpy(dst[i], s - len, len + 1); //original, mantener el strlcopy
    //strncpy(dst[i], s - len, len + 1); //Funciona
    //Aqui: quitar comillas y espacios fuera de comillas de las palabras
	return (dst);
}

char	**ft_flag_split(char const *s, char c)
{
	char	**dst;
	size_t	len;
	size_t	i;
    int flag[2]; //[0] simples [1] dobles
    
    flag[0] = 1; // 1 fuera -1 dentro
    flag[1] = 1;
	if (!s)
		return (NULL);
	dst = (char **)malloc(sizeof(char *) * (ft_flag_get_split_size(s, c) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (*s)
	{
		len = 0;
		//while (*s != c && *s && ++s)
        while(cut_or_pass(*s, flag) == 0  && *s && ++s)
            len++;
		if (len > 0)
		{
            dst = ft_flag_split_add(s, dst, i, len); //pone un espacioo de más al final?
			i++;
		}
		while (*s == c && *s)
			s++;
	}
	dst[i] = NULL;
	return (dst);
}

int cut_or_pass(char c, int *flag) //int 0 pass int 1 cut
{
    
    if(c == ' ' &&  flag[0] == 1 && flag[1] == 1) //es blank y no protegido (fuera comillas)
        return(1);
    if(c == '\'' && flag[1] == 1) //comillas simples fuera de dobles
        flag[0] = flag[0] * -1;
    if(c == '"' && flag[0] == 1) //comillas dobles fuera de simples
        flag[1] = flag[1] * -1;
    return(0); //por defecto dejamos pasar
}

/*
ft_rm_quote_blank(char *dst) //quitar comillas no pretegidas (de apertura y cierre) usar la funcion de expandir $
{
    char    *clean;
    char    *temp;
    int     len;
    int flag[2]; //[0] simples [1] dobles
    
    flag[0] = 1; // 1 fuera -1 dentro
    flag[1] = 1;

    len = 0;
    while( cut_or_pass(*dst, flag) == 0  && *dst && ++dst) //cut or pass 0, no protegida
        if(is blank or quote)
            len++; //ir avanzando
    llegamos a quote?
    copiamos hasta len en temp
    lo unimos a clean
    free temp
    pasamos la quote ++
    volvemos para copiar en temp
    la unimos a clean

    al final vevolvemos clean
        
}
*/
