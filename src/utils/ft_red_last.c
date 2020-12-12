#include "../../include/minishell.h"

t_red	*ft_red_last(t_red *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}
