#include "../../include/minishell.h"

char *ft_strtolower(char *str)
{
    int i;
    char *new;

    if (!str)
        return NULL;
    i = ft_strlen(str);
    if (!( new = malloc((i * sizeof(char)) + 1)))
        return NULL;
    i = 0;
    while (str[i])
    {
        new[i] = ft_tolower(str[i]);
        i++;
    }
    new[i] = 0;
    return new;
}