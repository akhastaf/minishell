#include "../../include/minishell.h"

char    *ft_strappend(char *str, char c)
{
    char *s;
    int l;
    int i;

    if (!str)
        return NULL;
    l = ft_strlen(str);
    s = malloc(sizeof(char) * l + 1);
    i = 0;
    while (i < l)
    {
        s[i] = str[i];
        i++;
    }
    s[i] = c;
    i++;
    s[i] = 0;
    return s;
}