#include "../../include/minishell.h"

int     ft_countcahr(char *s, char c)
{
    int i;
    int j;
    int q;
    int sq;

    i = 0;
    j = 0;
    q = 0;
    sq = 0;
    printf("%s\n", s);
    while (s[i])
    {
        // if (s[i] == '\'' && c != '\'')
        // {
        //     i++;
        //     while (s[i] != '\'')
        //         i++;
        // }
        if (s[i] == '"' && !q && !sq)
            q = 1;
        else if (s[i] == '"' && q)
            q = 0; 
        if (s[i] == '\'' && !sq && !q)
            sq = 1;
        else if (s[i] == '\'' && sq)
            sq = 0; 
        if (s[i] == c && c == '\'' && !q && s[i - 1 < 0 ? 1 : i - 1] != '\\')
            j++;
        // else if (s[i] == '"' && s[i - 1 < 0 ? 0 : i - 1] != '\\' && count_backslash(ft_strndup(s, i)) % 2 == 0)
        //     j++;
        else if (s[i] == c && c == '"' && !sq && s[i - 1 < 0 ? 0 : i - 1] != '\\')
            j++;
        else if (s[i] == c && c == '\\' && !sq && s[i - 1 < 0 ? 1 : i - 1] != '\\')
            j++;
        // if ((s[i] == '\\' && !q) || (s[i] == c && s[(i - 1 < 0 ? 1 : i - 1)] != '\\'))
        // {

        //     j++;
        // }
        i++;
    }
    return j;
}