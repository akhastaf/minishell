#include "../../include/minishell.h"

int     builtins_exit(char **arg)
{
    int i;

    i = 0;
    
    if (arg[1])
    {
        while (arg[1][i] && (arg[1][i] == ' ' || arg[1][i] == '\t' || arg[1][i] == '\r' || arg[1][i] == '\f'))
            i++;
        if (ft_strisdigit(ft_strtrim(arg[1] + i, " \t")))
            g_sh.ret = ft_atoll(arg[1] + i);
        else if (g_sh.ret > 9223372036854775807 || !ft_strisdigit(arg[1]))
        {
            if (!g_sh.c)
                ft_putendl_fd("exit", 2);
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(arg[1],2);
            ft_putendl_fd(": numeric argument required", 2);
            exit(255);
        }
        if (ft_size_arg(arg) > 2)
        {
            ft_putendl_fd("minishell: exit: too many arguments", 2);
            return 1;
        }
        if (g_sh.ret > 255)
            g_sh.ret = g_sh.ret % 256;
        if (!g_sh.c)
            ft_putendl_fd("exit", 2);
        exit(g_sh.ret);
    }
    if (!g_sh.c)
        ft_putendl_fd("exit", 2);
    exit(g_sh.status);
    return g_sh.ret;
}