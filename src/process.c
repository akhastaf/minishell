#include "../include/minishell.h"

char    *ft_getopr(char **arg)
{
    int l;

    l = ft_size_arg(arg);
    if (!ft_strcmp(arg[l - 1], "|") || !ft_strcmp(arg[l - 1], ";"))
        return (ft_strdup(arg[l - 1]));
    return NULL;
}

char    **ft_remove_arg(char **arg, char *str)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (!ft_strcmp(arg[i], str))
        {
            free(arg[i]);
            arg[i] = NULL;
        }
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
        tmp = cmd[i];
        cmd[i] = ft_strtrim(cmd[i], " ");
        free(tmp);
        arg =  ft_split(cmd[i], ' ');
        new = ft_cmd_new(ft_getpath(arg[0]), arg, ft_getopr(arg));
        if (new->opr)
            new->arg = ft_remove_arg(arg, new->opr);
        ft_cmd_add_back(&g_sh.cmdlist, new);
        i++;
        
    }
}