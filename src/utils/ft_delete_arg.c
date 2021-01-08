#include "../../include/minishell.h"

void    ft_delete_arg(char **arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        free(arg[i]);
        i++;
    }
    if (arg)
        free(arg);
}