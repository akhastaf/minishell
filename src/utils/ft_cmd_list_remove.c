#include "../../include/minishell.h"

void	ft_cmd_list_remove(t_cmd **cmdlist)
{
	t_cmd	*cmd;
	t_cmd	*next;

	cmd = *cmdlist;
	while (cmd)
	{
		next = cmd->next;
		ft_red_list_remove(&(cmd->red));
		ft_cmd_remove(cmd);
		free(cmd);
		cmd = next;
	}
	*cmdlist = NULL;
}
