#include "../include/minishell.h"


void    setup_pipe(t_cmd *cmd)
{
    if (cmd->opr && cmd->opr[0] == '|')
    {
        dup2(cmd->pipe[1], 1);
    }
    if (cmd->prev && cmd->prev->opr && cmd->prev->opr[0] == '|')
    {
        dup2(cmd->prev->pipe[0], 0);
    }
}

void    reset_std()
{
    dup2(g_sh.in, 0);
	dup2(g_sh.out, 1);
}

void    close_pipe()
{
    t_cmd *cmd;

    cmd = g_sh.cmdlist;
    while (cmd)
    {
        if (cmd->opr && cmd->opr[0] == '|')
        {
            close(cmd->pipe[0]);
            close(cmd->pipe[1]);
        }
        cmd =  cmd->next;
    }
}

void    open_pipes()
{
    t_cmd *cmd;
    cmd = g_sh.cmdlist;
    while (cmd)
    {
        if (cmd->opr && cmd->opr[0] == '|')
            pipe(cmd->pipe);
        cmd =  cmd->next;
    }
}