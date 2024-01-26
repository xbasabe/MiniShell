
#include "minishell.h"

char	**split_tokens(char *txt)
{
	int		i;
	int		flags[2];
	char	**tokens;
	char	temp[999];
	int		d;
	int		c;

	i = 0;
	d = 0;
	c = 0;
	flags[0] = 1;
	flags[1] = 1;
	tokens = (char **)malloc((sizeof(char *) * 20));
	while (txt[i] != '\0')
	{
		if (txt[i] == 39) // simples ' 39 ascci de '
			//temp = split_tokens_simples(flags, txt, &i, &d);
			ft_strcpy(temp, split_tokens_simples(flags, txt, &i, &d));
		else if (txt[i] == 34) //34 es el ascci de ""
			//temp = split_tokens_doubles(flags, txt, &i, &d);
			ft_strcpy(temp, split_tokens_simples(flags, txt, &i, &d));
		else if (txt[i] == ' ')
		{
			remove_quote(txt, i);
			temp[d] = '\0';
			tokens[c] = ft_strdup(temp);
			c++;
			d = 0;
		}
		temp[d] = txt[i];
		i++;
		d++;
		temp[d] = '\0';
		tokens[c] = ft_strdup(temp);
		//tokens[c + 1] = NULL;
		printf("   - token %c %s\n", c, tokens[c]);
	}
	temp[d] = '\0';
	tokens[c] = ft_strdup(temp);
	printf("   - token %c %s\n", c, tokens[c]);
	tokens[c + 1] = NULL;
	return (tokens);
}

char	*split_tokens_simples(int *flags, char *txt, int *i, int *d) // en vez de i para que se actualize y *d
{	
	char	*temp;
	
	temp = NULL;
	temp = (char *)malloc(sizeof(char) * ft_strlen(txt));
	if (flags[0] != -1 && flags[1] != -1)//dentro, entramos simples (ignorar dentro las dobles)
	{
		flag_change(txt, flags, i, 1);
		while (txt[*i] != 39) // 39 es el ascii de '
		{
			temp[*d] = txt[*i];
			if (txt[*i] == '\0')
			{
				//printf("opened quotes in command line\n");
				g_shell.num_quit = 1;
				return ("NULL"); //igual mejor return NULL y sacar opned quotes en el split_tokens
				//exit(1);
			}	
			*i = *i + 1;
			*d = *d + 1;
		}
		flag_change(txt, flags, i, 1);
	}
	return(temp);
}

char	*split_tokens_doubles(int *flags, char *txt, int *i, int *d) // en vez de i para que se actualize y *d
{
	char	*temp;

	temp = NULL;
	if (flags[1] != -1 && flags[0] != -1) //dentro, entramos dobles (ignorar dentro las simples)
	{
		flag_change(txt, flags, i, 0);
		while (txt[*i] != 34)
		{
			temp[*d] = txt[*i];
			if (txt[*i] == '\0')
			{
				//printf("opened quotes in command line\n");
				g_shell.num_quit = 1;
				//exit(1);
				return ("NULL");
			}
			*i = *i + 1;
			*d = *d + 1;
		}
		flag_change(txt, flags, i, 0);
	}
	return(temp);
}

void	flag_change(char *txt, int *flags, int *i, int f)
{
	int	init;

	init = *i;
	flags[f] = flags[f] * -1;
	remove_quote(txt, init);
}



/* FUNCIONA, CON UN LEAK

char	**split_tokens_NO_norme(char *txt)
{
	int		i;
	//int		*j;
	int		flags[2];
	char	**tokens;
	//char	*temp;
	char	temp[999];
	int		d;
	int		c;

	i = 0;
	d = 0;
	//j = &i;
	c = 0;
	flags[0] = 1;
	flags[1] = 1;
	//temp = (char *)malloc(sizeof(char) * ft_strlen(txt) + 1);
	//temp = NULL;
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
			c++;
			d = 0;
		}
		temp[d] = txt[i];
		i++;
		d++;
	}
	temp[d] = '\0';
	tokens[c] = ft_strdup(temp);
	tokens[c + 1] = NULL;
	return (tokens);
}

void	flag_change(char *txt, int *flags, int i, int f)
{
	int	init;

	init = i;
	flags[f] = flags[f] * -1;
	remove_quote(txt, init);
}

*/