#include "../../include/minishell.h"

int     ft_tab_min(int tab[], int i)
{
    int j;
    int min;

    j = 0;
    min = tab[j];
    while (j < i)
    {
        if (tab[j] < min)
            min = tab[j];
        j++;
    }
    if (min == 0)
    {
        j = 0;
        while (j < i)
        {
            if (tab[j] > min)
                return tab[j];
            j++;
        }
    }
    return min;
}