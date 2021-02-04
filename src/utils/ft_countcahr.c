#include "../../include/minishell.h"

int     ft_countcahr(char *s, char c)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (s[i])
    {
        if (s[i] == '\'' && c != '\'')
        {
            i++;
            while (s[i] != '\'')
                i++;
        }
        if ((s[i] == '\\' && is_specialcar(s[i + 1]) && s[i + 1] != '\'' && !is_specialcar(s[i+1])) || (s[i] == c && s[(i - 1 < 0 ? 1 : i - 1)] != '\\'))
            j++;
        i++;
    }
    return j;
}