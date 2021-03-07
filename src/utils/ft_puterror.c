#include "../../include/minishell.h"

void    ft_puterror(char *f, char *ar, char *l)
{
    if (f)
        ft_putstr_fd(f, 2);
    if (ar)
	    ft_putstr_fd(ar, 2);
    if (l)
	    ft_putendl_fd(l, 2);
}