#include "../../include/minishell.h"


int     ft_size_arg(char **arg)
{
    int i;

    i = 0;
    while (arg[i])
        i++;
    return i;
}