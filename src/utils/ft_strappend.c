#include "../../include/minishell.h"

char    *ft_strappend(char *str, char c)
{
    char *s;
    int l;
    int i;

    if (!str)
    {
        s = malloc(sizeof(char) * 2);
        s[0] = c;
        s[1] = 0;
        return s;
    }
    l = ft_strlen(str);
    if (!(s = malloc(sizeof(char) * (l + 2))))
        return NULL;
    i = 0;
    while (i < l)
    {
        s[i] = str[i];
        i++;
    }
    s[i] = c;
    i++;
    s[i] = 0;
    if (str)
        free(str);
    return s;
}