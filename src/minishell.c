/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:55:46 by akhastaf          #+#    #+#             */
/*   Updated: 2020/11/25 13:38:30 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void        minishell_loop(char **env)
{
    int status;

    status = 1;
    int i;
    i=0;
    char *pwd;
    char **path;
    char l[10];
    t_cmd cmd;
    // while (env[i])
    // {
    //     printf("%s\n", env[i]);
    //     i++;
    // }
    while(status)
    {
        pwd = ft_getenv(env, "PWD");
        while (path[i])
        {
            printf("%s\n", path[i]);
            i++;
        }
        //read(0, l, 10);
        write(1, "\033[0;32m", 8);
        write(1, pwd, strlen(pwd));
        write(1, "$> ", 3);
        write(1, "\033[0m", 5);
        readline();
        printf("%s\n", g_line);
        free(g_line);
        process_line();
        //excute();
    }
}