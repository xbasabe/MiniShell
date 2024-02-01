
#include "minishell.h"
#include <string.h>

char **split_tokens(char *txt)
{
	int i;
	int flags[2];
	char **tokens;
	int c;

	i = 0;
	c = 0;
	flags[0] = 1;
	flags[1] = 1;
	tokens = (char **)malloc((sizeof(char *) * 20));
	// while (txt && txt[i] != '\0')
	while (txt && (txt[i] != '\0') && (i < (int)ft_strlen(txt)))
	{
		if (txt[i] == 39) // simples ' 39 ascci de '
		{
			tokens[c] = ft_strdup(split_tokens_simples(flags, txt, &i)); // porque no ft_strcpy?
			// ft_strcpy(tokens[c], split_tokens_simples(flags, txt, &i));
			printf("   token sim [%d] -%s-\n", c, tokens[c]);
			c++;
		}
		else if (txt[i] == 34) // 34 es el ascci de ""
		{
			tokens[c] = ft_strdup(split_tokens_doubles(flags, txt, &i));
			// ft_strcpy(tokens[c], split_tokens_doubles(flags, txt, &i));
			printf("   token dob [%d] -%s-\n", c, tokens[c]);
			c++;
		}
		// else if (txt[i] != ' ')
		else
		{
			tokens[c] = ft_strdup(split_tokens_out(flags, txt, &i));
			// ft_strcpy(tokens[c], split_tokens_out(flags, txt, &i));
			printf("   token out [%d] -%s-\n", c, tokens[c]);
			c++;
		}
		i++;
		if (i == ((int)ft_strlen(txt) - 1))
			break;
		if (!txt)
			break;
	}
	tokens[c + 1] = NULL;
	return (tokens);
}

char *split_tokens_simples(int *flags, char *txt, int *i) // en vez de i para que se actualize y *d
{
	char *temp;
	int d;

	temp = NULL;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(txt) + 2));
	d = 0;
	if (flags[0] != -1 && flags[1] != -1) // dentro, entramos simples (ignorar dentro las dobles)
	{
		flags[0] = flags[0] * -1;
		temp[d] = txt[*i];
		*i = *i + 1;
		d++;
		while (txt[*i] != 39 && txt[*i] != '\0') // 39 es el ascii de '
		{
			temp[d] = txt[*i];
			*i = *i + 1;
			d++;
		}
		flags[0] = flags[0] * -1;
		temp[d] = txt[*i];
	}
	temp[++d] = '\0';
	return (ft_strdup(temp)); // devolver temp directmente?
}

char *split_tokens_doubles(int *flags, char *txt, int *i) // en vez de i para que se actualize y *d
{
	char *temp;
	int d;

	temp = NULL;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(txt) + 2));
	d = 0;
	if (flags[1] != -1 && flags[0] != -1) // dentro, entramos dobles (ignorar dentro las simples)
	{
		flags[1] = flags[1] * -1;
		temp[d] = txt[*i];
		*i = *i + 1;
		d++;
		while (txt[*i] != 34)
		{
			temp[d] = txt[*i];
			*i = *i + 1;
			d++;
		}
		flags[1] = flags[1] * -1;
		temp[d] = txt[*i]; // meter la comilla de cierre
	}
	// d++;
	// temp[d] = ' ';
	// d++;
	temp[++d] = '\0';
	// quote_erase(temp);
	// printf("  token dobles temp %s\n", temp);
	return (temp);
}

char *split_tokens_out(int *flags, char *txt, int *i) // en vez de i para que se actualize y *d
{
	char *temp;
	int d;

	(void)flags;
	while (txt[*i] == ' ') // timear, dejar uno? se podria hacer sin cortar linea?
		*i = *i + 1;
	d = 0;
	temp = NULL;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(txt) + 2));
	while (txt[*i] != 39 && txt[*i] != 34 && txt[*i] != '\0' && txt[*i] != ' ')
	{
		// if(txt[*i] == '$')
		//	txt = expand_vble_tokens(txt, i);
		temp[d] = txt[*i];
		*i = *i + 1;
		d++;
	}
	temp[d] = ' ';
	temp[++d] = '\0';
	*i = *i - 1; // recuperar posicion de txt
	return (temp);
}

// borrar
void flag_change(char *txt, int *flags, int f)
{
	(void)txt;
	flags[f] = flags[f] * -1;
	// remove_quote(txt, init);
}

// a usar despues de expandir
char *quote_erase(char *txt)
{
	int i;
	int j;
	char *temp;

	i = 0;
	j = 0;
	temp = (char *)malloc(sizeof(char) * 99);
	while (txt[i])
	{
		if (txt[i] == '\'' || txt[i] == '"')
			i++;
		temp[j] = txt[i];
		i++;
		j++;
	}
	return (temp);
}

// expandir. viene de parse_utils
char *expand_vble_tokens(char *txt, int *init)
{
	char *value;	 // valor que tiene la vble tras el $
	char exp[99999]; // el nuevo txt expandido
	int i;
	int j;
	int add;
	// int		memory;  //para usar en lexer.c create comands

	// memory = *init;
	i = 0;
	add = *init;
	while (txt[add] != ' ' && txt[add] != '\0' && txt[add] != '"') //&& txt[add] != '\'')
		add++;
	add = add - *init;
	value = search_vble_env(txt, *init);
	printf(" vble expandida: -%s-\n", value);
	if (value == NULL)
		return (txt); // bash elimina la vble buscada, el $VBLE
	j = 0;
	ft_strncpy(exp, txt, *init);
	if (value != NULL)
	{
		while (value[j])
		{
			exp[*init + j] = value[j];
			j++;
		}
	}
	j = j + *init;
	i = *init + add;
	*init = j - 2;
	exp[j] = '\0';
	// exp[j + 1] = '\0';
	j++;
	while (txt[i])
	{
		i++;
		exp[j] = txt[i];
		j++;
	}
	exp[j] = '\0';
	printf(" texto expandido: -%s-\n", exp);
	txt = exp;
	//*init = memory;
	return (txt);
}

char *expand_vble_lines(char *txt, int init)
{
	char *value; // valor que tiene la vble tras el $
	int i;
	int j;
	char *prev;
	char *post;
	char *temp;

	i = 0;
	j = 0;
	//post = (char *)malloc(sizeof(char) * 999);
	post = NULL;
	while (txt[i] != '$')
		i++;
	prev = (char *)malloc(sizeof(char) * (i + 2));
	ft_strlcpy(prev, txt, i + 1);
	printf("  previo:-%s-\n", prev);
	value = search_vble_env(txt, init);
	printf("  expandida: -%s-\n", value);
	temp = ft_strjoin(prev, value);
	printf("  prev + value: -%s-\n", temp);
	i = i + init;
	while (txt[i] != '\0')
	{
		//post[j] = txt[i];
		j++;
		i++;
	}
	//post[j] = '\0';
	ft_strilcpy(post, txt, i, j);
	printf("  post -%s-\n", post);
	free(prev);
	prev = ft_strjoin(temp, post);
	free(temp);
	free(post);
	printf("  texto expandido -%s-\n", prev);
	return (prev);
}
