#include "../../include/minishell.h"

t_cmd	*ft_cmd_last(t_cmd *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}
