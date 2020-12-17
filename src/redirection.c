#include "../include/minishell.h"

void    setup_redirection(t_cmd *cmd)
{
    t_red *red;

    red = cmd->red;
    while (red)
    {
        if (red && red->type[0] == '<')
            cmd->fdin = open(red->file, get_option(red), S_IRWXU);
        if (red && red->type[0] == '>')
            cmd->fdout = open(red->file, get_option(red), S_IRWXU);
        if (red->next && red->type[0] == '>')
            close(cmd->fdout);
        red = red->next;
    }
    if (cmd->fdout)
        dup2(cmd->fdout, 1);
    if (cmd->fdin)
        dup2(cmd->fdin, 0);
}


t_red   *get_redirection(char *cmd)
{
    int i;
    char *type;
    t_red *red;
    t_red *redlist;
    char *file;

    i = 0;
    type = NULL;
    redlist = NULL;
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
            file = ft_getword(cmd + i + 1, " ><");
            file = ft_strtrim(file, " ");
            red = ft_red_new(type, file);
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

int    get_option(t_red *red)
{
    int option;

     option = O_CREAT;
    if (red->type && red->type[0] == '>' && red->type[1] != '>')
        option = option | O_WRONLY | O_TRUNC;
    else if (red->type && red->type[0] == '<')
        option = option | O_RDONLY;
    else if (red->type && !ft_strcmp(red->type, ">>"))
        option = option | O_WRONLY | O_APPEND;
    return option;
}