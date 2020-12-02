/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:55:46 by akhastaf          #+#    #+#             */
/*   Updated: 2020/12/02 10:38:04 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_list_clear(t_cmd *cmdlist)
{
    
}


void    print_arg(char **arg)
{
    int i;
    
    i = 0;
    while (arg[i])
    {
        printf("arg[%d] %s\n", i, arg[i]);
        i++;
    }
}

void	print_cmd(t_cmd l)
{
	t_cmd *tmp = &l;
	if (!tmp)
		printf("NULL\n");
	while (tmp)
	{
		printf("path %s\n", tmp->path);
        print_arg(tmp->arg);
        printf("opr %s\n", tmp->opr);
		tmp = tmp->next;
	}
}

void        minishell_loop(char **env)
{
    int status;

    status = 1;
    char *pwd;
    // while (env[i])
    // {
    //     printf("%s\n", env[i]);
    //     i++;
    // }
    while(status)
    {
        pwd = ft_getenv("PWD");
        //read(0, l, 10);
        write(1, "\033[0;32m", 8);
        write(1, pwd, strlen(pwd));
        write(1, "$> ", 3);
        write(1, "\033[0m", 5);
        readline();
        //printf("%d : %s\n", (int)ft_strlen(g_sh.line), g_sh.line);
        process_line();
        //ft_envreplace(g_sh.line);
        //print_cmd(*g_sh.cmdlist);
        builtins();
        //excute();
        ft_cmd_list_remove(&g_sh.cmdlist);
        free(g_sh.line);
    }
}

void    init_sh(char **env)
{
    g_sh.env = env;
}