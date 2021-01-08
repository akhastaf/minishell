#include "../../include/minishell.h"

void    ft_red_list_remove(t_red **redlist)
{
    t_red *red;

    red = *redlist;
    while (red)
    {
        ft_red_remove(red);
        red = red->next;
    }
    *redlist = NULL;
}