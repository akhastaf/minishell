#include "../../include/minishell.h"

void    ft_red_list_remove(t_red **redlist)
{
    t_red *red;
    t_red *next;

    red = *redlist;
    while (red)
    {
        next = red->next;
        ft_red_remove(red);
        red = next;
    }
    *redlist = NULL;
}