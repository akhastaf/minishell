#include "../include/minishell.h"

char    *ft_getopr(char **arg)
{
    int l;

    l = ft_size_arg(arg);
    if (!ft_strcmp(arg[l - 1], "|") || !ft_strcmp(arg[l - 1], ";"))
        return (arg[l - 1]);
    return NULL;
}

char    **ft_remove_arg(char **arg, char *str)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (!ft_strcmp(arg[i], str))
            arg[i] = NULL;
        i++;
    }
    return arg;
}

void    process_line()
{
    char **arg;
    char **cmd;
    char *tmp;
    t_cmd *new;
    int i;
    int l;

    new = NULL;
    cmd = ft_split_two(g_sh.line, '|', ';');
    i = 0;
    while (cmd[i])
    {
        cmd[i] = ft_strrepace(cmd[i]);
        arg =  ft_split(cmd[i], ',');
        l = ft_size_arg(arg);
        new = ft_cmd_new(ft_getpath(arg[0]), arg, ft_getopr(arg));
         if (arg[l-1])
            new->arg = ft_remove_arg(arg, arg[l-1]);
        ft_cmd_add_back(&g_sh.cmdlist, new);
        i++;
    }
}