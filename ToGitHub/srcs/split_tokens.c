
#include "minishell.h"

/*
static char	**token_add(const char *s, char **dst, size_t i, size_t len)
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
*/
void	flag_change(char *txt, int *flags, int i, int f)
{
	int	init;

	init = i;
	flags[f] = flags[f] * -1;
	remove_quote(txt, init);
}

char	**split_tokens(char *txt)
{
	int		i;
	int		*j;
	int		flags[2];
	char	**tokens;
	char	*temp;
	int		d;
	int		c;

	i = 0;
	j = &i;
	c = 0;
	flags[0] = 1;
	flags[1] = 1;
	temp = (char *)malloc(sizeof(char) * ft_strlen(txt) + 1);
	//temp = NULL;
	//args = (char **)malloc((sizeof(char *) * 1) + 1);
	tokens = (char **)malloc((sizeof(char *) * 20));
	while (txt[i] != '\0')
	{
		if (txt[i] == 39) // simples ' 39 ascci de '
		{
			if (flags[0] != -1 && flags[1] != -1)//dentro, entramos simples (ignorar dentro las dobles)
			{
				flag_change(txt, flags, i, 1);
				while (txt[i] != 39) // 39 es el ascii de '
				{
					temp[d] = txt[i];
					if (txt[i] == '\0')
					{
						printf("opened quotes in command line\n");
						g_shell.num_quit = 1;
						exit(1);
					}	
					i++;
					d++;
				}
				flag_change(txt, flags, i, 1);
			}
		}
		else if (txt[i] == 34) //34 es el ascci de ""
		{
			if (flags[1] != -1 && flags[0] != -1) //dentro, entramos dobles (ignorar dentro las simples)
			{
				flag_change(txt, flags, i, 0);
				while (txt[i] != 34)
				{
					temp[d] = txt[i];
					if (txt[i] == '\0')
					{
						printf("opened quotes in command line\n");
						g_shell.num_quit = 1;
						exit(1);
					}
					i++;
					d++;
				}
				flag_change(txt, flags, i, 0);
			}
		}
		else if (txt[i] == '|')
		{
			remove_quote(txt, i);
			temp[d] = '\0';
			tokens[c] = ft_strdup(temp);
			printf("split tokens args[%d] %s\n", c, tokens[c]);
			c++;
			d = 0;
			//temp[0] = '\0';
			//temp = NULL;
		}
		temp[d] = txt[i];
		i++;
		d++;
	}
	temp[d] = '\0';
	tokens[c] = ft_strdup(temp);
	i = -1;
	/*while (tokens[++i])
		printf("split token. arg[%d] %s\n", i, tokens[i]);*/
	return (tokens);
}
