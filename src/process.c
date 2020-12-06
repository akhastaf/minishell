#include "../include/minishell.h"

char    *ft_getopr(char **arg)
{
    int l;

    l = ft_size_arg(arg);
    if (!ft_strcmp(arg[l - 1], "|") || !ft_strcmp(arg[l - 1], ";"))
        return (ft_strdup(arg[l - 1]));
    if (ft_strchr(arg[l - 1], '|'))
        return (ft_strdup("|"));
    else if (ft_strchr(arg[l - 1], ';'))
        return (ft_strdup(";"));
    return NULL;
}

char    **ft_remove_arg(char **arg, char *str)
{
    int i;
    int l;

    i = 0;
    while (arg[i])
    {
        if (!ft_strcmp(arg[i], str))
        {
            free(arg[i]);
            arg[i] = NULL;
            return arg;
        }
        i++;
    }
    if (ft_strchr(arg[i - 1], '|') || ft_strchr(arg[i - 1], ';'))
    {
        l = ft_strlen(arg[i - 1]);
        arg[i - 1][l - 1] = 0;
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

    //ft_refactor_line();
    if (g_sh.line)
    {
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
    else
    {
        printf("tets\n");
    }
    
}

void    ft_refactor_line()
{
    char *var;
    char *line;
    int i;
    int l;
    int j;

    line = NULL;
    i = 0;
    j = 0;
    while (g_sh.line[i])
    {
        if (g_sh.line[i] == '$' && !ft_is_space(g_sh.line[i + 1]))
        {
            if (g_sh.line[i + 1] == '?')
            {
                line = ft_strjoin(line, ft_itoa(g_sh.status));
                i++;
            }
            else
            {
                var = ft_getword(g_sh.line + i);
                l = ft_strlen(var);
                line = ft_strjoin(line, ft_getenv(var+1));
                i = i + l - 1;
            }
            j = i;
        }
        else if (g_sh.line[i] == '~')
        {
            line = ft_strjoin(line, ft_getenv("HOME"));
            i++;
            j = i;
        }
        else
        {
            line = ft_strappend(line, g_sh.line[i]);
            j++;
        }
        i++;
    }
    free(g_sh.line);
    g_sh.line = line;
}