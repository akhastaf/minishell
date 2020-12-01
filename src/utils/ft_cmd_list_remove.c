#include "../../include/minishell.h"

void    ft_cmd_list_remove(t_cmd **cmdlist)
{
    while (*cmdlist)
    {
        ft_cmd_remove(*cmdlist);
        *cmdlist = (*cmdlist)->next;
    }
    *cmdlist = NULL;
}