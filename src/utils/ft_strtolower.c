#include "../../include/minishell.h"

char *ft_strtolower(char *str)
{
    int i;

    if (!str)
        return NULL;
    
    i = 0;
    while (str[i])
    {
        str[i] = ft_tolower(str[i]);
        i++;
    }
    return str;
}