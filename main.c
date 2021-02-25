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
        prompt();
    }
    else if (g_sh.pid &&  signum == SIGQUIT)
        kill(g_sh.pid, SIGQUIT);
}

int     main(int ac, char **av, char **env)
{
    signal(SIGINT, sig_c);
    signal(SIGQUIT, sig_c);
    init_env(env);
    init_sh();
    if (ac == 3 && !ft_strcmp(av[1], "-c"))
    {
        g_sh.line = ft_strdup(av[2]);
        g_sh.c = 1;
    }
    else
     g_sh.c = 0;
    minishell_loop();
    return g_sh.ret;
}

void    increment_shlvl()
{
    int value;
    char *env;
    char *v;

    env = ft_getenv("SHLVL");
    value = ft_atoll(env ? env : "");
    free(env);
    if (value >= 2147483647)
        value = -1;
    if (value >= 200000)
    {
        ft_putstr_fd("minishell: warning: shell level (", 2);
        v = ft_itoa(value + 1); 
        ft_putstr_fd(v, 2);
        free(v);
        ft_putendl_fd(") too high, resetting to 1", 2);
        value = 0;
    }
    else if (value < 0)
        value = -1;
    v = ft_itoa(value + 1);
    ft_envremove("SHLVL");
    ft_setenv("SHLVL", v);
    free(v);
}

void    ft_set_pwd()
{
    char *pwd;
    char *lstcmd;

    if (!(pwd = ft_getenv("PWD")))
        if (!(pwd = getcwd(NULL, 0)))
            pwd = ft_strdup("");
    ft_setenv("PWD", pwd);
    free(pwd);
}

void    init_sh()
{
    init_errors();
    builtins_init();
    g_sh.home = ft_getenv("HOME");
    g_sh.cmdlist = NULL;
    g_sh.pid = 0;
    g_sh.ret = 0;
    g_sh.in = dup(0);
    g_sh.out = dup(1);
    ft_envremove("OLDPWD");
    ft_set_pwd();
    increment_shlvl();
}

void    ft_set_lstcmd(t_cmd *cmd)
{
    int n;
    int l;
    char *lstcmd;
    char *oldlstcmd;
    t_cmd *lcmd;

    n = 0;
    l = 0;
    if (!ft_strcmp(cmd->path, "echo") && !ft_argcmp(cmd->arg, "$_") && cmd->prev)
        lcmd = cmd->prev;
    else if (!ft_strcmp(cmd->path, "echo") && !ft_argcmp(cmd->arg, "$_"))
        lcmd = NULL;
    else
        lcmd = cmd;
    if (lcmd)
    {
        n = ft_size_arg(lcmd->arg) - 1;
        if (cmd->prev && cmd->prev->opr && !ft_strcmp(cmd->prev->opr, "|"))
            lstcmd = ft_strdup("");
        else if (lcmd)
        {
            if (( l = ft_strchrn(lcmd->arg[n], '=')))
                lstcmd = ft_substr(lcmd->arg[n], 0, l);
            else if (!(ft_strcmp(ft_strtolower(lcmd->arg[0]), "env")))
                lstcmd = ft_strdup(lcmd->path);
            else
                lstcmd = ft_strdup(lcmd->arg[n]);
        }
        oldlstcmd = ft_getenv("_");
        if (oldlstcmd)
            ft_envremove("_");
        ft_setenv("_", lstcmd);
        free(lstcmd);
        free(oldlstcmd);
    }
}

void    init_errors()
{
    g_sh.errors[1] = ft_strdup("minishell: syntax error near unexpected token `|'");
    g_sh.errors[2] = ft_strdup("minishell: syntax error near unexpected token `;'");
    g_sh.errors[3] = ft_strdup("minishell: syntax error near unexpected token `||'");
    g_sh.errors[4] = ft_strdup("minishell: syntax error near unexpected token `;;'");
    g_sh.errors[5] = ft_strdup("minishell: syntax error near unexpected token `|;'");
    g_sh.errors[6] = ft_strdup("minishell: syntax error near unexpected token `;|'");
    g_sh.errors[7] = ft_strdup("minishell: syntax error near unexpected token `<<'");
    g_sh.errors[8] = ft_strdup("minishell: syntax error near unexpected token `>'");
    g_sh.errors[9] = ft_strdup("minishell: syntax error near unexpected token `newline'");
    g_sh.errors[10] = ft_strdup("minishell: syntax error multiline");
}