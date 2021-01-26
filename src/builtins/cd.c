#include "../../include/minishell.h"

int     builtins_cd(char **arg)
{
    char *oldpwd;
    char *opwd;
    char *pwd;
    char *s;



    oldpwd = ft_strdup(ft_getenv("PWD") ? ft_getenv("PWD") : "");
    if (!arg[1])
    {
        if (!(s = ft_getenv("HOME")))
        {
            ft_putendl_fd("minishell: cd: HOME not set", 2);
            return 1;
        }
        arg[1] = ft_strdup(s);
    }
    else if (ft_is_empty(arg[1]) && oldpwd)
    {
        ft_setenv("OLDPWD", oldpwd);
        return 1;
    }
    
    if (!ft_strcmp(arg[1], "-"))
    {
        opwd = ft_getenv("OLDPWD");
        if (opwd)
            ft_putendl_fd(opwd, 1);
        else
        {
            ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
            return 1;
        }
            arg[1] = ft_strdup(opwd);
    }
    if (!chdir(arg[1]))
    {
        if (!(pwd = getcwd(NULL, 0)))
        {
            ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: ", 2);
            ft_putendl_fd(strerror(errno), 2);
            pwd = ft_strdup(ft_getenv("PWD"));
            pwd = ft_strappend(pwd, '/');
            pwd = ft_strjoin(pwd, arg[1]);
        }
        ft_setenv("PWD", pwd);
        if (oldpwd)
            ft_setenv("OLDPWD", oldpwd);
        free(pwd);
    }
    else
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(arg[1], 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno), 2);
        return 1;
    }
    free(oldpwd);
    return 0;
}