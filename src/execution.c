#include "../include/minishell.h"

int     excute(t_cmd *cmdlist)
{
    int i;
    t_cmd *cmd;

    g_sh.is_b = 0;
    cmd = cmdlist;
    while (cmd)
    {
        setup_pipe(cmd);
        setup_redirection(cmd);
        i = 0;
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
        g_sh.is_b = 0;
        reset_std();
        cmd = cmd->next;
    }
    return g_sh.status;
}

void    ft_launch(t_cmd *cmd)
{
    g_sh.pid = fork();
    if (g_sh.pid == 0)
    {
        if (execve(cmd->path, cmd->arg, g_sh.env))
        {
            write(1, "-bash ", 6);
            if (errno == 2)
            {
                write(1, cmd->path, ft_strlen(cmd->path));
                write(1, ": command not found\n", 20);
            }
            else
                perror(cmd->path);
        }
    }
    else
    {
        close(cmd->pipe[1]);
        waitpid(g_sh.pid, &g_sh.status, 0);
        g_sh.status = WEXITSTATUS(g_sh.status);
    }
}