#include "../../include/minishell.h"

int     ft_count_space(char *s)
{
    int i;

    i =0;
    while (s[i] && (s[i] == ' ' || s[i] == '\t'))
        i++;
    return i;
}