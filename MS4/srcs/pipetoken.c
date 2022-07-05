/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipetoken.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:54:39 by marvin            #+#    #+#             */
/*   Updated: 2022/06/22 11:54:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *pipetoken(char *input, char *c)
{
    int len = 0, i = 0;
    char *first;
    char **words;

    words = ft_split(input, ' ');
    while(words[i])
    {
        if (str_cmp(words[i], c) == 0)
            break ;
        len = len + ft_strlen(words[i]);
        i++;
    }
    len = len + i;
    first = (char *)malloc(sizeof(char) * len);
    ft_strlcpy(first, input, len); 
    i = 0;
    while(words[i])
    {
        free(words[i]);
        i++;
    }
    free(words);
    //printf("   first cmd: '%s'\n", first);
    return(first);
}

int expand(char **txt)
{
    int i;
    int j;

    i = 0;
    j = 1;
    while(txt[i])
    {
        if (txt[i][0] == '$')
        {
            
            while(txt[i][j])
            {
                txt[i][j - 1] = txt[i][j];
                j++;
            }
            txt[i][j - 1] = '\0';
            txt[i] = getenv(txt[i]);
            if (!txt[i])
                return(1);
            j = 1;
        }
        i++;
    }
    return(0);
}

int expand2(char *txt)
{
    int i;
    int j;

    i = 0;
    j = 1;
    if (txt[0]== '$')
    {
            
        while(txt[i])
        {
            txt[i- 1] = txt[i];
            j++;
        }
        txt[i - 1] = '\0';
        printf("txt '%s'", txt);
        txt = getenv(txt);
        if (!txt[i])
            return(1);
        i++;
    }
    return(0);
}

char    *literal(char *input)
{
    char **tokens;
    char **next;

    tokens = ft_split(input, '"');
    next = (char**)malloc(sizeof(char *) * 2);
    /*
    if (tokens[0])
        next[0] = (char *)malloc(sizeof(char) * ft_strlen(tokens[0]));
    if (tokens[1])
        next[1] = (char *)malloc(sizeof(char) * ft_strlen(tokens[1]));
    */
    //ft_strcpy(next[0], tokens[0]);
    //ft_strcpy(next[1], tokens[1]);
    if (!next[0] && !next[1])
        return("");
    next[0] = tokens[0];
    next[1] = tokens[1];
    return(next[1]);
}

void launch(char *intro, char **envi)
{
    const char *path;
    char *const *arguments;
    char **tokens;

    tokens = ft_split(intro, ' ');
    arguments = (char * const*)tokens;
    path = (const char*)search_cmd(tokens[0], envi);
    path = stradd((char *)path, "/");
    path = stradd((char *)path, tokens[0]);
    execve(path, arguments, envi);
    free((char *)path);
   // free((char *)arguments);
    clear(tokens);
}

const char *search_cmd(char *txt, char **envi)
{
    const char **p;
    int i;

    (void) envi; //getnextline hasta linea de PATH o inicializar envi
    p = (const char **)ft_split(getenv("PATH"), ':');
    i = path_exe(p, envi, txt);
    if(i >= 0)
        return(p[i]);
    clear((char **)p);
    return(NULL);
}

int path_exe(const char **p, char **envi, char *txt)
{
    const char *directory;
    struct dirent *dir;
    DIR     *dp;
    int i;
    int j;

    (void) envi;
   // (void) p;
    i = 0;
    j = 0;
    while(p[i])
    {
        directory = p[i];
        //printf("Directorio '%s'\n", directory);
        if((dp = opendir(directory)) == NULL)
        {
            printf("'%s' not found\n", txt);
            return(-1);
        }
        while((dir = readdir(dp)) != NULL)
        {
            //printf("Directorio '%s'. dir_name: '%s'\n", directory,dir->d_name);
            if(str_cmp(dir->d_name, txt) == 0)
                return(i);
            j++;
        }
        i++;
    }
    return(-1);
}

pid_t child_launch(char *input, char **envi)
{
    pid_t ch_pid = fork();

    if (ch_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (ch_pid > 0)
    {
       // printf("spawn child with pid - %d\n", ch_pid);
        return ch_pid;
    }
    else
    {
        launch(input, envi);
        return ch_pid;
    }
}
