#include "../../include/minishell.h"

t_red	*ft_red_new(void *type, char *file)
{
	t_red	*new;

	if (!(new = malloc(sizeof(t_red))))
		return (NULL);
	new->type = type;
    new->file = file;
	new->next = NULL;
	return (new);
}