#include "../../include/minishell.h"

int     ft_countcahr(char *s, char c)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (s[i])
    {
        if (s[i] == c)
            j++;
        i++;
    }
    return j;
}