#include "../include/minishell.h"

int     excute(t_cmd *cmdlist)
{
    int i;
    t_cmd *cmd;

    g_sh.is_b = 0;
    cmd = cmdlist;
    while (cmd )
    {
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
                    g_sh.status = g_sh.builtins_fun[i](cmd->arg);
                    close(cmd->pipe[1]);
                    g_sh.is_b++;
                    break;
                }
                i++;
            }
            if (!g_sh.is_b)
                ft_launch(cmd);
        }
        g_sh.is_b = 0;
        g_sh.error = 0;
        reset_std();
        cmd = cmd->next;
    }
    return g_sh.status;
}

void    ft_launch(t_cmd *cmd)
{
    DIR *dir;
    int err;

    g_sh.pid = fork();
    if (g_sh.pid == 0)
    {
        if (execve(cmd->path, cmd->arg, g_sh.env))
        {
            err = errno; 
            dir = opendir(cmd->path);
            ft_putstr_fd("-bash ", 2);
            if (dir)
            {
                ft_putstr_fd("|", 2);
                ft_putstr_fd(cmd->path, 2);
                ft_putstr_fd("|", 2);
                ft_putendl_fd(": is a directory", 2);
            }
            else if (err == 2)
            {
                ft_putstr_fd("|", 2);
                ft_putstr_fd(cmd->path, 2);
                ft_putstr_fd("|", 2);
                ft_putendl_fd(": command not found", 2);
                exit(127);
            }
            else
            {
                ft_putstr_fd(cmd->path, 2);
                ft_putstr_fd(": ", 2);
                ft_putendl_fd(strerror(err), 2);
            }
            exit(126);
        }
    }
    close(cmd->pipe[1]);
    waitpid(g_sh.pid, &g_sh.status, 0);
    g_sh.status = WEXITSTATUS(g_sh.status);
}

void    ft_warp_ref(t_cmd **cmd)
{
    int i;

    i = 0;
    while ((*cmd)->arg[i])
    {
        (*cmd)->arg[i] = ft_refactor_line((*cmd)->arg[i]);
        //(*cmd)->arg[i] = ft_strtrim((*cmd)->arg[i], "'\"");
        if ((*cmd)->arg[i])
        {
             (*cmd)->arg[i] = ft_strremove((*cmd)->arg[i], '"');
            (*cmd)->arg[i] = ft_strremove((*cmd)->arg[i], '\'');
            (*cmd)->arg[i] = ft_strremove((*cmd)->arg[i], '\\');
        }
        i++;
    }
}