#include "../../include/minishell.h"

char    *ft_strrepace(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == 34 || str[i] == 39)
        {
            i++;
            while (str[i] != 34 && str[i] != 39)
                i++;
        }
        if (str[i] == ' ')
            str[i] = ',';
        i++;
    }
    return (str);
}