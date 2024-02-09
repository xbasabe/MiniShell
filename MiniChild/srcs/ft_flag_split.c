#include "minishell.h"

/*
static size_t	ft_get_split_size(char const *s, char c);
int cut_or_pass(char c, int *flag);
static char	**ft_split_add(const char *s, char **dst, size_t i, size_t len);
char	**ft_flag_split(char const *s, char c);
*/
//static ft_rm_quote_word(char *dst);

static size_t	ft_flag_get_split_size(char const *s, char c)
{
	size_t	count;
    int		flag[2];//[0] simples [1] dobles
    
    flag[0] = 1; // 1 fuera -1 dentro
    flag[1] = 1;
	count = 0;
	while (*s && s++)
	{
        while (cut_or_pass(*s, flag) == 0 && *s)
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
	ft_strlcpy(dst[i], s - len, len + 1);
	return (dst);
}

/*[0] simples [1] dobles*/
/*1 fuera, -1 dentro*/
char	**ft_flag_split(char const *s, char c)
{
	char	**dst;
	size_t	len;
	size_t	i;
    int		flag[2];
    
    flag[0] = 1;
    flag[1] = 1;
	if (!s)
		return (NULL);
	dst = (char **)malloc(sizeof(char *) * (ft_flag_get_split_size(s, c) + 2));
	if (!dst)
		return (NULL);
	i = 0;
	while (*s)
	{
		len = 0;
		while (cut_or_pass(*s, flag) == 0  && *s && ++s)
            len++;
		if (len > 0)
		{
            dst = ft_flag_split_add(s, dst, i, len);//pone un espacioo de más al final?
			i++;
		}
		while (*s == c && *s)
			s++;
	}
	dst[i] = NULL;
	return (dst);
}

int	cut_or_pass(char c, int *flag)//int 0 pass int 1 cut
{
    if (c == ' ' && flag[0] == 1 && flag[1] == 1)//es blank y no protegido (fuera comillas)
        return(1);
    else if (c == '\'' && flag[1] == 1)//comillas simples fuera de dobles
    {  
		flag[0] = flag[0] * -1;
	}
    else if (c == '"' && flag[0] == 1)//comillas dobles fuera de simples
	{
		flag[1] = flag[1] * -1;
	}	
    return (0);
}

char	*ft_flag_expand(char *s) // contar $ e iterar
{
	int	count;
	int i;
	
	count = 0;
	i = 0;
	while (s[i] && s[i] != '\0')
	{
		if (s[i] == '$')
			count++;
		i++;
	}
	if (count == 0)
		return (s);
	while (count-- > 0)
	{
		s = expand_vble_lines(s, 0);
	}
	return (s);
}

int	expand_or_not(char c, int *flag) //no deberia proteger $ de las comillas dobles, solamente de simples
{
	if (c == '$' &&  flag[0] == 1)  // vble fuera comillas simples
        return(1);
	else if (c == '\'' && flag[1] == 1) //comillas simples fuera de dobles
    {  
		flag[0] = flag[0] * -1;
	}
    return (0);
}

int	rm_or_not(char c, int *flag, int *count) //no deberia proteger $ de las comillas dobles, solamente de simples
{
	if (c == 39 && flag[0] == 1 && flag[1] == 1 && count[0] == 2)//comillas simples fuera de dobles
	{  
		count[0]--;
		flag[0] = flag[0] * -1;
		return(3);
	}
	else if (c == 39 && count[0] == 1 && flag[0] == -1)//comillas simples fuera de dobles
	{  
		flag[0] = flag[0] * -1;
		return(3);
	}
    else if (c == 34 && flag[1] == 1 && flag[0] == 1 && count[1] == 2) //comillas dobles fuera de simples
	{
		count[1]--;
		flag[1] = flag[1] * -1;
		return (3);
	}
	else if (c == 34 && count[1] == 1 && flag[1] == -1)//comillas simples fuera de dobles
	{  
		flag[1] = flag[1] * -1;
		return (3);
	}
    return (0);
}

char *ft_flag_rm_quotes(char *word)
{
	char	*clean;
	int		flag[2];
	int		i;
	int		j;
	int		count[2];
	
	count[0] = 2;
	count[1] = 2;
	flag[0] = 1;
	flag[1] = 1;
	i = 0;
	j = 0;
	clean = (char*)malloc(sizeof(char) * (strlen(word) + 1));
	while (word[i])
	{
		if (rm_or_not(word[i], flag, count) == 0)
		{
			clean[j] = word[i];
			j++;
		}
		i++;
	}
	if (j > 0)
		clean[j] = '\0';
	return (clean);
}
