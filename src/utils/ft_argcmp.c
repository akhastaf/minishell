#include "../../include/minishell.h"

int	ft_argcmp(char **arg, char *s)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_strnstr(arg[i], s, ft_strlen(arg[i])))
			return (0);
		i++;
	}
	return (1);
}
