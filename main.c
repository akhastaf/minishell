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
    ft_set_pwd();
    if (ac == 3 && !ft_strcmp(av[1], "-c"))
    {
        g_sh.line = ft_strdup(av[2]);
        g_sh.c = 1;
    }
    else
     g_sh.c = 0;
    minishell_loop(env);
    return g_sh.ret;
}

void    increment_shlvl()
{
    int value;
    char *env;

    env = ft_getenv("SHLVL");
    value = ft_atol(env ? env : "");
    if (value >= 2147483647)
        value = -1;
    if (value >= 200000)
    {
        ft_putstr_fd("minishell: warning: shell level (", 2);
        ft_putstr_fd(ft_itoa(value + 1), 2);
        ft_putendl_fd(") too high, resetting to 1", 2);
        value = 0;
    }
    else if (value < 0)
        value = -1;
    ft_envremove("SHLVL");
    ft_setenv("SHLVL", ft_itoa(value + 1));
}

void    ft_set_pwd()
{
    char *pwd;

    if (!(pwd = ft_getenv("PWD")))
    {
        if (!(pwd = getcwd(NULL, 0)))
            pwd = ft_strdup("");
        ft_setenv("PWD", pwd);
        //ft_envadd(pwd);
    }
}

void    ft_set_lstcmd()
{
    char *lstcmd;

    lstcmd = ft_strdup(ft_cmd_last(g_sh.cmdlist)->path);
    if (ft_getenv("_"))
        ft_envremove("_");
    ft_setenv("_", lstcmd);
}