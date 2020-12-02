#include "../include/minishell.h"

int     builtins_env(char **arg)
{
    int i;
    
    i = 0;
    while (g_sh.env[i])
    {
        write(1, g_sh.env[i], ft_strlen(g_sh.env[i]));
        //write(1, "\n", 1);
        i++;
    }
    return 1;
}

int     builtins_pwd(char **arg)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    write(1, pwd, ft_strlen(pwd));
    write(1, "\n", 1);
    return 1;
}

int     builtins_cd(char **arg)
{
    int l;
    char *oldpwd;
    char *pwd;

    l = ft_size_arg(arg);
    oldpwd = getcwd(NULL, 0);
    if (l > 2)
        write(STDERR_FILENO, "cd: no such file or directory:\n", 32);
    if (l == 2)
    {
        if (!chdir(arg[1]))
        {
            pwd = getcwd(NULL, 0);
            ft_setenv("PWD", pwd);
            ft_setenv("OLDPWD", oldpwd);
            free(pwd);
        }
    }
    free(oldpwd);
    return 1;
}

void    builtins()
{
    if (!ft_strcmp(g_sh.cmdlist->arg[0], "pwd"))
        builtins_pwd(g_sh.cmdlist->arg);
    if (!ft_strcmp(g_sh.cmdlist->arg[0], "cd"))
        builtins_cd(g_sh.cmdlist->arg);
    if (!ft_strcmp(g_sh.cmdlist->arg[0], "env"))
        builtins_env(g_sh.cmdlist->arg);
}