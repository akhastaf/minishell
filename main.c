/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:55:52 by akhastaf          #+#    #+#             */
/*   Updated: 2020/12/14 18:59:30 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include <fcntl.h>
#include<sys/wait.h>
#include<signal.h>

void sig_c(int signum)
{
    write(2, "\n", 1);
    ft_printf_prompt();
}

int     main(int ac, char **av, char **env)
{
    signal(SIGINT, sig_c);
    init_sh(env);
    builtins_init();
    g_sh.cmdlist = NULL;
    g_sh.in = dup(0); // 5
    g_sh.out = dup(1); // 6
    increment_shlvl();
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
    printf("%s\n", shlvl);
    ft_envadd(shlvl);
}