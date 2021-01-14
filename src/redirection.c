#include "../include/minishell.h"

void    setup_redirection(t_cmd *cmd)
{
    t_red *red;

    red = cmd->red;
    cmd->fdout = 0;
    cmd->fdin = 0;
    while (red)
    {
        if (red && red->type[0] == '<')
            cmd->fdin = open(red->file, get_option(red), S_IRWXU);
        if (red && red->type[0] == '>')
            cmd->fdout = open(red->file, get_option(red), S_IRWXU);
        if (cmd->fdin < 0 || cmd->fdout< 0)
        {
            g_sh.error = 1;
            ft_putstr_fd("-bash ", 2);
            ft_putstr_fd(red->file, 2);
            ft_putstr_fd(": ", 2);
            ft_putendl_fd(strerror(errno), 2);
        }
        if (red->next && cmd->fdout && red->next->type[0] != '<')
            close(cmd->fdout);
        if (red->next && cmd->fdin && red->next->type[0] == '<')
            close(cmd->fdin);
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
        if (cmd[i] == '"')
        {
            i++;
            while (cmd[i] != '"')
                i++;
            i++;
        }
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
            file = ft_getword(cmd + i + 1, " ><|;");
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
    int s;
    int len;
    char *new;

    len = ft_redcount(cmd, (int)ft_strlen(cmd));
    s = ft_strnchrn(cmd, "><");
    new = ft_strndup(cmd, s);
    new = ft_strjoin(new, cmd + len + s);
    return new;
}

int    get_option(t_red *red)
{
    int option;

     option = 0;
    if (red->type && red->type[0] == '>' && red->type[1] != '>')
        option = O_CREAT | O_WRONLY | O_TRUNC;
    else if (red->type && red->type[0] == '<')
        option = O_RDONLY;
    else if (red->type && !ft_strcmp(red->type, ">>"))
        option = O_CREAT | O_WRONLY | O_APPEND;
    return option;
}

void    close_fd(t_cmd *cmd)
{
    close(cmd->fdout);
    close(cmd->fdin);
}

int     ft_redcount(char *cmd, int l)
{
    int i;
    int j;
    int r;
    int len;

    i = 0;
    j = 0;
    r = 0;
    while (i < l)
    {
        if (cmd[i] == '>' && cmd[i + 1] == '>')
        {
            j = j + 2;
            i++;
            r = 1;
        }
        else if (cmd[i] == '>' || cmd[i] == '<')
        {
            j++;
            r = 1;
        }
        if (r)
        {
            len = ft_strlen(ft_getword(cmd + i + 1, " ><;|"));
            r = len + (ft_strnchrn(cmd + i + 1 + len, "><") ? ft_count_space(cmd + i + 1 + len) : 0);
            i = i + r - 1;
            j = j + r;
        }
        r = 0;
        i++;
    }
    return j;
}