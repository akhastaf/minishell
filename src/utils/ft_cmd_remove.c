#include "../../include/minishell.h"

void    ft_cmd_remove(t_cmd *cmd)
{
    if (cmd->path)
    {
        free(cmd->path);
        cmd->path = NULL;
    }
    if (cmd->arg)
    {
        ft_delete_arg(cmd->arg);
        cmd->arg = NULL;
    }
    if (cmd->opr)
    {
        free(cmd->opr);
        cmd->opr = NULL;
    }
}