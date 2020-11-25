#include "../../include/minishell.h"

void	ft_cmd_add_back(t_cmd **alst, t_cmd *new)
{
	t_cmd *temp;

	temp = *alst;
	if (temp)
	{
		temp = ft_lstlast(temp);
		(temp)->next = new;
	}
	else
		*alst = new;
}
