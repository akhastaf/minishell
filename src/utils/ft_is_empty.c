#include "../../include/minishell.h"

int     ft_is_empty(char *s)
{
    int i;

    i = 0;
    while (s[i] && s[i] == ' ' && s[i] == '\t')
        i++;
    if (s[i])
        return 0;
    return 1;   
}