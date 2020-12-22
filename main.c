/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:55:52 by akhastaf          #+#    #+#             */
/*   Updated: 2020/12/21 11:16:54 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include <fcntl.h>
#include<sys/wait.h>
#include<signal.h>

void sig_c(int signum)
{
    if (!g_sh.pid)
    {
        write(1, "\n", 1);
        ft_printf_prompt();
    }
    // else
    // {
    //     write(1)
    // }
}

int     main(int ac, char **av, char **env)
{
    // char *cmd;
    // char *cmd1;
    signal(SIGINT, sig_c);
    init_sh(env);
    builtins_init();
    g_sh.cmdlist = NULL;
    g_sh.pid = 0;
    g_sh.in = dup(0); // 5
    g_sh.out = dup(1); // 6
    increment_shlvl();
    // cmd = ft_strdup("echo test >f1<f2>>f3");
    // printf("%d %s\n", (int)ft_strlen(cmd), cmd);
    // int c = ft_redcount(cmd, (int)ft_strlen(cmd));
    // int c1 = ft_strnchrn(cmd, "><");
    // printf("%d %d\n", c, c1);
    // cmd1 = ft_strndup(cmd, c1);
    // printf("|%s|\n", cmd1);
    // cmd1 = ft_strjoin(cmd1, cmd + c + c1);
    // printf("|%s|\n", cmd1);
    minishell_loop(env);
    return 0;
}

void    increment_shlvl()
{
    char *shlvl;
    int value;
    
    value = atoi(ft_getenv("SHLVL"));
    ft_envremove("SHLVL");
    shlvl = ft_strdup("SHLVL=");
    shlvl =  ft_strjoin(shlvl, ft_itoa(value + 1));
    ft_envadd(shlvl);
}