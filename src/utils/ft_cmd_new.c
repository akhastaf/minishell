#include "../../include/minishell.h"

t_cmd	*ft_cmd_new(void *path, char **arg, char *opr, t_red *red)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->path = path;
	new->arg = arg;
	new->opr = opr;
	new->red = red;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
