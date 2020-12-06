#include "../include/minishell.h"

int     builtins_env(char **arg)
{
    int i;
    
    i = 0;
    while (g_sh.env[i])
    {
        write(1, g_sh.env[i], ft_strlen(g_sh.env[i]));
        write(1, "\n", 1);
        i++;
    }
    return 0;
}

int     builtins_pwd(char **arg)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    write(1, pwd, ft_strlen(pwd));
    write(1, "\n", 1);
    return 0;
}

int     builtins_cd(char **arg)
{
    int l;
    char *oldpwd;
    char *pwd;

    l = ft_size_arg(arg);
    oldpwd = getcwd(NULL, 0);
    if (l > 2)
    {
        write(STDERR_FILENO, "cd: no such file or directory:\n", 32);
        return 1;
    }
    if (l == 2)
    {
        if (!chdir(arg[1]))
        {
            pwd = getcwd(NULL, 0);
            ft_setenv("PWD", pwd);
            ft_setenv("OLDPWD", oldpwd);
            free(pwd);
        }
        else
            return 1;
    }
    free(oldpwd);
    return 0;
}

int     builtins_echo(char **arg)
{
    int n;
    int i;
    int l;

    n = 0;
    if (arg[1])
        if (!ft_strcmp(arg[1], "-n"))
            n = 1;
    i = 1;
    while (arg[i + n])
    {
        l = ft_strlen(arg[i + n]);
        if (arg[i + n][0] == 39 || arg[i + n][0] == 34)
            write(1, arg[i + n] + 1, l - 2);
        else
            write(1, arg[i + n], l);
        if (arg[i + n + 1])
            write(1, " ", 1);
        i++;
    }
    if (!n)
        write(1, "\n", 1);
    return 0;
}

int     builtins_export(char **arg)
{
    return 0;
}

int     builtins_unset(char **arg)
{
    int i;

    i = 1;
    while (arg[i])
    {
        if (ft_envremove(arg[i]))
            return 0;
        i++;
    }
    return 1;
}

void    builtins_init()
{
    g_sh.builtins_fun[0] = &builtins_pwd;
    g_sh.builtins_fun[1] = &builtins_cd;
    g_sh.builtins_fun[2] = &builtins_env;
    g_sh.builtins_fun[3] = &builtins_echo;
    g_sh.builtins_fun[4] = &builtins_unset;
    g_sh.builtins_str[0] = "pwd";
    g_sh.builtins_str[1] = "cd";
    g_sh.builtins_str[2] = "env";
    g_sh.builtins_str[3] = "echo";
    g_sh.builtins_str[4] = "unset";
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