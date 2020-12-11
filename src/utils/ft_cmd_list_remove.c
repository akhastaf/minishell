#include "../../include/minishell.h"

void    ft_cmd_list_remove(t_cmd **cmdlist)
{
    t_cmd *cmd;

    cmd = *cmdlist;
    while (cmd)
    {
        ft_cmd_remove(cmd);
        cmd = cmd->next;
    }
    *cmdlist = NULL;
}