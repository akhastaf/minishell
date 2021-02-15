#include "../include/minishell.h"

int     excute(t_cmd *cmdlist)
{
    int i;
    t_cmd *cmd;

    g_sh.is_b = 0;
    cmd = cmdlist;
    while (cmd)
    {
        if (!cmd->next)
            ft_set_lstcmd(cmd);
        ft_warp_ref(&cmd);
        setup_pipe(cmd);
        setup_redirection(cmd);
        i = 0;
        if (!g_sh.error && cmd->path)
        {
            while (i < BUILTINS_NUM)
            {
                if (!ft_strcmp(cmd->path, g_sh.builtins_str[i]))
                {
                    if (!ft_strcmp(cmd->path, "export") && ((cmd->prev && cmd->prev->opr && cmd->prev->opr[0] == '|') || (cmd->opr && cmd->opr[0] == '|')))
                        g_sh.is_b++;
                    else if (!ft_strcmp(cmd->path, "exit") && cmd->prev && cmd->prev->opr &&  cmd->prev->opr[0] == '|')
                        reset_std();
                    else if (!ft_strcmp(cmd->path, "exit") && cmd->opr && cmd->opr[0] == '|')
                        reset_std();
                    else if (!ft_strcmp(cmd->path, "exit") || (!cmd->prev || cmd->prev->opr || cmd->prev->opr[0] != '|'))
                        g_sh.status = g_sh.builtins_fun[i](cmd->arg);
                     else if (ft_strcmp(cmd->path, "exit"))
                        g_sh.status = g_sh.builtins_fun[i](cmd->arg);
                    close(cmd->pipe[1]);
                    g_sh.is_b++;
                    break;
                }
                i++;
            }
            if (!g_sh.is_b && !ft_is_empty(cmd->path))
                ft_launch(cmd);
        }
        g_sh.is_b = 0;
        g_sh.error = 0;
        reset_std();
        if (cmd->prev && cmd->prev->opr && cmd->prev->opr[0] == '|')
        {
            close(cmd->prev->pipe[0]);
            close(cmd->prev->pipe[1]);
        }
        cmd = cmd->next;
    }
    return g_sh.status;
}

void    ft_launch(t_cmd *cmd)
{
    DIR *dir;
    char *path;
    int err;
    int j;

    g_sh.pid = fork();
    if (g_sh.pid == 0)
    {
        if (execve(cmd->path, cmd->arg, g_sh.env))
        {
            err = errno;
            path = cmd->path;
            if (!ft_strchr(cmd->path, '/') && (!ft_getenv("PATH") || ft_is_empty(ft_getenv("PATH"))))
                path = ft_strjoin("./", cmd->path);
            dir = opendir(path);
            if (dir && (ft_strchr(cmd->path, '/') || !ft_getenv("PATH") || ft_is_empty(ft_getenv("PATH"))))
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(cmd->path, 2);
                ft_putendl_fd(": is a directory", 2);
                closedir(dir);
                exit(126);
            }
            else if (errno == 13 && (ft_strchr(cmd->path, '/') || !ft_getenv("PATH") || ft_is_empty(ft_getenv("PATH"))))
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(cmd->path, 2);
                ft_putendl_fd(": is a directory", 2);
                exit(126);
            }
            else if (!ft_getenv("PATH") || ft_is_empty(ft_getenv("PATH")))
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(cmd->path, 2);
                ft_putendl_fd(": No such file or directory", 2);
                exit(127);
            }
            else if (err == 2 || dir)
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(cmd->path, 2);
                if (ft_strchr(cmd->path, '/'))
                {
                    ft_putstr_fd(": ", 2);
                    ft_putendl_fd(strerror(errno), 2);
                }
                else
                    ft_putendl_fd(": command not found", 2);
                exit(127);
            }
            else if (err != 8)
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(cmd->path, 2);
                ft_putendl_fd(": Permission denied", 2);
                exit(126);
            }
            exit(0);
        }
    }
    close(cmd->pipe[1]);
    if ((cmd->opr && cmd->opr[0] == ';') || (!cmd->opr))
        waitpid(g_sh.pid, &g_sh.status, 0);
    g_sh.status = WEXITSTATUS(g_sh.status);
}

void    ft_warp_ref(t_cmd **cmd)
{
    int i;
    int j;
    char **arg;
    char *tmp;

    if ((*cmd)->path && !ft_is_empty((*cmd)->path))
    {
        (*cmd)->path = ft_refactor_line((*cmd)->path);
        (*cmd)->path = ft_strremove((*cmd)->path, '\\');
    }
    arg = malloc((ft_size_arg((*cmd)->arg) + 1) * sizeof(char*));
    i = 0;
    j = 0;
    while ((*cmd)->arg[i])
    {
        tmp = ft_refactor_line((*cmd)->arg[i]);
        if (tmp)
        {
            arg[j] = tmp;
            arg[j] = ft_putbackslash(arg[j]);
            arg[j] = ft_strremove(arg[j], '\'');
            arg[j] = ft_strremove(arg[j], '"');
            arg[j] = ft_strremove(arg[j], '\\');
            j++;
        }
        i++;
    }
    arg[j] = NULL;
    // print_arg(arg);
    (*cmd)->arg = arg;
}


char    *ft_putbackslash(char *s)
{
    int i;
    int j;
    int q;
    int sq;
    char *new;

    i = 0;
    q = 0;
    sq = 0;
    j = 0;
    if (!s[0])
        return (ft_strdup(s));
    new = NULL;
    while (s[i])
    {
        if (s[i] == '\'' && !sq && !q)
            sq = 1;
        else if (s[i] == '\'' && sq )
            sq = 0;
        if (s[i] == '"' && !q && !sq)
            q = 1;
        else if (s[i] == '"' && q)
            q = 0;
        if ((s[i] == '"' && sq) || (s[i] == '\\' && sq) || (s[i] == '\\' && s[i +1] != '\\' && s[i + 1] != '"' && s[i + 1] != '$' && q))
        {
            new = ft_strappend(new, '\\');
            j++;
        }
        new = ft_strappend(new, s[i]);
        i++;
    }
    if (s[0] != '\0')
        new[i + j] = 0;
    return new;
}

