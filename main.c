/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:55:52 by akhastaf          #+#    #+#             */
/*   Updated: 2020/12/22 12:14:23 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include <fcntl.h>
#include<sys/wait.h>
#include<signal.h>

void sig_c(int signum)
{
    if (!g_sh.pid && signum == SIGINT)
    {
        write(1, "\n", 1);
        ft_printf_prompt();
    }
}

int     main(int ac, char **av, char **env)
{
    // char *cmd;
    // char *cmd1;
    signal(SIGINT, sig_c);
    signal(SIGQUIT, sig_c);
    init_sh(env);
    g_sh.home = ft_getenv("HOME");
    builtins_init();
    g_sh.cmdlist = NULL;
    g_sh.pid = 0;
    g_sh.ret = 0;
    g_sh.in = dup(0);
    g_sh.out = dup(1);
    increment_shlvl();
    minishell_loop(env);
    return g_sh.ret;
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