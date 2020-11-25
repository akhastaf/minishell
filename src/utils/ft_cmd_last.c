#include "../../include/minishell.h"

t_cmd	*ft_lstlast(t_cmd *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}
