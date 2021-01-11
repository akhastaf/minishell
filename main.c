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
        ft_print_prompt();
    }
}

int     main(int ac, char **av, char **env)
{
    int c;
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
    ft_envremove("OLDPWD");
    if (ac == 3 && !ft_strcmp(av[1], "-c"))
    {
        g_sh.line = ft_strdup(av[2]);
        c = 1;
    }
    else
     c = 0;
    minishell_loop(env, c);
    return g_sh.ret;
}

void    increment_shlvl()
{
    char *shlvl;
    char *tmp;
    int value;
    
    value = atoi(ft_getenv("SHLVL"));
    ft_envremove("SHLVL");
    shlvl = ft_strdup("SHLVL=");
    tmp = shlvl;
    shlvl =  ft_strjoin(shlvl, ft_itoa(value + 1));
    ft_memdel(tmp);
    ft_envadd(shlvl);
}