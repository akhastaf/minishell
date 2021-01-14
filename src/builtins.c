#include "../include/minishell.h"

int     builtins_env(char **arg)
{
    int i;
    
    i = 0;
    while (g_sh.env[i])
    {
        if (ft_strchr(g_sh.env[i], '='))
            ft_putendl_fd(g_sh.env[i], 1); 
        i++;
    }
    return 0;
}

int     builtins_exit(char **arg)
{
    int i;
    int j;

    i = 0;
    if (ft_size_arg(arg) > 2)
    {
        write(2, "-bash: exit: too many arguments\n", 33);
        return 1;
    }
    if (arg[1])
    {
        j = 0;
        while (arg[1][i] && ft_isdigit(arg[1][i]))
        {
            j++;
            i++;
        }
        if (arg[1][i] == 0 && j <= 10)
            g_sh.ret = ft_atoi(arg[1]);
        else
        {
            ft_putendl_fd("exit", 2);
            ft_putstr_fd("bash: exit: ", 2);
            ft_putstr_fd(arg[1],2);
            ft_putendl_fd(": numeric argument required", 2);
            exit(255);
        }
        if (g_sh.ret > 255)
            g_sh.ret = g_sh.ret % 256;
        ft_putendl_fd("exit", 2);
        exit(g_sh.ret);
    }
    ft_putendl_fd("exit", 2);
    exit(g_sh.status);
    return g_sh.ret;
}

int     builtins_pwd(char **arg)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    ft_putendl_fd(pwd, 1);
    return 0;
}

int     builtins_cd(char **arg)
{
    char *oldpwd;
    char *opwd;
    char *pwd;
    char *s;

    if (!arg[1])
    {
        s = ft_getenv("HOME");
        arg = ft_argadd(arg, s);
    }
    oldpwd = getcwd(NULL, 0);
    if (!ft_strcmp(arg[1], "-"))
    {
        opwd = ft_getenv("OLDPWD");
        if (opwd)
            ft_putendl_fd(opwd, 1);
        else
        {
            ft_putendl_fd("-bash: cd: OLDPWD not set", 2);
            return 1;
        }
            arg[1] = ft_strdup(opwd);
    }
    if (!chdir(arg[1]))
    {
        pwd = getcwd(NULL, 0);
        ft_setenv("PWD", pwd);
        ft_setenv("OLDPWD", oldpwd);
        free(pwd);
    }
    else
    {
        ft_putstr_fd("-bash: cd: ", 2);
        ft_putstr_fd(arg[1], 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno), 2);
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
    i = 1;
    while (arg[i])
    {
        if (!ft_strcmp(arg[i], "-n"))
            n = 1;
        else if (!ft_strncmp(arg[i], "-n", 2))
        {
            l = 1;
            while (arg[i][l] == 'n')
                l++;
            if (!arg[i][l])
                n = 1;
            else
                break ;
        }
        else
            break ;
        i++;
    }
    while (arg[i])
    {
        ft_putstr_fd(arg[i], 1);
        if (arg[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (!n)
        ft_putstr_fd("\n", 1);
    return 0;
}

int     builtins_export(char **arg)
{
    int i;
    int n;
    char *var;
    char *val;

    val = NULL;
    n = 0;
    if (ft_size_arg(arg) == 1)
    {
        i = 0;
        while (g_sh.env[i])
        {
            if (ft_strncmp(g_sh.env[i], "_=", 2))
            {
                n = ft_strchrn(g_sh.env[i], '=');
                ft_putstr_fd("declare -x ", 1);
                if (n)
                {
                    var = ft_strndup(g_sh.env[i], n + 1);
                    ft_putstr_fd(var , 1);
                    ft_putstr_fd("\"", 1);
                    ft_putstr_fd(g_sh.env[i] + n + 1, 1);
                    ft_putendl_fd("\"", 1);
                }
                else
                {
                    var = ft_strdup(g_sh.env[i]);
                    ft_putendl_fd(var , 1);
                }
                free(var);
            }
            i++;
        }
    }
    i = 1;
    n = 0;
    while (arg[i])
    {
        n = ft_strchrn(arg[i], '+');
        if (arg[i][0] == '=')
        {
            ft_putendl_fd("bash: export: `=': not a valid identifier", 2);
            return 1;
        }
        else if (n && arg[i][n + 1]  != '=')
        {
             ft_putstr_fd("bash: export: `",2);
             ft_putstr_fd(arg[i], 2);
             ft_putendl_fd("': not a valid identifier", 2);
             return 1;
        }
        n = ft_strchrn(arg[i], '=');
        if (!n)
        {
            ft_envadd(arg[i]);
            return 0;
        }
        if (arg[i][n - 1] == '+')
        {
            var = ft_strndup(arg[i], n - 1);
            val = ft_getenv(var);
        }
        else if (n)
            var = ft_strndup(arg[i], n);
        if (ft_isdigit(var[0]))
        {
            ft_putstr_fd("bash: export: `", 2);
            ft_putstr_fd(var, 2);
            ft_putendl_fd("': not a valid identifier", 2);
            return 1;
        }
        val = ft_strjoin(val, arg[i] + n + 1);
        val = ft_strtrim(val, "'\"");
        arg[i] = ft_strjoin(var, "=");
        arg[i] = ft_strjoin(arg[i], val);
        if (ft_getenv(var))
        {
            ft_envremove(var);
            ft_envadd(arg[i]);
        }
        else if (var && arg[i][0] != '$')
            ft_envadd(arg[i]);
        i++;
    }
    return 0;
}

int     builtins_unset(char **arg)
{
    int i;

    i = 1;
    while (arg[i])
    {
        ft_envremove(arg[i]);
        i++;
    }
    return 0;
}

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