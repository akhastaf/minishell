#include "../../include/minishell.h"

int     builtins_export(char **arg)
{
    int i;
    int n;
    char *var;
    char *val;
    int ret;
    char *tmp;

    val = NULL;
    tmp = NULL;
    n = 0;
    ret = 0;
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
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(arg[i], 2);
            ft_putendl_fd("': not a valid identifier", 2);
            return 1;
        }
        else if (n && n < ft_strchrn(arg[i], '=') && arg[i][n + 1]  != '=')
        {
             ft_putstr_fd("minishell: export: `",2);
             ft_putstr_fd(arg[i], 2);
             ft_putendl_fd("': not a valid identifier", 2);
             return 1;
        }
        n = ft_strchrn(arg[i], '=');
        if (arg[i][n - 1 < 0 ? n : n - 1] == '+')
        {
            var = ft_strndup(arg[i], n - 1);
            val = ft_getenv(var);
        }
        else if (n)
            var = ft_strndup(arg[i], n);
        else
            var = ft_strdup(arg[i]);
        if (ft_isdigit(var[0]) || ft_isstrnchr(var, " |!;&$@\\'\"") || ft_is_empty(var))
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(arg[i], 2);
            ft_putendl_fd("': not a valid identifier", 2);
            ret = 1;
        }
        if (!n && !ft_isstrnchr(var, " |!;&$@\\'\""))
            ft_envadd(ft_strdup(arg[i]));
        else if (!ft_isstrnchr(var, " |!;&$@\\'\""))
        {
            tmp = val;
            val = ft_strjoin(val, arg[i] + n + 1);
            free(tmp);
            tmp = arg[i];
            arg[i] = ft_strjoin(var, "=");
            free(tmp);
            tmp = arg[i];
            arg[i] = ft_strjoin(arg[i], val);
            free(tmp);
            if (ft_checkenv(var))
            {
                ft_envremove(var);
                ft_envadd(ft_strdup(arg[i]));
            }
            else if (var && arg[i][0] != '$')
                ft_envadd(ft_strdup(arg[i]));
        }
        i++;
        free(val);
        free(var);
        val = NULL;
    }
    return ret;
}