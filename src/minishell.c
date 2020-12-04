/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:55:46 by akhastaf          #+#    #+#             */
/*   Updated: 2020/12/03 19:43:59 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void    print_arg(char **arg)
{
    int i;
    
    i = 0;
    while (arg[i])
    {
        printf("%s\n", arg[i]);
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
void    ft_printf_prompt()
{
    char *pwd;

    pwd = ft_getenv("PWD");
    write(1, "\033[0;32m", 8);
    write(1, pwd, strlen(pwd));
    write(1, "$> ", 3);
    write(1, "\033[0m", 5);
}
void        minishell_loop(char **env)
{
    int status;

    status = 1;
    while(status)
    {
        ft_printf_prompt();
        readline();
        process_line();
        print_cmd(*g_sh.cmdlist);
        builtins();
        //excute();
        ft_cmd_list_remove(&g_sh.cmdlist);
        free(g_sh.line);
    }
}

void    init_sh(char **env)
{
    int l;
    int i;

    l = ft_size_arg(env);
    g_sh.env = malloc(l * sizeof(char*) + 1);
    i = 0;
    while (env[i])
    {
        g_sh.env[i] = ft_strdup(env[i]);
        i++;
    }
}

void    ft_envadd(char *var)
{
    int l;
    int i;
    char **env;
    
    l = ft_size_arg(g_sh.env);
    printf("%d\n", l);
    env = malloc(l * sizeof(char*) + 2);
    ft_memcpy(env, g_sh.env, sizeof(char*) * l);
    env[l] = ft_strdup(var);
    env[l + 1] = NULL;
    g_sh.env = env;
    l = ft_size_arg(g_sh.env);
    printf("%d\n", l);
    printf("%s\n", g_sh.env[l-1]);
}