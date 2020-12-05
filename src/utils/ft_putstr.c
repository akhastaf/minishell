#include "../../include/minishell.h"

void	ft_putstr(char *s)
{
	if (s)
		write(1, s, ft_strlen(s));
}