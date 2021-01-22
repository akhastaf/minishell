#include "../../include/minishell.h"

int     ft_strisdigit(char *str)
{
    int i;

    i = 0;
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    while (str[i])
    {
        if ((str[i] == '+' && str[i + 1] == '+') || (str[i] == '-' && str[i + 1] == '-'))
            return 0;
        else if (!ft_isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}