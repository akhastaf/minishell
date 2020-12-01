#include "../../include/minishell.h"

void    ft_cmd_remove(t_cmd *cmd)
{
    if (cmd->path)
        free(cmd->path);
    if (cmd->arg)
        ft_delete_arg(cmd->arg);
    if (cmd->opr)
        free(cmd->opr);
    if (cmd->red)
        free(cmd->red);
    if (cmd->file)
        free(cmd->file);
    free(cmd);
    cmd = NULL;
}