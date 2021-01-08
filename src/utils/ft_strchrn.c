#include "../../include/minishell.h"

int     ft_strchrn(char *s, char c)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == c)
            return i;
        i++;
    }
    return 0;
}