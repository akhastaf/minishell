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
        if (cmd->fdin < 0)
            perror("Error");
        if (cmd->fdout< 0)
            perror("Error");
        if (red->next && cmd->fdout && red->type[0] != '<')
            close(cmd->fdout);
        if (red->next && cmd->fdin && red->type[0] == '<')
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
    int i;
    int j;
    int len;
    char *new;

    len = ft_redcount(cmd);
    printf("%d\n", (int)ft_strlen(cmd) - len + 1);
    printf("%s\n", cmd);
    new = malloc(ft_strlen(cmd) - len + 1);
    i = 0;
    j = 0;
    while (cmd[i])
    {
        if (cmd[i] == '>' && cmd[i + 1] == '>')
        {
            i = i + ft_strlen(ft_getword(cmd + i + 2, "> <"));
            i = i + 2;
        }
        else if (cmd[i] == '>' || cmd[i] == '<' )
        {
            i = i + ft_strlen(ft_getword(cmd + i + 1, "> <"));
            i++;
        }
        if (cmd[i] != '>' && cmd[i] != '<')
        {
            new[j] = cmd[i];
            printf("j : %d new[%d]= %c\n", j, j, new[j]);
            j++;
            i++;
        }
    }
    new[--j] = 0;
    printf("j : %d\n", j);
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

int     ft_redcount(char *cmd)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    while (cmd[i])
    {
        if (cmd[i] == '>' && cmd[i + 1] == '>')
        {
            j = j + 2;
            len = ft_strlen(ft_getword(cmd + i + 2, "> <"));
            j = j + len;
            i = i + 2;
        }
        else if (cmd[i] == '>' || cmd[i] == '<' )
        {
            j++;
            len = ft_strlen(ft_getword(cmd + i + 1, "> <"));
            j = j + len;
            j = j + ft_count_space(cmd + len + i + 1);
        }
        len = 0;
        i++;
    }
    return j;
}