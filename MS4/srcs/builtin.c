/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:40:03 by marvin            #+#    #+#             */
/*   Updated: 2022/06/15 10:40:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int echo(char *input, int n)
{
    char **temp;
    int i;
    
   // temp = (char **)malloc(sizeof(char*) * 2);
    temp = ft_split(input, ' ');
    i = 1;
    if (str_cmp(temp[1], "-n") == 0)
    {
        n = 1;
        i++;
    }
    expand(temp);
    while(temp[i])
    {
        //expand2(temp[i]);
        printf("%s", temp[i]);
        i++;
        if(temp[i])
            printf(" ");
    }
    if (n == 0)
        printf("\n");
    clear(temp);
    return(0);
}

int cd(char **intro, char **envi)
{
    //char *path;
    const char *directory;
    struct dirent *dir;
    DIR     *dp;

    (void) envi;
    printf("      ---entramos en cd fution\n");
    //dir->d_name = intro[1];
    directory = intro[1];
    dp = opendir(directory);
    dir = readdir(dp);
    printf("dir_name: '%s'\n", dir->d_name);
    return(0);
}

void env(char **envi)
{
    int i;

    i = 0;
    while(envi[i])
        printf("%s\n",envi[i++]);
}
