/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:55:52 by akhastaf          #+#    #+#             */
/*   Updated: 2020/12/11 11:36:03 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include <fcntl.h>
#include<sys/wait.h>
#include<signal.h>

void sig_c(int signum)
{
    if (g_sh.pid)
        kill(g_sh.pid, SIGINT);
    else
        write(2, "\n", 1);
}


int     main(int ac, char **av, char **env)
{
    //signal(SIGINT, sig_c);
    init_sh(env);
    builtins_init();
    g_sh.cmdlist = NULL;
    minishell_loop(env);
    return 0;
}