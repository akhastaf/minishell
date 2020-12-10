#include "../include/minishell.h"

int     excute(t_cmd *cmdlist)
{
    int i;

    i = 0;
    while (cmdlist)
    {
        while (i < BUILTINS_NUM)
        {
            if (!ft_strcmp(cmdlist->path, g_sh.builtins_str[i]))
                return g_sh.builtins_fun[i](cmdlist->arg);
            i++;
        }
        ft_launch(*cmdlist);
        cmdlist = cmdlist->next;
    }
    return g_sh.status;
}

void    ft_launch(t_cmd cmd)
{
    g_sh.pid = fork();
    if (g_sh.pid == 0) // child p = 0; // parent p = 4578
    {
        if (execve(cmd.path, cmd.arg, g_sh.env))
        {
            write(1, "-bash ", 6);
            if (errno == 2)
            {
                write(1, cmd.path, ft_strlen(cmd.path));
                write(1, ": command not found\n", 20);
            }
            else
                perror(cmd.path);
        }
    }
    else
        waitpid(g_sh.pid, &g_sh.status, 0);
}