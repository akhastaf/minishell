#include "../include/minishell.h"

t_red   *get_redirection(char *cmd)
{
    int i;
    char *type;
    t_red *red;
    t_red *redlist;

    i = 0;
    type = NULL;
    redlist = NULL;
    printf("cmd : %s\n", cmd);
    while (cmd[i])
    {
        if (cmd[i] == '>' && cmd[i + 1] == '>')
        {
            type = ft_strdup(">>");
            i++;
        }
        else if (cmd[i] == '>')
            type = ft_strdup(">");
        else if (cmd[i] == '<')
            type = ft_strdup("<");
        if (type)
        {
            red = ft_red_new(type, ft_getword(cmd + i + 1));
            ft_red_add_back(&redlist, red);
        }
        type = NULL;
        i++;
    }
    return redlist;
}

char    *remove_red(char *cmd)
{
    int tab[3];
    int i;
    char *new;

    tab[0] = ft_strchrn(cmd, '>');
    tab[1] = ft_strchrn(cmd, '<');
    tab[2] = ft_strnchrn(cmd, ">>");
    i = ft_tab_min(tab, 3);
    if (i)
        return (ft_substr(cmd, 0, i));
    return ft_strdup(cmd);
}