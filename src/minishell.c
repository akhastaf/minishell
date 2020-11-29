/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:55:46 by akhastaf          #+#    #+#             */
/*   Updated: 2020/11/28 14:24:39 by akhastaf         ###   ########.fr       */
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
        //read(0, l, 10);
        write(1, "\033[0;32m", 8);
        write(1, pwd, strlen(pwd));
        write(1, "$> ", 3);
        write(1, "\033[0m", 5);
        readline();
        if (!strcmp(g_sh.line, "env"))
            ft_env(NULL);
        printf("%s\n", g_sh.line);
        free(g_sh.line);
        process_line();
        //excute();
    }
}

void    init_sh(char **env)
{
    g_sh.env = env;
}