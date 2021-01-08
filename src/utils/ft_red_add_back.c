#include "../../include/minishell.h"

void	ft_red_add_back(t_red **alst, t_red *new)
{
	t_red *temp;

	temp = *alst;
	if (temp)
	{
		temp = ft_red_last(temp);
		(temp)->next = new;
	}
	else
		*alst = new;
}
