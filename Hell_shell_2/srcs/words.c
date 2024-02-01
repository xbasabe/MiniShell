#include "minishell.h"

char **line_to_words(char *line)
{
	int     count[2];
	int     flags[2];
    char    **words;

	count[0] = 0;
	count[1] = 0;
	flags[0] = 1;
	flags[1] = 1;
	
	quote_d_count(line, count); //inicializar count y flags como para parser
	if (opened_quotes(line, count, flags) == 0)
	{
		g_shell.num_quit = 1; //registrar el error en le vble global
		words = (char**)malloc(sizeof(char*)*2);
		words[0] = (char*)malloc(sizeof(char)*40);
		strcpy(words[0], "echo -Minishell: words: opened quotes");
		words[1] = (char*)malloc(sizeof(char)*1);
		strcpy(words[1], "\0");
		return(words);
	}
    else
	{
		words = get_words(line, count, flags);
	}
	return(words);
}

/* ya la tenemos en line
void	flop_flag(char *txt, int *flags, int *count, int i, int f) //version de flip-flag sin quitar las comillas
{
	int init;
	
	init = i;
	flags[f] = flags[f] * -1;
	count[f]--;
	//remove_quote(txt, init); las comillas deben seguir para prsear las lineas
}
*/

char	**get_words(char *txt, int *count, int *flags) //count numero de comillas
{
	int		i; //txt index
	int 	j; //temp_text index
    int    	c_words; //words index
	char	temp_text[500];
    char    **words;

	i = 0;
	j = 0;
	c_words = 0;
	printf(" words.c  Linea: %s\n", txt);

	words = (char**)malloc(sizeof(char*) * 50);
	while(txt && txt[i] != '\0')
	{
		temp_text[j] = txt[i];
		if(txt[i] == 39) // simples ' 39 ascci de '
		{	
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
				temp_text[j] = '\0';
				words[c_words] = (char*)malloc(sizeof(char) * (j + 1)); //darle tamaño j
				strcpy(words[c_words], temp_text); //cambiar por ft_strcpy
				printf("     Word[%d] %s\n", c_words, words[c_words]);
				temp_text[0] = '\0'; //reinicio alternativo
				j = 0; //reinicio contador de temp_text
				//i++;
				c_words++;
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
				flop_flag(flags, count, 0);
				temp_text[j] = '\0';
				words[c_words] = (char*)malloc(sizeof(char) * (j + 1)); //darle tamaño j
				//expandir $VBLE
				strcpy(words[c_words], temp_text); //cambiar por ft_strcpy
				printf("     Word[%d] %s\n", c_words, words[c_words]);
				temp_text[0] = '\0'; //reinicio alternativo
				j = 0; //reinicio contador de temp_text
				//i++;
				c_words++;
			}
		}
		else if(txt[i] != ' ' || txt[i] != '\t') // tabulador? crear funcion is_space?
        {
		    temp_text[j] = txt[i];
			while(txt[i] != 34 && txt[i] != 39)
			{
				 temp_text[j] = txt[i];
			}
			temp_text[j] = '\0';
			words[c_words] = (char*)malloc(sizeof(char) * 999); //darle tamaño j
			//trim para quitar espacios extra
			ft_strtrim((const char*)words[c_words], "' ',\t");
            strcpy(words[c_words], temp_text); //cambiar por ft_strcpy
			printf("     Word[%d] %s\n", c_words, words[c_words]);
			temp_text[0] = '\0'; //reinicio alternativo
			j = 0; //reinicio contador de temp_text
			i++;
			c_words++;
        }
		temp_text[j] = txt[i];
		i++;
        j++;
	}
	/*
	temp_text[j] = '\0';
	words[c_words] = (char*)malloc(sizeof(char) * (ft_strlen(temp_text) + 1));
	words[c_words] = ft_strdup(temp_text);
	//words[c_words] = ft_strdup(expand_word(temp_text));
	printf("     Word[%d] %s\n", c_words, words[c_words]);
	temp_text[0] = '\0';
	c_words++;

	*/
	words[c_words] = (char*)malloc(sizeof(char) * 1);
	words[c_words] = "\0";
	
	return(words);
}

char *expand_word(char *word)
{
	int i;
	
	i = 0;
	while(word[i])
	{
		if(word[i] == '$')
			word = expand_vble(word, &i);
		i++;
	}
	//i--; 
	word[i] = '\0';
	return(word);
}

