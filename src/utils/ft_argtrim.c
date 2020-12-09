#include "../../include/minishell.h"

char    **ft_argtrim(char **arg, char *set)
{
    int i;
    char *tmp;

    i = 0;
    while (arg[i])
    {
        tmp = arg[i];
        arg[i] = ft_strtrim(arg[i], set);
        free(tmp);
        i++;
    }
    return arg;
}