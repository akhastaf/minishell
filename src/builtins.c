#include "../include/minishell.h"

void    builtins_init()
{
    g_sh.builtins_fun[0] = &builtins_pwd;
    g_sh.builtins_fun[1] = &builtins_cd;
    g_sh.builtins_fun[2] = &builtins_env;
    g_sh.builtins_fun[3] = &builtins_echo;
    g_sh.builtins_fun[4] = &builtins_unset;
    g_sh.builtins_fun[5] = &builtins_export;
    g_sh.builtins_fun[6] = &builtins_exit;
    g_sh.builtins_str[0] = "pwd";
    g_sh.builtins_str[1] = "cd";
    g_sh.builtins_str[2] = "env";
    g_sh.builtins_str[3] = "echo";
    g_sh.builtins_str[4] = "unset";
    g_sh.builtins_str[5] = "export";
    g_sh.builtins_str[6] = "exit";
}

int    builtins(t_cmd cmd)
{
    int i;

    i = 0;
    while (i < BUILTINS_NUM)
    {
        if (!ft_strcmp(cmd.path, g_sh.builtins_str[i]))
            return g_sh.builtins_fun[i](cmd.arg);
        i++;
    }
    return -1;
}


int     ft_isbuiltins(char *path)
{
    int i;

    i = 0;
    while (i < BUILTINS_NUM)
    {
        if (!ft_strcmp(path, g_sh.builtins_str[i]))
            return 1;
        i++;
    }
    return 0;
}